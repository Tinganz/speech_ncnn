#include "imgui.h"
#include "imgui_helper.h"
#include "imgui_internal.h"
#include <ImGuiFileDialog.h>
#include "entry.h"
#include "Wave.hpp"
#include "Speech.hpp"
#include <thread>
#include "Config.h"

#define DUMP_WAVE   0
#define DEFAULT_MAIN_VIEW_WIDTH     1680
#define DEFAULT_MAIN_VIEW_HEIGHT    1024

static std::mutex g_mutex;
static bool g_app_will_quit = false;
static int thread_main(bool& done, bool &running, bool &start,
                        int threads, int view_size,
                        int64_t& processing_time, int64_t& source_time,
                        AudioFrame* input_frame, std::string& outputs)
{
    int64_t t1, t2;
    if (!input_frame)
        return 0;
    running = true;
#if DUMP_WAVE
    wave_error error = WAV_NO_ERROR;
    WavWriter writer("/Users/dicky/Desktop/dump.wav", 1, 16000, 32, &error);
#endif
    // init speech
    std::vector<std::string> param_path;
    std::vector<std::string> bin_path;
    std::string decoder_param_path = std::string(DEFAULT_MODEL_PATH) + "/decoder_CETS.param";
    std::string encoder_param_path = std::string(DEFAULT_MODEL_PATH) + "/encoder_CETS.param";
    std::string joiner_param_path =  std::string(DEFAULT_MODEL_PATH) + "/joiner_CETS.param";
    std::string decoder_bin_path =   std::string(DEFAULT_MODEL_PATH) + "/decoder_CETS.bin";
    std::string encoder_bin_path =   std::string(DEFAULT_MODEL_PATH) + "/encoder_CETS.bin";
    std::string joiner_bin_path =    std::string(DEFAULT_MODEL_PATH) + "/joiner_CETS.bin";
    param_path.push_back(encoder_param_path);
    param_path.push_back(decoder_param_path);
    param_path.push_back(joiner_param_path);
    bin_path.push_back(encoder_bin_path);
    bin_path.push_back(decoder_bin_path);
    bin_path.push_back(joiner_bin_path);
    Speech speech(param_path, bin_path, threads);
    if (input_frame->is_recording)
    {
        speech.do_recognize();
        while(1)
        {
            start = true;
            if (g_app_will_quit || done)
            {
                speech.push_data(nullptr, 0);
                speech.stop_recognize();
                break;
            }
            if (input_frame->mutex.try_lock())
            {
                if (input_frame->frame.flags & IM_MAT_FLAGS_CUSTOM_PREROLL)
                {
                    speech.push_data((const float *)input_frame->frame.data, input_frame->frame.total());
                    input_frame->frame.flags &= ~IM_MAT_FLAGS_CUSTOM_PREROLL;
#if DUMP_WAVE
                    if (writer.wave_writer_get_sample_bits() > 0)
                    {
                        writer.wave_writer_put_samples(input_frame->frame.data, input_frame->frame.w);
                    }
#endif
                }
                input_frame->mutex.unlock();
            }
            
            g_mutex.lock();
            outputs = speech.m_text;
            g_mutex.unlock();
        }
    }
    else
    {
        start = true;
        source_time = (float)input_frame->frame.w / (float)input_frame->frame.rate.num * 1000000;
        t1 = get_current_time();
        outputs = speech.recognize((const float *)input_frame->frame.data, input_frame->frame.total());
        t2 = get_current_time();
        processing_time = t2 - t1;
    }
    start = false;
    running = false;
    return 0;
}

static void show_waveform(ImGui::ImMat& plot_frame_max, ImGui::ImMat& plot_frame_min, ImVec2 pos, ImVec2 size)
{
    ImGui::PushStyleColor(ImGuiCol_FrameBg, 0);
    ImGui::PushStyleColor(ImGuiCol_PlotLines, ImVec4(0.f, 1.f, 0.f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.1f, 0.5f, 0.1f, 0.5f));
    int channel_height = size.y / plot_frame_max.c;
    for (int i = 0; i < plot_frame_max.c; i++)
    {
        std::string id_string = "##wave_form@channel" + std::to_string(i);
        ImGui::ImMat channel_data_max = plot_frame_max.channel(i);
        ImGui::ImMat channel_data_min = plot_frame_min.channel(i);
        if (plot_frame_max.empty() || plot_frame_min.empty())
            continue;
        ImGui::SetCursorScreenPos(pos + ImVec2(0, i * channel_height));
        ImGui::PlotLinesEx(id_string.c_str(), (float *)channel_data_max.data, channel_data_max.w, 0, nullptr, -1.0f, 1.0f, size, sizeof(float), false, true);
        ImGui::SetCursorScreenPos(pos + ImVec2(0, i * channel_height));
        ImGui::PlotLinesEx(id_string.c_str(), (float *)channel_data_min.data, channel_data_min.w, 0, nullptr, -1.0f, 1.0f, size, sizeof(float), false, true);
    }
    ImGui::PopStyleColor(3);
}
/****************************************************************************************
 * 
 * Application Framework
 *
 ***************************************************************************************/
void Application_GetWindowProperties(ApplicationWindowProperty& property)
{
    property.name = "NCNN Speech";
    property.docking = false;
    property.viewport = false;
    property.auto_merge = false;
    property.width = DEFAULT_MAIN_VIEW_WIDTH;
    property.height = DEFAULT_MAIN_VIEW_HEIGHT;
}

void Application_SetupContext(ImGuiContext* ctx)
{
    if (!ctx)
        return;
#ifdef USE_BOOKMARK
    ImGuiSettingsHandler bookmark_ini_handler;
    bookmark_ini_handler.TypeName = "BookMark";
    bookmark_ini_handler.TypeHash = ImHashStr("BookMark");
    bookmark_ini_handler.ReadOpenFn = [](ImGuiContext* ctx, ImGuiSettingsHandler* handler, const char* name) -> void*
    {
        return ImGuiFileDialog::Instance();
    };
    bookmark_ini_handler.ReadLineFn = [](ImGuiContext* ctx, ImGuiSettingsHandler* handler, void* entry, const char* line) -> void
    {
        IGFD::FileDialog * dialog = (IGFD::FileDialog *)entry;
        dialog->DeserializeBookmarks(line);
    };
    bookmark_ini_handler.WriteAllFn = [](ImGuiContext* ctx, ImGuiSettingsHandler* handler, ImGuiTextBuffer* out_buf)
    {
        ImGuiContext& g = *ctx;
        out_buf->reserve(out_buf->size() + g.SettingsWindows.size() * 6); // ballpark reserve
        auto bookmark = ImGuiFileDialog::Instance()->SerializeBookmarks();
        out_buf->appendf("[%s][##%s]\n", handler->TypeName, handler->TypeName);
        out_buf->appendf("%s\n", bookmark.c_str());
        out_buf->append("\n");
    };
    ctx->SettingsHandlers.push_back(bookmark_ini_handler);
#endif
}

void Application_Initialize(void** handle)
{
}

void Application_Finalize(void** handle)
{
}

bool Application_Frame(void * handle, bool app_will_quit)
{
    static bool app_done = false;
    g_app_will_quit = app_will_quit;
    // Main Window
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                            ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | 
                            ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus;
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(io.DisplaySize, ImGuiCond_None);
    ImGui::Begin("NCNN Speech Test", nullptr, flags);
    ImDrawList *draw_list = ImGui::GetWindowDrawList();
    static std::thread * test_thread = nullptr;
    static AudioFrame * in_frame = nullptr;
    static std::string outputs;
    static int m_threads = 8;
    static std::string m_serial_port;
    static int m_input_type = 0; // 0 = file, 1 = microphone, 2 = serial port
    static bool m_running = false;
    static bool m_done = true;
    static bool m_start = false;
    static int64_t m_processing_time = 0;
    static int64_t m_source_time = 0;
    static std::string m_file_path;
    static std::vector<std::string> m_serial_dev;
    const char* threads_items[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8"};
    const char* input_items[] = { "from file", "microphone", "serial port" };
    const std::string filters = "Audio files (*.wav){.wav}";
    const int channel_height = 128;
    const int scrollSize = 16;
    float wav_view_base_width = ImGui::GetWindowWidth() - 300 - 48 - 40;
    ImVec2 channel_view_size = ImVec2(wav_view_base_width, channel_height);
    ImGui::BeginChild("##Speech_Config", ImVec2(300, ImGui::GetWindowHeight() - 60), true);
    ImGui::BeginDisabled(m_running);
    ImGui::Combo("Threads", &m_threads, threads_items, IM_ARRAYSIZE(threads_items));
    ImGui::Combo("Input", &m_input_type, input_items, IM_ARRAYSIZE(input_items));
    ImGui::Separator();

    // search serial port devices
    if (m_serial_dev.empty())
    {
        enumSerialPort(m_serial_dev);
        m_serial_port = m_serial_dev.size() > 0 ? m_serial_dev[0] : "";
    }
    else if (m_input_type == 2)
    {
        const char* serial_str = m_serial_port.c_str();
        if (ImGui::BeginCombo("Serial Port", serial_str))
        {
            for (int i = 0; i < m_serial_dev.size(); i++)
            {
                bool is_selected = m_serial_dev[i] == m_serial_port;
                if (ImGui::Selectable(m_serial_dev[i].c_str(), is_selected))
                {
                    m_serial_port = m_serial_dev[i];
                }
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
    }

    if (m_input_type == 0)
    {
        // input from file, we open file dialog
        if (ImGui::Button( ICON_IGFD_FOLDER_OPEN " Open File...", ImVec2(280,32)))
        {
            ImGuiFileDialog::Instance()->OpenDialog("##SpeechOpenFileDlgKey", ICON_IGFD_FOLDER_OPEN " Choose File", 
                                                    filters.c_str(),
                                                    m_file_path.empty() ? "." : m_file_path,
                                                    1, 
                                                    IGFDUserDatas("open"), 
                                                    ImGuiFileDialogFlags_ShowBookmark |
                                                    ImGuiFileDialogFlags_CaseInsensitiveExtention |
                                                    ImGuiFileDialogFlags_DisableCreateDirectoryButton |
                                                    ImGuiFileDialogFlags_Modal);
        }
        ImGui::ShowTooltipOnHover("File Path:%s", m_file_path.c_str());
    }

    ImGui::EndDisabled();
    if (!m_running)
    {
        if (test_thread && test_thread->joinable())
        {
            test_thread->join();
            delete test_thread;
            test_thread = nullptr;
        }
        std::string botton_label = m_input_type == 0 ? std::string(ICON_FA_PLAY) : std::string(ICON_FA_CIRCLE_DOT) + "##start";
        if (ImGui::Button(botton_label.c_str(), ImVec2(64, 64)))
        {
            if (m_input_type == 1)
            {
                // from microphone
                if (in_frame) { in_frame->release(); delete in_frame; in_frame = nullptr; }
                in_frame = new AudioFrame(1, 16000, AUDIO_F32SYS);
                if (in_frame) in_frame->start();
            }
            else if (m_input_type == 2)
            {
                // from serial port
                if (in_frame) { in_frame->release(); delete in_frame; in_frame = nullptr; }
                in_frame = new AudioFrame(m_serial_port, 115200, 160000);
                if (in_frame) in_frame->start();
            }
            m_done = false;
            m_processing_time = 0;
            m_start = false;
            outputs.clear();
            test_thread = new std::thread(thread_main, std::ref(m_done), std::ref(m_running), std::ref(m_start),
                                        m_threads, channel_view_size.x,
                                        std::ref(m_processing_time), std::ref(m_source_time), 
                                        in_frame, std::ref(outputs));
        }
    }
    else
    {
        if (ImGui::Button(ICON_FA_STOP "##stop", ImVec2(64, 64)))
        {
            m_done = true;
            if (test_thread && test_thread->joinable())
            {
                test_thread->join();
                delete test_thread;
                test_thread = nullptr;
                m_done = false;
            }
            if (m_input_type == 1)
            {
                if (in_frame) in_frame->stop();
            }
        }
        ImGui::SameLine();
        ImGui::LoadingIndicatorCircle("Running", 4.0f);
    }
    ImGui::EndChild();

    // running panel
    ImGui::SameLine();
    ImGui::BeginChild("##Speech_Result", ImVec2(ImGui::GetWindowWidth() - 300 - 30, ImGui::GetWindowHeight() - 60), true);
    ImVec2 panel_window_pos = ImGui::GetCursorScreenPos();
    ImVec2 panel_window_size = ImGui::GetWindowSize();
    ImRect panel_rect(panel_window_pos, panel_window_pos + panel_window_size);
    ImGui::Text(" Meida Time: %.2fms", m_source_time / 1000.0);
    ImGui::SameLine();
    ImGui::Text(" Process Time: %.2fms", m_processing_time / 1000.0);
    ImGui::SameLine();
    ImGui::Text(" Speed: %.2f%%", m_processing_time ? (float)m_source_time / (float)m_processing_time * 100.0 : 0);

    ImGui::BeginChild("##Speech_waveform", ImVec2(ImGui::GetWindowWidth() - 30, ImGui::GetWindowHeight() - 60 - scrollSize * 2), false, ImGuiWindowFlags_NoScrollWithMouse);
    auto current_pos = ImGui::GetCursorScreenPos();
    draw_list->AddRect(current_pos, current_pos + channel_view_size, IM_COL32_WHITE, 4);
    if (in_frame)
    {
        if (m_input_type == 0 && !in_frame->empty())
        {
            if (in_frame->mutex.try_lock())
            {
                in_frame->resample(channel_view_size.x);
                in_frame->mutex.unlock();
            }
            show_waveform(in_frame->plot_frame_max, in_frame->plot_frame_min, current_pos, channel_view_size);
        }
        else if (!in_frame->frames.empty())
        {
            size_t frames = channel_view_size.x / in_frame->frames[0].w;
            int show_frame = ImMax(ImMin(frames, in_frame->frames.size()), (size_t)1);
            // test
            ImVec2 frame_size = frames > 0 ? ImVec2(channel_view_size.x / frames, channel_view_size.y) : channel_view_size;
            int frame_index = show_frame;
            for (auto frame = in_frame->frames.end() - 1; frame >= in_frame->frames.end() - show_frame; frame--)
            {
                frame_index --;
                ImVec2 frame_pos = ImVec2(current_pos.x + (*frame).w * frame_index, current_pos.y);
                show_waveform(*frame, *frame, frame_pos, frame_size);
            }
        }

        if (!in_frame->is_recording)
        {
            static float firstTime = 0.f;
            float duration = in_frame->duration > 0 ? in_frame->duration : 1e-10;
            // draw pos line
            float cursor_pos = (in_frame->pos - firstTime) / duration * in_frame->plot_frame_max.w;
            if (cursor_pos >= 0 && cursor_pos <= channel_view_size.x)
            {
                ImVec2 p1(cursor_pos + current_pos.x , current_pos.y);
                ImVec2 p2(cursor_pos + current_pos.x , current_pos.y + channel_view_size.y * in_frame->frame.c);
                ImGui::GetWindowDrawList()->AddLine(p1, p2, IM_COL32(255, 0, 0, 255), 2);
            }
            if (ImGui::Button(in_frame->is_running ? ICON_FA_PAUSE : ICON_FA_PLAY "##Play"))
            {
                in_frame->start();
            }
            ImGui::SameLine();
            if (ImGui::Button(ICON_FA_STOP "##Stop"))
            {
                in_frame->stop();
            }
            ImGui::SameLine();
            float pos = in_frame->pos;
            ImGui::PushItemWidth(channel_view_size.x - 32 * 2);
            if (ImGui::SliderFloat("##Progress", &pos, 0.f, in_frame->duration, "%.1f"))
            {
                in_frame->seek(pos);
            }
            ImGui::PopItemWidth();
        }
        else if (m_start)
        {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 0.f, 0.f, 1.f));
            ImGui::TextUnformatted(ICON_FA_CIRCLE_DOT);
            ImGui::PopStyleColor();
        }
    }
    g_mutex.lock();
    if (!outputs.empty())
    {
        std::string lower_str = outputs;
        std::transform(outputs.begin(), outputs.end(), lower_str.begin(), ::tolower);
        ImGui::Text("%s", lower_str.c_str());
    }
    g_mutex.unlock();
    ImGui::EndChild(); // Speech_waveform
    ImGui::EndChild(); // Speech_Result
    
    // File Dialog
    ImVec2 minSize = ImVec2(600, 400);
	ImVec2 maxSize = ImVec2(FLT_MAX, FLT_MAX);
    if (ImGuiFileDialog::Instance()->Display("##SpeechOpenFileDlgKey", ImGuiWindowFlags_NoCollapse, minSize, maxSize))
    {
        std::string userDatas = std::string((const char*)ImGuiFileDialog::Instance()->GetUserDatas());
        int userDataInt = reinterpret_cast<intptr_t>(ImGuiFileDialog::Instance()->GetUserDatas());
        if (ImGuiFileDialog::Instance()->IsOk() && userDatas.compare("open") == 0)
        {
            m_file_path = ImGuiFileDialog::Instance()->GetFilePathName();
            if (!m_file_path.empty())
            {
                if (in_frame) { in_frame->release(); delete in_frame; in_frame = nullptr; }
                in_frame = new AudioFrame(m_file_path);
            }
        }
        ImGuiFileDialog::Instance()->Close();
    }

    ImGui::End();
    // end frame
    app_done = app_will_quit;
    return app_done;
}
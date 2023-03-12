#include "imgui.h"
#include "imgui_helper.h"
#include "imgui_internal.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cerrno>
#include "entry.h"
#include <SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif

#if defined(__APPLE__)
#define FULLSCREEN_OFFSET_X  0
#define FULLSCREEN_OFFSET_Y  0
#define FULLSCREEN_WIDTH_ADJ  0
#define FULLSCREEN_HEIGHT_ADJ  0
#elif defined(__linux__)
#define FULLSCREEN_OFFSET_X  72
#define FULLSCREEN_OFFSET_Y  0
#define FULLSCREEN_WIDTH_ADJ  64
#define FULLSCREEN_HEIGHT_ADJ  0
#else
#define FULLSCREEN_OFFSET_X  0
#define FULLSCREEN_OFFSET_Y  0
#define FULLSCREEN_WIDTH_ADJ  0
#define FULLSCREEN_HEIGHT_ADJ  32
#endif

void Application_FullScreen(bool on)
{
    ImGui_ImplSDL2_FullScreen(ImGui::GetMainViewport(), on);
}

int main(int argc, char** argv)
{
    // Setup SDL
    // (Some versions of SDL before <2.0.10 appears to have performance/stalling issues on a minority of Windows systems,
    // depending on whether SDL_INIT_GAMECONTROLLER is enabled or disabled.. updating to latest version of SDL is recommended!)
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    ApplicationWindowProperty property(argc, argv);
    Application_GetWindowProperties(property);
    // Init IME effect windows only
    ImGui_ImplSDL2_InitIme();

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(__APPLE__)
    // GL 3.2 Core + GLSL 150
    const char* glsl_version = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    int window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI;
    if (property.resizable) window_flags |= SDL_WINDOW_RESIZABLE;
    if (property.full_size)
    {
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(0, &DM);
        SDL_Rect r;
        SDL_GetDisplayUsableBounds(0, &r);
        property.pos_x = (r.x > 0 && r.x < 100) ? r.x : r.x + FULLSCREEN_OFFSET_X;
        property.pos_y = r.y + FULLSCREEN_OFFSET_Y;
        property.width = DM.w - FULLSCREEN_WIDTH_ADJ;
        property.height = DM.h - r.y;
        property.center = false;
        window_flags |= SDL_WINDOW_BORDERLESS;
    }
    else if (property.full_screen)
    {
        window_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    else
    {
        if (property.top_most)
        {
            window_flags |= SDL_WINDOW_ALWAYS_ON_TOP;
        }
        if (!property.window_border)
        {
            window_flags |= SDL_WINDOW_BORDERLESS;
        }
    }
    std::string title = property.name;
    //title += " SDL_GL3";
    SDL_Window* window = SDL_CreateWindow(title.c_str(), property.center ? SDL_WINDOWPOS_CENTERED : property.pos_x,
                                                        property.center ? SDL_WINDOWPOS_CENTERED : property.pos_y,
                                                        property.width, property.height, window_flags);
    if (!window)
    {
        fprintf(stderr, "Failed to Create Window: %s\n", SDL_GetError());
        return -1;
    }

    // Set window icon
    if (!property.icon_path.empty())
    {
        ImGui_ImplSDL2_SetWindowIcon(window, property.icon_path.c_str());
    }
    // Hook IME effect windows only
    ImGui_ImplSDL2_HookIme(window);
    
    SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    auto ctx = ImGui::CreateContext();
    Application_SetupContext(ctx);
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGuiContext& g = *GImGui;
    io.Fonts->AddFontDefault();
    io.FontGlobalScale = property.scale;
    if (property.power_save) io.ConfigFlags |= ImGuiConfigFlags_EnableLowRefreshMode;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    if (property.docking) io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    if (property.viewport)io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    if (!property.auto_merge) io.ConfigViewportsNoAutoMerge = true;
    // Setup App setting file path
    auto setting_path = property.using_setting_path ? ImGuiHelper::settings_path(property.name) : "";
    auto ini_name = property.name;
    std::replace(ini_name.begin(), ini_name.end(), ' ', '_');
    setting_path += ini_name + ".ini";
    io.IniFilename = setting_path.c_str();
    auto language_path = property.language_path + ini_name + "_language.ini";
    if (property.internationalize)
    {
        io.LanguageFileName = language_path.c_str();
        g.Style.TextInternationalize = 1;
        g.LanguageName = "Default";
    }
    
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImVec4 clear_color = ImVec4(0.f, 0.f, 0.f, 1.f);
    //property.handle = gl_context;
    Application_Initialize(&property.handle);

    // Main loop
    bool done = false;
    bool app_done = false;
    bool show = true;
    while (!app_done)
    {
        ImGui_ImplSDL2_WaitForEvent();
        
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;

            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_SHOWN)
            {
                show = true;
            }
            if (event.type == SDL_WINDOWEVENT && (event.window.event == SDL_WINDOWEVENT_HIDDEN || event.window.event == SDL_WINDOWEVENT_MINIMIZED))
            {
                show = false;
            }
            if (event.type == SDL_WINDOWEVENT && (event.window.event == SDL_WINDOWEVENT_EXPOSED || event.window.event == SDL_WINDOWEVENT_RESTORED))
            {
                show = true;
            }
        }

        if (!show && !(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable))
        {
            ImGui::sleep(10);
            continue;
        }
        
        // Start the Dear ImGui frame
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();

        ImGui::NewFrame();

        if (io.ConfigFlags & ImGuiConfigFlags_EnableLowRefreshMode)
            ImGui::SetMaxWaitBeforeNextFrame(1.0 / property.fps);

        app_done = Application_Frame(property.handle, done);

        ImGui::EndFrame();

        // Rendering
        ImGui::Render();
        SDL_GL_MakeCurrent(window, gl_context);
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
            SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
        }

        SDL_GL_SwapWindow(window);
    }

    Application_Finalize(&property.handle);

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
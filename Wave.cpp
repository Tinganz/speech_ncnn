#include "Wave.hpp"
#include "Resample.hpp"
#include <assert.h>
#include <thread>

// Wav Reader
#define FOUR_CC(a,b,c,d) (((a)<<24) | ((b)<<16) | ((c)<<8) | ((d)<<0))
#define WAV_ERROR(a) do { if (*error) *error = a; } while(0)
#define WAV_ERROR_EXIT(a) do { if (*error) *error = a; fclose(fp); fp = nullptr; return; } while(0)

static int read_byte(FILE *fp, unsigned char *out)
{
    if (1 > fread(out, 1, 1, fp)) {
        return feof(fp) ? 0 : -1;
    }
    return 1;
}

static int read_int32_b(FILE *fp, int *out)
{
    int result;
    unsigned char a, b, c, d;

    if ((result=read_byte(fp, &a)) != 1) return result;
    if ((result=read_byte(fp, &b)) != 1) return result;
    if ((result=read_byte(fp, &c)) != 1) return result;
    if ((result=read_byte(fp, &d)) != 1) return result;

    *out = (a<<24) | (b<<16) | (c<<8) | (d<<0);
    return 1;
}

static int read_int32_l(FILE *fp, int *out)
{
    int result;
    unsigned char a, b, c, d;

    if ((result=read_byte(fp, &a)) != 1) return result;
    if ((result=read_byte(fp, &b)) != 1) return result;
    if ((result=read_byte(fp, &c)) != 1) return result;
    if ((result=read_byte(fp, &d)) != 1) return result;

    *out = (d<<24) | (c<<16) | (b<<8) | (a<<0);
    return 1;
}

static int read_int16_l(FILE *fp, int *out)
{
    int result;
    unsigned char a, b;

    if ((result=read_byte(fp, &a)) != 1) return result;
    if ((result=read_byte(fp, &b)) != 1) return result;

    *out = (b<<8) | (a<<0);
    return 1;
}

WavReader::WavReader(const char *filename, wave_error* _error)
{
    int root_id, root_len, format_id;
    int continue_reading = 1;
    error = _error;
    fp = fopen(filename, "rb");
    if (!fp) { WAV_ERROR(WAV_OPEN_ERROR); return;}
    if (!read_int32_b(fp, &root_id)) WAV_ERROR_EXIT(WAV_IO_ERROR);
    if (root_id != FOUR_CC('R','I','F','F'))  WAV_ERROR_EXIT(WAV_BAD_CONTENT);
    if (!read_int32_l(fp, &root_len)) WAV_ERROR_EXIT(WAV_IO_ERROR);

    while (continue_reading)
    {
        if (!read_int32_b(fp, &format_id)) WAV_ERROR_EXIT(WAV_IO_ERROR);
        switch (format_id) 
        {
        case FOUR_CC('W','A','V','E'):
            if (!read_wave_chunk()) return;
            continue_reading = 0;
            break;
        default:
            if (!skip()) return;
            break;
        }
    }
}

WavReader::~WavReader()
{
    if (fp) { fclose(fp); fp = nullptr; }
}

int WavReader::skip()
{
    int len;
    if (!read_int32_l(fp, &len)) { WAV_ERROR(WAV_IO_ERROR); return 0; }
    if (fseek(fp, len, SEEK_CUR) == -1) { WAV_ERROR(WAV_IO_ERROR); return 0; }
    return 1;
}

int WavReader::read_wave_chunk()
{
    int result, sub1_id, sub1_len, sub2_id, sub2_len, byte_rate, block_align;
    if ((result = read_int32_b(fp, &sub1_id)) != 1) { if (result == 0) WAV_ERROR(WAV_BAD_CONTENT); else WAV_ERROR(WAV_IO_ERROR); return 0; }
    if (sub1_id == FOUR_CC('J','U','N','K'))  
    {
        skip();
        if ((result = read_int32_b(fp, &sub1_id)) != 1) { if (result == 0) WAV_ERROR(WAV_BAD_CONTENT); else WAV_ERROR(WAV_IO_ERROR); return 0; }
    }
    if (sub1_id != FOUR_CC('f','m','t',' ')) { WAV_ERROR(WAV_BAD_CONTENT); return 0; }
    if ((result = read_int32_l(fp, &sub1_len)) != 1) { if (result == 0) WAV_ERROR(WAV_BAD_CONTENT); else  WAV_ERROR(WAV_IO_ERROR); return 0; }
    if ((result = read_int16_l(fp, &format)) != 1) { if(result == 0) WAV_ERROR(WAV_BAD_CONTENT); else WAV_ERROR(WAV_IO_ERROR); return 0; }
    if ((result = read_int16_l(fp, &num_channels)) != 1) { if (result == 0) WAV_ERROR(WAV_BAD_CONTENT); else WAV_ERROR(WAV_IO_ERROR); return 0; }
    if ((result = read_int32_l(fp, &sample_rate)) != 1) { if (result == 0) WAV_ERROR(WAV_BAD_CONTENT); else WAV_ERROR(WAV_IO_ERROR); return 0; }
    if ((result = read_int32_l(fp, &byte_rate)) != 1) { if (result == 0) WAV_ERROR(WAV_BAD_CONTENT); else WAV_ERROR(WAV_IO_ERROR); return 0; }
    if ((result = read_int16_l(fp, &block_align)) != 1) { if (result == 0) WAV_ERROR(WAV_BAD_CONTENT); else WAV_ERROR(WAV_IO_ERROR); return 0; }
    if ((result = read_int16_l(fp, &sample_bits)) != 1) { if (result == 0) WAV_ERROR(WAV_BAD_CONTENT); else WAV_ERROR(WAV_IO_ERROR); return 0; }
    if ((result = read_int32_b(fp, &sub2_id)) != 1) { if (result == 0) WAV_ERROR(WAV_BAD_CONTENT); else WAV_ERROR(WAV_IO_ERROR); return 0; }
    if (sub2_id == FOUR_CC('L','I','S','T'))  
    {
        skip();
        if ((result = read_int32_b(fp, &sub2_id)) != 1) { if (result == 0) WAV_ERROR(WAV_BAD_CONTENT); else WAV_ERROR(WAV_IO_ERROR); return 0; }
    }
    if (sub2_id != FOUR_CC('d','a','t','a')) { WAV_ERROR(WAV_BAD_CONTENT); return 0; }
    if ((result = read_int32_l(fp, &sub2_len)) != 1) { if (result == 0) WAV_ERROR(WAV_BAD_CONTENT); else WAV_ERROR(WAV_IO_ERROR); return 0; }
    num_samples = sub2_len / (num_channels * sample_bits / 8);
    return 1;
}

int WavReader::wave_reader_get_samples(void *buf, size_t size)
{
    int ret;
    assert(buf != NULL);
    ret = fread(buf, num_channels * sample_bits / 8, size, fp);
    if (ret < size && ferror(fp)) { return -1; }
    return ret;
}

int WavReader::wave_reader_get_samples_planes(void *buf, size_t size, size_t stride)
{
    int ret;
    int length = 0;
    assert(buf != NULL);
    uint8_t* out_buf = (uint8_t*)buf;
    while (length < size)
    {
        for (int i = 0; i < num_channels; i++)
        {
            ret = fread(out_buf + i * stride, sample_bits / 8, 1, fp);
            if (ferror(fp) || feof(fp) || ret < 1) 
                return length;
        }
        length ++;
        out_buf += sample_bits / 8;
    }
    return length;
}

// WavWrite
#define FMT_LEN 16
#define DEFAULT_RIFF_LEN (4 + 8 + FMT_LEN + 8)

static int write_byte(FILE *fp, unsigned char in)
{
    if (1 > fwrite(&in, 1, 1, fp)) { return 0; }
    return 1;
}

static int write_int32_b(FILE *fp, int in)
{
    unsigned char a, b, c, d;
    a = (in>>24) & 0xFF;
    b = (in>>16) & 0xFF;
    c = (in>> 8) & 0xFF;
    d = (in>> 0) & 0xFF;
    if (!write_byte(fp, a)) return 0;
    if (!write_byte(fp, b)) return 0;
    if (!write_byte(fp, c)) return 0;
    if (!write_byte(fp, d)) return 0;
    return 1;
}

static int write_int32_l(FILE *fp, int in)
{
    unsigned char a, b, c, d;
    a = (in>> 0) & 0xFF;
    b = (in>> 8) & 0xFF;
    c = (in>>16) & 0xFF;
    d = (in>>24) & 0xFF;
    if (!write_byte(fp, a)) return 0;
    if (!write_byte(fp, b)) return 0;
    if (!write_byte(fp, c)) return 0;
    if (!write_byte(fp, d)) return 0;
    return 1;
}

static int write_int16_l(FILE *fp, int in)
{
    unsigned char a, b;
    a = (in>> 0) & 0xFF;
    b = (in>> 8) & 0xFF;
    if (!write_byte(fp, a)) return 0;
    if (!write_byte(fp, b)) return 0;
    return 1;
}

static int is_acceptable_num_channels(const int num_channels)
{
    return 1 <= num_channels 
            && num_channels <= 8;
}

static int is_acceptable_sample_bits(const int sample_bits) 
{
    return sample_bits == 8
        || sample_bits == 16
        || sample_bits == 24
        || sample_bits == 32;
}

static int is_acceptable_sample_rate(const int sample_rate)
{
    return sample_rate == 8000
        || sample_rate == 11025
        || sample_rate == 16000
        || sample_rate == 22050
        || sample_rate == 24000
        || sample_rate == 32000
        || sample_rate == 44100
        || sample_rate == 48000
        || sample_rate == 96000;
}

WavWriter::WavWriter(const char *filename, int _num_channels, int _sample_rate, int _sample_bits, wave_error* _error)
{
    assert(filename != NULL);
    error = _error;
    if (!is_acceptable_num_channels(_num_channels) || !is_acceptable_sample_bits(_sample_bits) || !is_acceptable_sample_rate(_sample_rate)) { WAV_ERROR(WAV_BAD_FORMAT); return; }
    fp = fopen(filename, "wb");
    if (!fp) { WAV_ERROR(WAV_OPEN_ERROR); return; }
    num_channels = _num_channels;
    sample_rate = _sample_rate;
    sample_bits = _sample_bits;
    num_samples = 0;
    if (_sample_bits == 32) format = 3;
    if (!write_riff_chunk()) WAV_ERROR_EXIT(WAV_IO_ERROR);
}

WavWriter::~WavWriter()
{
    if (fp)
    {
        int l = num_samples * num_channels * sample_bits / 8;
        assert(0 <= l);
        if (l % 2 != 0) write_byte(fp, 0);
        if (fseek(fp, 0, SEEK_SET) != 0) { WAV_ERROR_EXIT(WAV_IO_ERROR); }
        if (!write_riff_chunk()) { WAV_ERROR_EXIT(WAV_IO_ERROR); }
        fclose(fp);
        fp = nullptr;
    }
}

int WavWriter::write_riff_chunk()
{
    if (!write_int32_b(fp, FOUR_CC('R','I','F','F'))) return 0;
    if (!write_int32_l(fp, DEFAULT_RIFF_LEN + get_data_len())) return 0;
    if (!write_int32_b(fp, FOUR_CC('W','A','V','E'))) return 0;
    if (!write_int32_b(fp, FOUR_CC('f','m','t',' '))) return 0;
    if (!write_int32_l(fp, FMT_LEN)) return 0;
    if (!write_int16_l(fp, format)) return 0;
    if (!write_int16_l(fp, num_channels)) return 0;
    if (!write_int32_l(fp, sample_rate)) return 0;
    if (!write_int32_l(fp, sample_rate * num_channels * sample_bits / 8)) return 0;
    if (!write_int16_l(fp, num_channels * sample_bits / 8)) return 0;
    if (!write_int16_l(fp, sample_bits)) return 0;
    if (!write_int32_b(fp, FOUR_CC('d','a','t','a'))) return 0;
    if (!write_int32_l(fp, get_data_len())) return 0;
    return 1;
}

int WavWriter::get_data_len()
{
    int l = num_samples * num_channels * sample_bits / 8;
    assert(0 <= l);
    if (l % 2 != 0) l++;
    return l;
}

int WavWriter::wave_writer_put_samples(void *buf, size_t size)
{
    int ret;
    assert(buf != NULL);
    ret = fwrite(buf, num_channels * sample_bits / 8, size, fp);
    if (ret < size) return -1;
    num_samples += ret;
    return ret;
}

int WavWriter::wave_writer_put_samples_planes(void *buf, size_t size, size_t stride)
{
    int ret;
    int length = 0;
    assert(buf != NULL);
    uint8_t* in_buf = (uint8_t*)buf;
    while (length < size)
    {
        for (int i = 0; i < num_channels; i++)
        {
            ret = fwrite(in_buf + i * stride, sample_bits / 8, 1, fp);
            if (ferror(fp) || ret < 1) 
                return length;
        }
        length ++;
        in_buf += sample_bits / 8;
        num_samples += ret;
    }
    return length;
}

#define MAX_AUDIO_RECODER_FRAMES 32
void sdl_audio_play_callback(void *opaque, Uint8 *stream, int len)
{
    AudioFrame * frame = (AudioFrame *)opaque;
    if (!frame || frame->frame.empty())
    {
        memset(stream, 0, len);
        return;
    }
    int samples = len / frame->frame.c / frame->frame.elemsize;
    if (frame->sample_pos + samples < frame->frame.w)
    {
        // copy data interlaced
        float * stream_data = (float *)stream;
        for (int c = 0; c < frame->audio_spec.channels; c++)
        {
            float* channel_data = (float*)frame->frame.channel(c).data;
            for (int i = 0; i < samples; i++)
            {
                stream_data[i * frame->audio_spec.channels + c] = channel_data[i + frame->sample_pos];
            }
        }
    }
    else
    {
        memset(stream, 0, len);
    }
    frame->sample_pos += samples;
    if (frame->sample_pos >= frame->frame.w)
    {
        // end of data
        frame->sample_pos = frame->frame.w;
    }
    frame->pos = (float)frame->sample_pos / (float)frame->audio_spec.freq;
}

void sdl_audio_record_callback(void *opaque, Uint8 *stream, int len)
{
    AudioFrame * frame = (AudioFrame *)opaque;
    if (!frame || frame->frame.empty())
    {
        return;
    }
    frame->mutex.lock();
    int samples = len / frame->frame.c / frame->frame.elemsize;
    samples = samples > frame->frame.w ? frame->frame.w : samples;
    for (int c = 0; c < frame->frame.c; c++)
    {
        float* channel_data = (float*)frame->frame.channel(c).data;
        for (int i = 0; i < samples; i++)
        {
            if (frame->audio_spec.format == AUDIO_F32SYS)
            {
                float * stream_data = (float *)stream;
                channel_data[i] = stream_data[i * frame->audio_spec.channels + c];
            }
            else if (frame->audio_spec.format == AUDIO_S32SYS)
            {
                int32_t * stream_data = (int32_t *)stream;
                channel_data[i] = stream_data[i * frame->audio_spec.channels + c] / (float)(INT32_MAX - 1);
            }
            else if (frame->audio_spec.format == AUDIO_S16SYS)
            {
                int16_t * stream_data = (int16_t *)stream;
                channel_data[i] = stream_data[i * frame->audio_spec.channels + c] / (float)(INT16_MAX - 1);
            }
            else if (frame->audio_spec.format == AUDIO_U16SYS)
            {
                uint16_t * stream_data = (uint16_t *)stream;
                channel_data[i] = stream_data[i * frame->audio_spec.channels + c] / (float)(UINT16_MAX - 1) - INT16_MAX;
            }
        }
    }
    frame->frame.flags |= IM_MAT_FLAGS_CUSTOM_PREROLL;
    frame->frames.push_back(frame->frame);
    if (frame->frames.size() > MAX_AUDIO_RECODER_FRAMES)
        frame->frames.erase(frame->frames.begin());
    frame->mutex.unlock();
}

static int thread_main(AudioFrame * ctx)
{
    ctx->is_running = true;
    char buf[4096] = {0};
    size_t total = 0;
    while (!ctx->is_done)
    {
        auto ret = readSerialData(buf + total, 2048);
        if (ret > 0)
        {
            total += ret;
            if (total >= 2048)
            {
                ctx->mutex.lock();
                auto out_size = Resample_s8f32((const int8_t *)buf, (float*)ctx->frame.data, 11000, 16000, total, ctx->frame.w, 1, 4.f);
                int remain_size = total - out_size;
                if (remain_size < 0)
                {
                    total = 0;
                    ctx->mutex.unlock();
                    continue;
                }
                memmove(buf, buf + out_size, remain_size);
                total = remain_size;
                ctx->frame.flags |= IM_MAT_FLAGS_CUSTOM_PREROLL;
                ctx->frames.push_back(ctx->frame);
                if (ctx->frames.size() > MAX_AUDIO_RECODER_FRAMES)
                    ctx->frames.erase(ctx->frames.begin());
                ctx->mutex.unlock();
            }
        }
        else
        {
            usleep(1000);
        }
    }
    ctx->is_running = false;
    return 0;
}

AudioFrame::AudioFrame(std::string path)
{
    wave_error error = WAV_NO_ERROR;
    WavReader reader(path.c_str(), &error);
    if (!error)
    {
        size_t samples = reader.wave_reader_get_num_samples();
        ImDataType type = IM_DT_FLOAT32;
        if (reader.wave_reader_get_format() == 1)
        {
            if (reader.wave_reader_get_sample_bits() == 16) type = IM_DT_INT16;
            if (reader.wave_reader_get_sample_bits() == 8) type = IM_DT_INT8;
        }
        frame.create_type(samples, 1, reader.wave_reader_get_num_channels(), IM_DT_FLOAT32);
        frame.rate.num = reader.wave_reader_get_sample_rate();
        frame.rate.den = 1;
        frame.flags = IM_MAT_FLAGS_AUDIO_FRAME;
        pos = 0;
        sample_pos = 0;
        is_running = false;
        is_recording = false;
        duration = (float)samples / (float)frame.rate.num;
        int length = 0;
        ImGui::ImMat time_domain;
        time_domain.create_type(4096, 1, reader.wave_reader_get_num_channels(), type);
        while (length < samples)
        {
            int ret = reader.wave_reader_get_samples_planes(time_domain.data, 4096, time_domain.cstep * time_domain.elemsize);
            if (ret <= 0)
                break;
            if (length + ret > samples)
                ret = samples - length;
            for (int i = 0; i < reader.wave_reader_get_num_channels(); i++)
            {
                ImGui::ImMat in_channel_mat = time_domain.channel(i);
                ImGui::ImMat out_channel_mat = frame.channel(i);
                for (int n = 0; n < ret; n++)
                {
                    if (reader.wave_reader_get_format() == 1)
                        out_channel_mat.at<float>(n + length, 0) = in_channel_mat.at<int16_t>(n, 0) / 32768.f; // 16bit to float
                    else if (reader.wave_reader_get_format() == 3)
                        out_channel_mat.at<float>(n + length, 0) = in_channel_mat.at<float>(n, 0);
                }
            }
            length += ret;
        }
        SDL_AudioSpec wanted_spec;
        wanted_spec.channels = frame.c;
        wanted_spec.freq = frame.rate.num;
        wanted_spec.format = frame.type == IM_DT_FLOAT32 ? AUDIO_F32SYS : AUDIO_S16SYS;
        wanted_spec.silence = 0;
        wanted_spec.samples = SDL_AUDIO_MIN_BUFFER_SIZE;
        wanted_spec.callback = sdl_audio_play_callback;
        wanted_spec.userdata = this;
        audio_dev = SDL_OpenAudioDevice(NULL, 0, &wanted_spec, &audio_spec, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE | SDL_AUDIO_ALLOW_CHANNELS_CHANGE);
        if (audio_dev)
        {
            SDL_PauseAudioDevice(audio_dev, 1);
        }
    }
}

AudioFrame::AudioFrame(int channels, int sample_rate, int format)
{
    SDL_AudioSpec wanted_spec;
    wanted_spec.channels = channels;
    wanted_spec.freq = sample_rate;
    wanted_spec.format = format;
    wanted_spec.silence = 0;
    wanted_spec.samples = AUDIO_RECODER_BUFFER_SIZE;
    wanted_spec.callback = sdl_audio_record_callback;
    wanted_spec.userdata = this;
    audio_dev = SDL_OpenAudioDevice(NULL, 1, &wanted_spec, &audio_spec, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE | SDL_AUDIO_ALLOW_CHANNELS_CHANGE);
    if (audio_dev)
    {
        SDL_PauseAudioDevice(audio_dev, 1);
        frame.create_type(audio_spec.samples, 1, audio_spec.channels, IM_DT_FLOAT32);
        frame.rate.num = audio_spec.freq;
        frame.rate.den = 1;
        frame.flags = IM_MAT_FLAGS_AUDIO_FRAME;
        pos = 0;
        sample_pos = 0;
        is_running = false;
        is_recording = true;
    }
}

AudioFrame::AudioFrame(const std::string port, int port_rate, int sample_rate)
{
    serial_fd = openAndConfigureSerialPort(port.c_str(), port_rate);
    if (serial_fd < 0)
    {
        if (serial_fd == -1)
            fprintf(stderr, "Unable to connect to serial port.\n");
        else //sfd == -2
            fprintf(stderr, "Error setting serial port attributes.\n");
    }
    else
    {
        frame.create_type(AUDIO_RECODER_BUFFER_SIZE, 1, 1, IM_DT_FLOAT32);
        frame.rate.num = sample_rate;
        frame.rate.den = 1;
        frame.flags = IM_MAT_FLAGS_AUDIO_FRAME;
        is_running = false;
        is_recording = true;
    }
}

void AudioFrame::resample(int view_size)
{
    int samples = frame.w / view_size;
    plot_frame_max.create_type(view_size, 1, frame.c, IM_DT_FLOAT32);
    plot_frame_min.create_type(view_size, 1, frame.c, IM_DT_FLOAT32);
    plot_frame_xs.create_type(view_size, 1,  frame.c, IM_DT_FLOAT32);
    for (int c = 0; c < frame.c; c++)
    {
        float * in_channel_data = (float *)frame.channel(c).data;
        float * out_channel_data_max = (float *)plot_frame_max.channel(c).data;
        float * out_channel_data_min = (float *)plot_frame_min.channel(c).data;
        float * out_channel_data_xs = (float *)plot_frame_xs.channel(c).data;
        for (int i = 0; i < view_size; i++)
        {
            float max_val = -FLT_MAX;
            float min_val = FLT_MAX;
            if (samples <= 32)
            {
                min_val = max_val = in_channel_data[i * samples];
            }
            else
            {
                for (int n = 0; n < samples; n++)
                {
                    float val = in_channel_data[i * samples + n];
                    if (max_val < val) max_val = val;
                    if (min_val > val) min_val = val;
                }
                if (max_val < 0 && min_val < 0)
                {
                    max_val = min_val = min_val;
                }
                else if (max_val > 0 && min_val > 0)
                {
                    max_val = min_val = max_val;
                }
            }
            out_channel_data_max[i] = ImMin(max_val, 1.f);
            out_channel_data_min[i] = ImMax(min_val, -1.f);
            out_channel_data_xs[i] = i;
        }
    }
}

void AudioFrame::release()
{
    if (audio_dev)
    {
        SDL_ClearQueuedAudio(audio_dev);
        SDL_PauseAudioDevice(audio_dev, 1);
        SDL_CloseAudioDevice(audio_dev);
        audio_dev = 0;
    }
    if (serial_fd >= 0)
    {
        if (recoder_thread && recoder_thread->joinable())
        {
            is_done = true;
            recoder_thread->join();
            delete recoder_thread;
            recoder_thread = nullptr;
        }
        closeSerialPort();
        serial_fd = -1;
    }
    frame.release(); 
    frames.clear();
    is_running = false;
}

void AudioFrame::start()
{
    if (audio_dev)
    {
        if (is_running)
            SDL_PauseAudioDevice(audio_dev, 1);
        else 
            SDL_PauseAudioDevice(audio_dev, 0);
        is_running = !is_running;
    }
    else if (serial_fd != -1)
    {
        if (recoder_thread && recoder_thread->joinable())
        {
            is_done = true;
            recoder_thread->join();
            delete recoder_thread;
            recoder_thread = nullptr;
            is_done = false;
        }
        recoder_thread = new std::thread(thread_main, this);
    }
    else
        is_running = false;
}

void AudioFrame::stop()
{
    if (audio_dev)
    {
        SDL_ClearQueuedAudio(audio_dev);
        SDL_PauseAudioDevice(audio_dev, 1);
        is_running = false;
        sample_pos = 0;
        pos = 0;
    }
    else if (serial_fd != -1)
    {
        if (recoder_thread && recoder_thread->joinable())
        {
            is_done = true;
            recoder_thread->join();
            delete recoder_thread;
            recoder_thread = nullptr;
            is_done = false;
        }
    }
    else
    {
        is_running = false;
        sample_pos = 0;
        pos = 0;
    }
}

void AudioFrame::seek(float _pos)
{
    if (is_recording)
        return;
    if (audio_dev)
        SDL_ClearQueuedAudio(audio_dev);
    sample_pos = _pos * audio_spec.freq;
    if (!is_running) pos = _pos;
}

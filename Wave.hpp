#ifndef __WAVE_HPP__
#define __WAVE_HPP__
#include <immat.h>
#include <imgui_internal.h>
#include <stdio.h>
#include <SDL.h>
#include "SerialPort.hpp"
#include <string>
#include <thread>
#include <mutex>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else // _WIN32
#include <sys/time.h>
#endif // _WIN32
#include <unistd.h>

#define SDL_AUDIO_MIN_BUFFER_SIZE 256
#define AUDIO_RECODER_BUFFER_SIZE 2048

typedef enum {
    WAV_NO_ERROR = 0,
    WAV_OPEN_ERROR,
    WAV_IO_ERROR,
    WAV_ALLOC_ERROR,
    WAV_BAD_CONTENT,
    WAV_BAD_FORMAT,
} wave_error;

inline int64_t get_current_time()
{
#ifdef _WIN32
    LARGE_INTEGER freq;
    LARGE_INTEGER pc;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&pc);
    return (int64_t)((double)pc.QuadPart / ((double)freq.QuadPart + 1e-10) * 1000000);
#else  // _WIN32
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
#endif // _WIN32
}

class WavReader
{
public:
    WavReader(const char *filename, wave_error* _error);
    ~WavReader();
public:
    int wave_reader_get_format() { return format; }
    int wave_reader_get_num_channels() { return num_channels; }
    int wave_reader_get_sample_rate() { return sample_rate; }
    int wave_reader_get_sample_bits() { return sample_bits; }
    int wave_reader_get_num_samples() { return num_samples; }
    int wave_reader_get_samples(void *buf, size_t size);
    int wave_reader_get_samples_planes(void *buf, size_t size, size_t stride);
private:
    int format {0};
    int num_channels {0};
    int sample_rate {0};
    int sample_bits {0};
    int num_samples {0};
    FILE *fp {nullptr};
    wave_error *error {nullptr};
private:
    int read_wave_chunk();
    int skip();
};

class WavWriter
{
public:
    WavWriter(const char *filename, int _num_channels, int _sample_rate, int _sample_bits, wave_error* _error);
    ~WavWriter();
public:
    int wave_writer_get_format() { return format; }
    int wave_writer_get_num_channels() { return num_channels; }
    int wave_writer_get_sample_rate() { return sample_rate; }
    int wave_writer_get_sample_bits() { return sample_bits; }
    int wave_writer_get_num_samples() { return num_samples; }
    int wave_writer_put_samples(void *buf, size_t size);
    int wave_writer_put_samples_planes(void *buf, size_t size, size_t stride);
private:
    int num_channels {0};
    int sample_rate {0};
    int sample_bits {0};
    int num_samples {0};
    int format {1};
    FILE *fp {nullptr};
    wave_error *error {nullptr};
private:
    int write_riff_chunk();
    int get_data_len();
};

void sdl_audio_play_callback(void *opaque, Uint8 *stream, int len);
void sdl_audio_record_callback(void *opaque, Uint8 *stream, int len);
typedef struct AudioFrame
{
    AudioFrame() {}
    AudioFrame(std::string path);
    AudioFrame(int channels, int sample_rate, int format);
    AudioFrame(const std::string port, int port_rate, int sample_rate);
    ~AudioFrame() { release(); }

    SDL_AudioDeviceID audio_dev {0};
    SDL_AudioSpec audio_spec;
    int serial_fd {-1};
    size_t sample_pos {0};
    float pos {0};
    float duration {0};
    bool is_recording {false};
    bool is_running {false};
    bool is_done {false};
    std::mutex mutex;
    std::thread * recoder_thread {nullptr};

    ImGui::ImMat frame;
    ImGui::ImMat plot_frame_xs;
    ImGui::ImMat plot_frame_max;
    ImGui::ImMat plot_frame_min;
    std::vector<ImGui::ImMat> frames;

    bool empty() { return frame.empty(); }
    void resample(int view_size);
    void release();

    void start();
    void stop();
    void seek(float _pos);
} AudioFrame;

#endif /* __WAVE_HPP__ */
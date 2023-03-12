#include "SerialPort.hpp"
#include "Resample.hpp"
#include "Wave.hpp"
#include <string>
#include "stdio.h"

static int sfd = -1;

static void usage(const char * name)
{
    fprintf(stderr, "usage:\n");
    fprintf(stderr, "%s -p <port> -o <name> -t <length> -?\n", name);
    fprintf(stderr, "   -p <port>   : USB serial port path(/dev/cu.usbmodemxxxx)\n");
    fprintf(stderr, "   -s <scale>  : input wave data gain(default is 1.f)\n");
    fprintf(stderr, "   -o <name>   : output wave file path\n");
    fprintf(stderr, "   -t <length> : recorde length in second\n");
    fprintf(stderr, "   -?          : show this help\n");
}

int main(int argc, char ** argv)
{
    bool is_light_on = false;
    char buf[4096] = {0};
    float pcm[2048] = {0};
    const char light_on[] = "pixel on 0 0\n";
    const char light_off[] = "pixel off 0 0\n";
    const char finish[] = "pixel off 0 0\n";
    std::string devicePathStr = "/dev/cu.usbmodem141202";
    std::string dumpPathStr = "dump.wav";
    int recorde_time = 10;
    float scale = 1.f;

    // parser input arguments
    const char *option_str = "p:o:t:s:";
    int c = -1;
    while ((c = getopt(argc, argv, option_str)) != -1)
    {
        switch (c)
        {
            case 'p': devicePathStr = std::string(optarg); break;
            case 'o': dumpPathStr = std::string(optarg); break;
            case 't': recorde_time = atoi(optarg); break;
            case 's': scale = atof(optarg); break;
            case '?':
            default: usage(argv[0]); exit(-1); break;
        }
    }

    // open wave file
    wave_error error = WAV_NO_ERROR;
    WavWriter writer(dumpPathStr.c_str(), 1, 16000, 32, &error);

    // open serial port
    const int baudRate = 115200;
    sfd = openAndConfigureSerialPort(devicePathStr.c_str(), baudRate);
    if (sfd < 0)
    {
        if (sfd == -1) {
            fprintf(stderr, "Unable to connect to serial port.\n");
        }
        else { //sfd == -2
            fprintf(stderr, "Error setting serial port attributes.\n");
        }
        return -1;
    }
    fprintf(stderr, "Open serial port %s successed.\n", devicePathStr.c_str());

    // recorde pcm
    size_t saved = 0;
    size_t total = 0;
    size_t request_size = recorde_time * 16000;
    scale = scale <= 0 ? scale = 1.f : scale; 
    int64_t start_time = get_current_time();
    while (true)
    {
        auto ret = readSerialData(buf + total, 2048);
        if (ret > 0)
        {
            total += ret;
            if (total >= 2048)
            {
                fprintf(stderr, "Got %ld data, saved %ld\n", total, saved);

                is_light_on = !is_light_on;
                if (is_light_on)
                    writeSerialData(light_on, strlen(light_on));
                else
                    writeSerialData(light_off, strlen(light_off));
                
                // convert and resample 10k s8 pcm to 16k f32 pcm
                auto out_size = Resample_s8f32((const int8_t *)buf, pcm, 11000, 16000, total, 2048, 1, scale);
                int remain_size = total - out_size;
                if (remain_size < 0)
                {
                    total = 0;
                    continue;
                }
                memmove(buf, buf + out_size, remain_size);
                if (writer.wave_writer_get_sample_bits() > 0)
                {
                    saved += writer.wave_writer_put_samples(pcm, 2048);
                    if (saved > request_size)
                    {
                        break;
                    }
                }
                total = remain_size;
            }
        }
        else
        {
            usleep(1000);
        }
    }
    int64_t end_time = get_current_time();
    fprintf(stderr, "Total saved %ld duration %.2fs\n", saved, (end_time - start_time) / 1000.f);
    writeSerialData(light_off, strlen(light_off));
    closeSerialPort();

    return 0;
}

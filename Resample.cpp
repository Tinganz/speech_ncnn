#include "Resample.hpp"
#include <stdio.h>

size_t Resample_f32(const float *input, float *output, int inSampleRate, int outSampleRate, size_t inputSize, size_t outputMax, int channels)
{
    if (input == NULL)
        return 0;
    size_t outputSize = (size_t) (inputSize * (double) outSampleRate / (double) inSampleRate);
    outputSize -= outputSize % channels;
    outputSize = outputSize < outputMax ? outputSize : outputMax;
    if (output == NULL)
        return outputSize;
    double stepDist = ((double) inSampleRate / (double) outSampleRate);
    const uint64_t fixedFraction = (1LL << 32);
    const double normFixed = (1.0 / (1LL << 32));
    uint64_t step = ((uint64_t) (stepDist * fixedFraction + 0.5));
    uint64_t curOffset = 0;
    for (uint32_t i = 0; i < outputSize; i += 1)
    {
        for (uint32_t c = 0; c < channels; c += 1)
        {
            *output++ = (float) (input[c] + (input[c + channels] - input[c]) * (
                    (double) (curOffset >> 32) + ((curOffset & (fixedFraction - 1)) * normFixed)
            )
            );
        }
        curOffset += step;
        input += (curOffset >> 32) * channels;
        curOffset &= (fixedFraction - 1);
    }
    return outputSize;
}

size_t Resample_s16(const int16_t *input, int16_t *output, int inSampleRate, int outSampleRate, size_t inputSize, int channels)
{
    if (input == NULL)
        return 0;
    size_t outputSize = (size_t) (inputSize * (double) outSampleRate / (double) inSampleRate);
    outputSize -= outputSize % channels;
    if (output == NULL)
        return outputSize;
    double stepDist = ((double) inSampleRate / (double) outSampleRate);
    const uint64_t fixedFraction = (1LL << 32);
    const double normFixed = (1.0 / (1LL << 32));
    uint64_t step = ((uint64_t) (stepDist * fixedFraction + 0.5));
    uint64_t curOffset = 0;
    for (uint32_t i = 0; i < outputSize; i += 1)
    {
        for (uint32_t c = 0; c < channels; c += 1)
        {
            *output++ = (int16_t) (input[c] + (input[c + channels] - input[c]) * (
                    (double) (curOffset >> 32) + ((curOffset & (fixedFraction - 1)) * normFixed)
            )
            );
        }
        curOffset += step;
        input += (curOffset >> 32) * channels;
        curOffset &= (fixedFraction - 1);
    }
    return outputSize;
}

size_t Resample_s8s16(const int8_t *input, int16_t *output, int inSampleRate, int outSampleRate, size_t inputSize, int channels)
{
    if (input == NULL)
        return 0;
    int16_t * input_int16 = (int16_t *)malloc(inputSize * sizeof(int16_t));
    if (!input_int16)
        return 0;
    for (int i = 0; i < inputSize; i++)
    {
        input_int16[i] = input[i] * 256;
    }
    size_t outputSize = Resample_s16(input_int16, output, inSampleRate, outSampleRate, inputSize, channels);
    free(input_int16);
    return outputSize;
}

size_t Resample_s8f32(const int8_t *input, float *output, int inSampleRate, int outSampleRate, size_t inputSize, size_t outputSize, int channels, float scale)
{
    if (input == NULL)
        return outputSize;
    
    size_t _in_length = outputSize * (double) inSampleRate / (double) outSampleRate;
    _in_length -= _in_length % 2;
    float * input_float = (float *)malloc(_in_length * sizeof(float));
    if (!input_float)
        return outputSize;
    for (int i = 0; i < _in_length; i++)
    {
        input_float[i] = input[i] * scale / 255.f;
        input_float[i] = input_float[i] < -1.f ? -1.f : input_float[i] > 1.f ? 1.f : input_float[i];
    }

    size_t ret = Resample_f32(input_float, output, inSampleRate, outSampleRate, _in_length, outputSize, channels);
    if (ret != outputSize)
    {
        printf("out size error\n");
    }

    free(input_float);

    if (ret > 0)
        return _in_length;

    return outputSize;
}
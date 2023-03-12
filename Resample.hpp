#ifndef __RESAMPLE_HPP__
#define __RESAMPLE_HPP__
#include <stdint.h>
#include <stdlib.h>
size_t Resample_f32(const float *input, float *output, int inSampleRate, int outSampleRate, size_t inputSize, size_t outputMax, int channels);
size_t Resample_s16(const int16_t *input, int16_t *output, int inSampleRate, int outSampleRate, size_t inputSize, int channels);
size_t Resample_s8s16(const int8_t *input, int16_t *output, int inSampleRate, int outSampleRate, size_t inputSize, int channels);
size_t Resample_s8f32(const int8_t *input, float *output, int inSampleRate, int outSampleRate, size_t inputSize, size_t outputSize, int channels, float scale = 1.f);
#endif /* __RESAMPLE_HPP__ */
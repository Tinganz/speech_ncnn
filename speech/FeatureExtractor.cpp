#include "FeatureExtractor.h"

FeatureExtractor::FeatureExtractor()
{
    knf::FbankOptions opts;
    opts.frame_opts.dither = 0;
    opts.frame_opts.snip_edges = false;
    opts.frame_opts.samp_freq = expected_sampling_rate_;
    opts.mel_opts.num_bins = 80;
    fbank_ = std::make_unique<knf::OnlineFbank>(opts);
}

void FeatureExtractor::AcceptWaveform(float sampling_rate, const float *waveform, int32_t n)
{
    std::lock_guard<std::mutex> lock(mutex_);
    fbank_->AcceptWaveform(sampling_rate, waveform, n);
}

void FeatureExtractor::InputFinished()
{
    std::lock_guard<std::mutex> lock(mutex_);
    fbank_->InputFinished();
}

int32_t FeatureExtractor::NumFramesReady() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return fbank_->NumFramesReady();
}

bool FeatureExtractor::IsLastFrame(int32_t frame) const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return fbank_->IsLastFrame(frame);
}

ncnn::Mat FeatureExtractor::GetFrames(int32_t frame_index, int32_t n) const 
{
    ncnn::Mat features;
    if (frame_index + n > NumFramesReady())
    {
        fprintf(stderr, "%d + %d > %d\n", frame_index, n, NumFramesReady());
        return features;
    }
    std::lock_guard<std::mutex> lock(mutex_);

    int32_t feature_dim = fbank_->Dim();
    features.create(feature_dim, n);

    for (int32_t i = 0; i != n; ++i)
    {
        const float *f = fbank_->GetFrame(i + frame_index);
        std::copy(f, f + feature_dim, features.row(i));
    }
    return features;
}

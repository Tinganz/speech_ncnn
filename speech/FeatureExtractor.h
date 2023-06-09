#ifndef SHERPA_FEATURES_H_
#define SHERPA_FEATURES_H_
#include <memory>
#include <mutex>  // NOLINT
#include <mat.h>
#include "fbank/online-feature.h"
class FeatureExtractor 
{
public:
    FeatureExtractor();

    /*
    @param sampling_rate The sampling_rate of the input waveform. Should match
                        the one expected by the feature extractor.
    @param waveform Pointer to a 1-D array of size n
    @param n Number of entries in waveform
    */
    void AcceptWaveform(float sampling_rate, const float *waveform, int32_t n);

    // InputFinished() tells the class you won't be providing any
    // more waveform.  This will help flush out the last frame or two
    // of features, in the case where snip-edges == false; it also
    // affects the return value of IsLastFrame().
    void InputFinished();

    int32_t NumFramesReady() const;

    // Note: IsLastFrame() will only ever return true if you have called
    // InputFinished() (and this frame is the last frame).
    bool IsLastFrame(int32_t frame) const;

    /** Get n frames starting from the given frame index.
    *
    * @param frame_index  The starting frame index
    * @param n  Number of frames to get.
    * @return Return a 2-D tensor of shape (n, feature_dim).
    *         ans.w == feature_dim; ans.h == n
    */
    ncnn::Mat GetFrames(int32_t frame_index, int32_t n) const;

private:
    std::unique_ptr<knf::OnlineFbank> fbank_;
    mutable std::mutex mutex_;
    float expected_sampling_rate_ = 16000;
};
#endif /* SHERPA_FEATURES_H_ */

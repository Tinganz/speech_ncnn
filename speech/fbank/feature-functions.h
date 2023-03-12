#ifndef KALDI_NATIVE_FBANK_CSRC_FEATURE_FUNCTIONS_H
#define KALDI_NATIVE_FBANK_CSRC_FEATURE_FUNCTIONS_H

#include <vector>
namespace knf {

// ComputePowerSpectrum converts a complex FFT (as produced by the FFT
// functions in csrc/rfft.h), and converts it into
// a power spectrum.  If the complex FFT is a vector of size n (representing
// half of the complex FFT of a real signal of size n, as described there),
// this function computes in the first (n/2) + 1 elements of it, the
// energies of the fft bins from zero to the Nyquist frequency.  Contents of the
// remaining (n/2) - 1 elements are undefined at output.

void ComputePowerSpectrum(std::vector<float> *complex_fft);

}  // namespace knf

#endif  // KALDI_NATIVE_FBANK_CSRC_FEATURE_FUNCTIONS_H

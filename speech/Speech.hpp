#ifndef __SPEECH_HPP__
#define __SPEECH_HPP__
#include <net.h>
#include <string>
#include <vector>
#include <string>
#include <thread>
#include "FeatureExtractor.h"
#include "SymbolTable.h"

class Speech {
public:
    Speech(const std::vector<std::string> &param_path, const std::vector<std::string> &bin_path, int threads = 1);
    ~Speech();
    std::string recognize(const float *waveform, int32_t n); // single data buffer recognize

    void push_data(const float *waveform, int32_t n); // send data into bank
    void do_recognize();                              // start thread to do recognize
    void stop_recognize();                            // stop recognize if thread is running

private:
    ncnn::Net encoder;
    ncnn::Net decoder;
    ncnn::Net joiner;
    ncnn::Option opt;
    
public:
    FeatureExtractor m_feature_extractor;
    SymbolTable * m_sym {nullptr};
    std::vector<ncnn::Mat> states;
    std::string m_text;
    bool m_done {false};
    bool m_running {false};
    int32_t num_layers_ = 12;               // arg1
    int32_t memory_size_ = 32;              // arg2
    int32_t cnn_module_kernel_ = 31;        // arg3
    int32_t left_context_length_ = 32 / 4;  // arg4
    int32_t chunk_length_ = 32;             // arg5
    int32_t right_context_length_ = 8;      // arg6
    int32_t d_model_ = 512;                 // arg7

    int32_t ContextSize() const { return 2; }
    int32_t BlankId() const { return 0; }

private:
    std::thread * _thread = nullptr;

    std::vector<int32_t> encoder_input_indexes_;
    std::vector<int32_t> encoder_output_indexes_;

    std::vector<int32_t> decoder_input_indexes_;
    std::vector<int32_t> decoder_output_indexes_;

    std::vector<int32_t> joiner_input_indexes_;
    std::vector<int32_t> joiner_output_indexes_;

private:
    void InitEncoderInputOutputIndexes();
    void InitDecoderInputOutputIndexes();
    void InitJoinerInputOutputIndexes();
    std::vector<ncnn::Mat> GetEncoderInitStates() const;

public:
    ncnn::Mat RunEncoder(const ncnn::Mat &features, ncnn::Mat *hx, ncnn::Mat *cx);
    std::pair<ncnn::Mat, std::vector<ncnn::Mat>> RunEncoder(ncnn::Mat &features, const std::vector<ncnn::Mat> &states);
    std::pair<ncnn::Mat, std::vector<ncnn::Mat>> RunEncoderV3(ncnn::Mat &features, const std::vector<ncnn::Mat> &states);
    ncnn::Mat RunDecoder(ncnn::Mat &decoder_input);
    ncnn::Mat RunJoiner(ncnn::Mat &encoder_out, ncnn::Mat &decoder_out);
    void GreedySearch(ncnn::Mat &encoder_out, ncnn::Mat *decoder_out, std::vector<int32_t> *hyp);
};

#endif /* __SPEECH_HPP__ */

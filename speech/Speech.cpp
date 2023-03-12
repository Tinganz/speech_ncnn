#include "Speech.hpp"
#include <mat.h>
#include <numeric>
#include <iostream>
#include <regex>
#include <thread>
#include "table.h"

class MetaData : public ncnn::Layer 
{
public:
    int load_param(const ncnn::ParamDict &pd) override;
    int32_t arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7;
    int32_t arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15;
    int32_t arg16, arg17, arg18, arg19, arg20, arg21, arg22, arg23;
    float arg24, arg25, arg26, arg27, arg28, arg29, arg30, arg31;
};

int MetaData::load_param(const ncnn::ParamDict &pd)
{
    arg0 = pd.get(0, 0), arg1 = pd.get(1, 0), arg2 = pd.get(2, 0);
    arg3 = pd.get(3, 0), arg4 = pd.get(4, 0), arg5 = pd.get(5, 0);
    arg6 = pd.get(6, 0), arg7 = pd.get(7, 0), arg8 = pd.get(8, 0);
    arg9 = pd.get(9, 0), arg10 = pd.get(10, 0), arg11 = pd.get(11, 0);
    arg12 = pd.get(12, 0), arg13 = pd.get(13, 0), arg14 = pd.get(14, 0);
    arg15 = pd.get(15, 0), arg16 = pd.get(16, 0), arg17 = pd.get(17, 0);
    arg18 = pd.get(18, 0), arg19 = pd.get(19, 0), arg20 = pd.get(20, 0);
    arg21 = pd.get(21, 0), arg22 = pd.get(22, 0), arg23 = pd.get(23, 0);

    // The following 8 attributes are of type float
    arg24 = pd.get(24, 0.f), arg25 = pd.get(25, 0.f), arg26 = pd.get(26, 0.f);
    arg27 = pd.get(27, 0.f), arg28 = pd.get(28, 0.f), arg29 = pd.get(29, 0.f);
    arg30 = pd.get(30, 0.f), arg31 = pd.get(31, 0.f);

    return 0;
}

static ncnn::Layer *MetaDataCreator(void * /*userdata*/)
{
    return new MetaData();
}


Speech::Speech(const std::vector<std::string> &param_path, const std::vector<std::string> &bin_path, int threads)
{
    int ret;
    m_sym = new SymbolTable(EnglishTable);
    encoder.register_custom_layer("SherpaMetaData", MetaDataCreator);

    // init network
    opt.use_packing_layout = false;
    opt.use_fp16_packed = false;
    opt.use_fp16_storage = false;
    opt.use_fp16_arithmetic = false;
    opt.num_threads = threads;

    encoder.opt = opt;
    decoder.opt = opt;
    joiner.opt = opt;

    // init encoder net
    ret = encoder.load_param(param_path[0].data());
    if (ret != 0)
    {
        std::cout << "Speech encoder model can't load error:no proto" << std::endl;
        encoder.clear();
        return;
    }
    ret = encoder.load_model(bin_path[0].data());
    if (ret != 0)
    {
        std::cout << "Speech encoder model can't load error:no weight" << std::endl;
        encoder.clear();
        return;
    }

    // init decoder net
    ret = decoder.load_param(param_path[1].data());
    if (ret != 0)
    {
        std::cout << "Speech decoder model can't load error:no proto" << std::endl;
        decoder.clear();
        return;
    }
    ret = decoder.load_model(bin_path[1].data());
    if (ret != 0)
    {
        std::cout << "Speech decoder model can't load error:no weight" << std::endl;
        decoder.clear();
        return;
    }

    // init joiner net
    ret = joiner.load_param(param_path[2].data());
    if (ret != 0)
    {
        std::cout << "Speech joiner model can't load error:no proto" << std::endl;
        joiner.clear();
        return;
    }
    ret = joiner.load_model(bin_path[2].data());
    if (ret != 0)
    {
        std::cout << "Speech joiner model can't load error:no weight" << std::endl;
        joiner.clear();
        return;
    }

    auto layers = encoder.layers();
    for (auto layer : layers)
    {
#if NCNN_STRING
        if (layer->type == "InnerProduct")
        {
            layer->support_vulkan = false;
        }
        if (layer->type == "BinaryOp")
        {
            layer->support_vulkan = false;
        }
#else
        if (layer->typeindex == LayerType::InnerProduct)
        {
            layer->support_vulkan = false;
        }
        if (layer->typeindex == LayerType::BinaryOp)
        {
            layer->support_vulkan = false;
        }
#endif
    }

    // Now load parameters for member variables
    for (const auto *layer : encoder.layers())
    {
        if (layer->type == "SherpaMetaData" && layer->name == "sherpa_meta_data1")
        {
            // Note: We don't use dynamic_cast<> here since it will throw
            // the following error
            //  error: ‘dynamic_cast’ not permitted with -fno-rtti
            const auto *meta_data = reinterpret_cast<const MetaData *>(layer);

            num_layers_ = meta_data->arg1;
            memory_size_ = meta_data->arg2;
            cnn_module_kernel_ = meta_data->arg3;
            left_context_length_ = meta_data->arg4;
            chunk_length_ = meta_data->arg5;
            right_context_length_ = meta_data->arg6;
            d_model_ = meta_data->arg7;
            break;
        }
    }

    InitDecoderInputOutputIndexes();
    InitEncoderInputOutputIndexes();
    InitJoinerInputOutputIndexes();
}

Speech::~Speech() 
{
    encoder.clear();
    decoder.clear();
    joiner.clear();
}

void Speech::InitEncoderInputOutputIndexes()
{
    // input indexes map
    // [0] -> in0, features,
    // [1] -> in1, layer0, s0
    // [2] -> in2, layer0, s1
    // [3] -> in3, layer0, s2
    // [4] -> in4, layer0, s3
    //
    // [5] -> in5, layer1, s0
    // [6] -> in6, layer1, s1
    // [7] -> in7, layer1, s2
    // [8] -> in8, layer1, s3
    //
    // until layer 11
    encoder_input_indexes_.resize(1 + num_layers_ * 4);

    // output indexes map
    // [0] -> out0, encoder_out
    //
    // [1] -> out1, layer0, s0
    // [2] -> out2, layer0, s1
    // [3] -> out3, layer0, s2
    // [4] -> out4, layer0, s3
    //
    // [5] -> out5, layer1, s0
    // [6] -> out6, layer1, s1
    // [7] -> out7, layer1, s2
    // [8] -> out8, layer1, s3
    encoder_output_indexes_.resize(1 + num_layers_ * 4);
    const auto &blobs = encoder.blobs();

    std::regex in_regex("in(\\d+)");
    std::regex out_regex("out(\\d+)");

    std::smatch match;
    for (int32_t i = 0; i != blobs.size(); ++i)
    {
        const auto &b = blobs[i];
        if (std::regex_match(b.name, match, in_regex))
        {
            auto index = std::atoi(match[1].str().c_str());
            encoder_input_indexes_[index] = i;
        } 
        else if (std::regex_match(b.name, match, out_regex))
        {
            auto index = std::atoi(match[1].str().c_str());
            encoder_output_indexes_[index] = i;
        }
    }
}

void Speech::InitDecoderInputOutputIndexes()
{
    // input indexes map
    // [0] -> in0, decoder_input,
    decoder_input_indexes_.resize(1);

    // output indexes map
    // [0] -> out0, decoder_out,
    decoder_output_indexes_.resize(1);

    const auto &blobs = decoder.blobs();
    for (int32_t i = 0; i != blobs.size(); ++i)
    {
        const auto &b = blobs[i];
        if (b.name == "in0") decoder_input_indexes_[0] = i;
        if (b.name == "out0") decoder_output_indexes_[0] = i;
    }
}

void Speech::InitJoinerInputOutputIndexes()
{
    // input indexes map
    // [0] -> in0, encoder_input,
    // [1] -> in1, decoder_input,
    joiner_input_indexes_.resize(2);

    // output indexes map
    // [0] -> out0, joiner_out,
    joiner_output_indexes_.resize(1);

    const auto &blobs = joiner.blobs();
    for (int32_t i = 0; i != blobs.size(); ++i) {
        const auto &b = blobs[i];
        if (b.name == "in0") joiner_input_indexes_[0] = i;
        if (b.name == "in1") joiner_input_indexes_[1] = i;
        if (b.name == "out0") joiner_output_indexes_[0] = i;
    }
}

std::vector<ncnn::Mat> Speech::GetEncoderInitStates() const
{
    std::vector<ncnn::Mat> states;
    states.reserve(num_layers_ * 4);

    for (int32_t i = 0; i != num_layers_; ++i)
    {
        auto s0 = ncnn::Mat(d_model_, memory_size_);
        auto s1 = ncnn::Mat(d_model_, left_context_length_);
        auto s2 = ncnn::Mat(d_model_, left_context_length_);
        auto s3 = ncnn::Mat(cnn_module_kernel_ - 1, d_model_);
        s0.fill(0);
        s1.fill(0);
        s2.fill(0);
        s3.fill(0);
        states.push_back(s0);
        states.push_back(s1);
        states.push_back(s2);
        states.push_back(s3);
    }

    return states;
}

ncnn::Mat Speech::RunEncoder(const ncnn::Mat &features, ncnn::Mat *hx, ncnn::Mat *cx)
{
    if (encoder.get_blobs_size() == 0 || encoder.get_layers_size() == 0)
    {
        std::cout << "network maybe empty, error!!!" << std::endl;
        return ncnn::Mat();
    }
    int32_t num_encoder_layers = 12;
    int32_t d_model = 512;
    int32_t rnn_hidden_size = 1024;

    if (hx->empty()) 
    {
        hx->create(d_model, num_encoder_layers);
        cx->create(rnn_hidden_size, num_encoder_layers);

        hx->fill(0);
        cx->fill(0);
    }

    ncnn::Mat feature_lengths(1);
    feature_lengths[0] = features.h;

    ncnn::Extractor encoder_ex = encoder.create_extractor();

    encoder_ex.input("in0", features);
    encoder_ex.input("in1", feature_lengths);
    encoder_ex.input("in2", *hx);
    encoder_ex.input("in3", *cx);

    ncnn::Mat encoder_out;
    encoder_ex.extract("out0", encoder_out);

    encoder_ex.extract("out2", *hx);
    encoder_ex.extract("out3", *cx);

    return encoder_out;
}

std::pair<ncnn::Mat, std::vector<ncnn::Mat>> Speech::RunEncoder(ncnn::Mat &features, const std::vector<ncnn::Mat> &states)
{
    int32_t num_encoder_layers = 12;
    int32_t d_model = 512;
    int32_t rnn_hidden_size = 1024;
    ncnn::Mat hx;
    ncnn::Mat cx;

    if (states.empty())
    {
        auto s = GetEncoderInitStates();
        hx = s[0];
        cx = s[1];
    }
    else
    {
        hx = states[0];
        cx = states[1];
    }

    ncnn::Mat feature_length(1);
    feature_length[0] = features.h;

    ncnn::Extractor encoder_ex = encoder.create_extractor();

    encoder_ex.input(encoder_input_indexes_[0], features);
    encoder_ex.input(encoder_input_indexes_[1], feature_length);
    encoder_ex.input(encoder_input_indexes_[2], hx);
    encoder_ex.input(encoder_input_indexes_[3], cx);

    ncnn::Mat encoder_out;
    encoder_ex.extract(encoder_output_indexes_[0], encoder_out);

    encoder_ex.extract(encoder_output_indexes_[1], hx);
    encoder_ex.extract(encoder_output_indexes_[2], cx);

    std::vector<ncnn::Mat> next_states = {hx, cx};

    return {encoder_out, next_states};
}

std::pair<ncnn::Mat, std::vector<ncnn::Mat>> Speech::RunEncoderV3(ncnn::Mat &features, const std::vector<ncnn::Mat> &states)
{
    std::vector<ncnn::Mat> _states;

    const ncnn::Mat *p;
    if (states.empty())
    {
        _states = GetEncoderInitStates();
        p = _states.data();
    } 
    else
    {
        p = states.data();
    }

    ncnn::Extractor encoder_ex = encoder.create_extractor();

    // Note: We ignore error check there
    encoder_ex.input(encoder_input_indexes_[0], features);
    for (int32_t i = 1; i != encoder_input_indexes_.size(); ++i)
    {
        encoder_ex.input(encoder_input_indexes_[i], p[i - 1]);
    }

    ncnn::Mat encoder_out;
    encoder_ex.extract(encoder_output_indexes_[0], encoder_out);

    std::vector<ncnn::Mat> next_states(num_layers_ * 4);
    for (int32_t i = 1; i != encoder_output_indexes_.size(); ++i) {
        encoder_ex.extract(encoder_output_indexes_[i], next_states[i - 1]);
    }

    return {encoder_out, next_states};
}

ncnn::Mat Speech::RunDecoder(ncnn::Mat &decoder_input) 
{
    if (decoder.get_blobs_size() == 0 || decoder.get_layers_size() == 0)
    {
        std::cout << "network maybe empty, error!!!" << std::endl;
        return ncnn::Mat();
    }
    ncnn::Extractor decoder_ex = decoder.create_extractor();

    ncnn::Mat decoder_out;
    decoder_ex.input(decoder_input_indexes_[0], decoder_input);
    decoder_ex.extract(decoder_output_indexes_[0], decoder_out);
    decoder_out = decoder_out.reshape(decoder_out.w);

    return decoder_out;
}

ncnn::Mat Speech::RunJoiner(ncnn::Mat &encoder_out, ncnn::Mat &decoder_out)
{
    if (joiner.get_blobs_size() == 0 || joiner.get_layers_size() == 0)
    {
        std::cout << "network maybe empty, error!!!" << std::endl;
        return ncnn::Mat();
    }
    auto joiner_ex = joiner.create_extractor();
    joiner_ex.input(joiner_input_indexes_[0], encoder_out);
    joiner_ex.input(joiner_input_indexes_[1], decoder_out);

    ncnn::Mat joiner_out;
    joiner_ex.extract(joiner_output_indexes_[0], joiner_out);
    return joiner_out;
}

void Speech::GreedySearch(ncnn::Mat &encoder_out, ncnn::Mat *decoder_out, std::vector<int32_t> *hyp)
{
    int32_t context_size = 2;
    int32_t blank_id = 0;  // hard-code it to 0
    ncnn::Mat decoder_input(context_size);
    static int blank_count = 0;
    for (int32_t t = 0; t != encoder_out.h; ++t) 
    {
        ncnn::Mat encoder_out_t(encoder_out.w, encoder_out.row(t));
        ncnn::Mat joiner_out = RunJoiner(encoder_out_t, *decoder_out);

        auto y = static_cast<int32_t>(std::distance(
            static_cast<const float *>(joiner_out),
            std::max_element(
                static_cast<const float *>(joiner_out),
                static_cast<const float *>(joiner_out) + joiner_out.w)
        ));

        if (y != blank_id)
        {
            static_cast<int32_t *>(decoder_input)[0] = hyp->back();
            static_cast<int32_t *>(decoder_input)[1] = y;
            hyp->push_back(y);
            *decoder_out = RunDecoder(decoder_input);
            blank_count = 0;
        }
        else
        {
            blank_count ++;
        }
    }
    if (blank_count > 20)
    {
        if (hyp->size() > 0 && hyp->at(hyp->size() - 1) > 2)
            hyp->push_back(-1);
    }
}

std::string Speech::recognize(const float *waveform, int32_t n)
{
    m_feature_extractor.AcceptWaveform(16000, waveform, n);
    std::vector<float> tail_paddings(static_cast<int>(0.3 * 16000));
    m_feature_extractor.AcceptWaveform(16000, tail_paddings.data(), tail_paddings.size());
    m_feature_extractor.InputFinished();

    int32_t segment = 51; // conv_emformer
    int32_t offset = chunk_length_; // conv_emformer
    int32_t context_size = ContextSize();
    int32_t blank_id = BlankId();

    std::vector<int32_t> hyp(context_size, blank_id);
    ncnn::Mat decoder_input(context_size);
    for (int32_t i = 0; i != context_size; ++i)
        static_cast<int32_t *>(decoder_input)[i] = blank_id;

    ncnn::Mat decoder_out = RunDecoder(decoder_input);
    ncnn::Mat hx;
    ncnn::Mat cx;
    int32_t num_processed = 0;
    
    while (m_feature_extractor.NumFramesReady() - num_processed >= segment)
    {
        ncnn::Mat features = m_feature_extractor.GetFrames(num_processed, segment);
        num_processed += offset;
        ncnn::Mat encoder_out;
        std::tie(encoder_out, states) = RunEncoderV3(features, states);
        GreedySearch(encoder_out, &decoder_out, &hyp);
    }
    std::string text;
    for (int32_t i = context_size; i != hyp.size(); ++i)
        text += m_sym->at(hyp[i]);

    return text;
}

void Speech::push_data(const float *waveform, int32_t n)
{
    if (!waveform || n == 0)
    {
        std::vector<float> tail_paddings(static_cast<int>(0.3 * 16000));
        m_feature_extractor.AcceptWaveform(16000, tail_paddings.data(), tail_paddings.size());
        m_feature_extractor.InputFinished();
        m_done = true;
        return;
    }
    m_feature_extractor.AcceptWaveform(16000, waveform, n);
}

static int recognize_thread(Speech * ctx)
{
    ctx->m_running = true;
    ctx->m_text.clear();
    int32_t segment = 51; // conv_emformer
    int32_t offset = ctx->chunk_length_; // conv_emformer
    int32_t context_size = ctx->ContextSize();
    int32_t blank_id = ctx->BlankId();
    std::vector<int32_t> hyp(context_size, blank_id);
    ncnn::Mat decoder_input(context_size);
    for (int32_t i = 0; i != context_size; ++i)
        static_cast<int32_t *>(decoder_input)[i] = blank_id;

    std::vector<ncnn::Mat> states;
    ncnn::Mat decoder_out = ctx->RunDecoder(decoder_input);
    ncnn::Mat hx;
    ncnn::Mat cx;
    int32_t num_processed = 0;
    int32_t num_tokens = hyp.size();

    while (!ctx->m_done)
    {
        while (ctx->m_feature_extractor.NumFramesReady() - num_processed >= segment)
        {
            ncnn::Mat features = ctx->m_feature_extractor.GetFrames(num_processed, segment);
            num_processed += offset;
            ncnn::Mat encoder_out;
            std::tie(encoder_out, states) = ctx->RunEncoderV3(features, states);
            ctx->GreedySearch(encoder_out, &decoder_out, &hyp);
        }
        if (hyp.size() != num_tokens)
        {
            num_tokens = hyp.size();
            for (int32_t i = context_size; i != hyp.size(); ++i)
            {
                if (hyp[i] == -1) ctx->m_text.clear();
                else ctx->m_text += ctx->m_sym->at(hyp[i]);
            }
        }
    }

    ctx->m_running = false;
    return 0;
}

void Speech::do_recognize()
{
    stop_recognize();
    m_done = false;
    _thread = new std::thread(recognize_thread, this);
}

void Speech::stop_recognize()
{
    if (_thread && _thread->joinable())
    {
        m_done = true;
        _thread->join();
        delete _thread;
        _thread = nullptr;
    }
}
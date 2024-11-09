//

#ifndef _DECODER_H_
#define _DECODER_H_

#include <fstream>
#include <iostream>
#include <string>
#include "constant.h"
#include "helper.h"

using namespace std;

class Decoder {
    public:
    string channel_path;
    string decoder_path;
    string encoder_path;

    public:
    Decoder() = default;
    ~Decoder() = default;
    Decoder(string channel_path, string decoder_path, string encoder_path);

    private:
    void reed_solomon(string input_path, string output_path, string reed_solomon_encoder_path);
    void hamming(string input_path, string output_path, string hamming_encoder_path);
    void interleave(string input_path, string output_path, int coefficient);
    void deinterleave(string input_path, string output_path, int coefficient);

    public:
    string skip();
    string reed_solomon();
    string reed_solomon_hamming();
    string reed_solomon_hamming_interleave(int coefficient);
};

#include "decoder.cpp"

#endif
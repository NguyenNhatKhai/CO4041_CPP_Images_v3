//

#ifndef _ENCODER_H_
#define _ENCODER_H_

#include <fstream>
#include <iostream>
#include <string>
#include "constant.h"
#include "helper.h"

using namespace std;

class Encoder {
    public:
    string source_path;
    string encoder_path;

    public:
    Encoder() = default;
    ~Encoder() = default;
    Encoder(string source_path, string encoder_path);

    private:
    void reed_solomon(string input_path, string output_path);
    void hamming(string input_path, string output_path);
    void interleave(string input_path, string output_path, int coefficient);
    void deinterleave(string input_path, string output_path, int coefficient);

    public:
    string skip();
    string reed_solomon();
    string reed_solomon_hamming();
    string reed_solomon_hamming_interleave(int coefficient);
};

#include "encoder.cpp"

#endif
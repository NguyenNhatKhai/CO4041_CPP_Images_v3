//

#include "encoder.h"

Encoder::Encoder(string source_path, string encoder_path) {
    this->source_path = source_path;
    this->encoder_path = encoder_path;
}

void Encoder::reed_solomon(string input_path, string output_path) {
    ifstream input_file(input_path + ".txt");
    ofstream output_file(output_path + ".txt");
    string input_buffer(RS_CODEWORD, '0');
    while (input_file.read(input_buffer.data(), RS_MESSAGE) || input_file.gcount() > 0) {
        fill(input_buffer.begin() + input_file.gcount(), input_buffer.end(), '0');
        output_file.write(input_buffer.data(), RS_CODEWORD);
    }
    input_file.close();
    output_file.close();
}

void Encoder::hamming(string input_path, string output_path) {
    ifstream input_file(input_path + ".txt");
    ofstream output_file(output_path + ".txt");
    string input_buffer(HAMMING_CODEWORD, '0');
    while (input_file.read(input_buffer.data(), HAMMING_MESSAGE) || input_file.gcount() > 0) {
        fill(input_buffer.begin() + input_file.gcount(), input_buffer.end(), '0');
        output_file.write(input_buffer.data(), HAMMING_CODEWORD);
    }
    input_file.close();
    output_file.close();
}

void Encoder::interleave(string input_path, string output_path, int coefficient) {
    ifstream input_file(input_path + ".txt");
    ofstream output_file(output_path + ".txt");
    string input_buffer(HAMMING_MESSAGE * coefficient, '0');
    string output_buffer(HAMMING_MESSAGE * coefficient, '0');
    while (input_file.read(input_buffer.data(), HAMMING_MESSAGE * coefficient) || input_file.gcount() > 0) {
        for (int i = 0; i < HAMMING_MESSAGE; i ++) {
            for (int j = 0; j < coefficient; j ++) {
                output_buffer[i * coefficient + j] = input_buffer[j * HAMMING_MESSAGE + i];
            }
        }
        output_file.write(output_buffer.data(), HAMMING_MESSAGE * coefficient);
    }
    input_file.close();
    output_file.close();
}

void Encoder::deinterleave(string input_path, string output_path, int coefficient) {
    ifstream input_file(input_path + ".txt");
    ofstream output_file(output_path + ".txt");
    string input_buffer(HAMMING_CODEWORD * coefficient, '0');
    string output_buffer(HAMMING_CODEWORD * coefficient, '0');
    while (input_file.read(input_buffer.data(), HAMMING_CODEWORD * coefficient) || input_file.gcount() > 0) {
        for (int i = 0; i < coefficient; i ++) {
            for (int j = 0; j < HAMMING_CODEWORD; j ++) {
                output_buffer[i * HAMMING_CODEWORD + j] = input_buffer[j * coefficient + i];
            }
        }
        output_file.write(output_buffer.data(), HAMMING_CODEWORD * coefficient);
    }
    input_file.close();
    output_file.close();
}

string Encoder::skip() {
    string skip_encoder_path = this->encoder_path + "_skip";
    copy(this->source_path, skip_encoder_path);
    return skip_encoder_path;
}

string Encoder::reed_solomon() {
    string reed_solomon_encoder_path = this->encoder_path + "_reed_solomon";
    this->reed_solomon(this->source_path, reed_solomon_encoder_path);
    return reed_solomon_encoder_path;
}

string Encoder::reed_solomon_hamming() {
    string reed_solomon_encoder_path = this->encoder_path + "_reed_solomon";
    this->reed_solomon(this->source_path, reed_solomon_encoder_path);
    string hamming_encoder_path = this->encoder_path + "_hamming";
    this->hamming(reed_solomon_encoder_path, hamming_encoder_path);
    return hamming_encoder_path;
}

string Encoder::reed_solomon_hamming_interleave(int coefficient) {
    string reed_solomon_encoder_path = this->encoder_path + "_reed_solomon";
    this->reed_solomon(this->source_path, reed_solomon_encoder_path);
    string interleave_encoder_path = this->encoder_path + "_interleave";
    this->interleave(reed_solomon_encoder_path, interleave_encoder_path, coefficient);
    string hamming_encoder_path = this->encoder_path + "_hamming";
    this->hamming(interleave_encoder_path, hamming_encoder_path);
    string deinterleave_encoder_path = this->encoder_path + "_deinterleave";
    this->deinterleave(hamming_encoder_path, deinterleave_encoder_path, coefficient);
    return deinterleave_encoder_path;
}


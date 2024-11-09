//

#include "decoder.h"

Decoder::Decoder(string channel_path, string decoder_path, string encoder_path) {
    this->channel_path = channel_path;
    this->decoder_path = decoder_path;
    this->encoder_path = encoder_path;
}

void Decoder::reed_solomon(string input_path, string output_path, string reed_solomon_encoder_path) {
    ifstream input_file(input_path + ".txt");
    ofstream output_file(output_path + ".txt");
    ifstream reed_solomon_encoder_file(reed_solomon_encoder_path + ".txt");
    string input_buffer(RS_CODEWORD, '0');
    string reed_solomon_encoder_buffer(RS_CODEWORD, '0');
    while (input_file.read(input_buffer.data(), RS_CODEWORD) || input_file.gcount() > 0) {
        reed_solomon_encoder_file.read(reed_solomon_encoder_buffer.data(), RS_CODEWORD);
        int different_symbols = 0;
        for (int i = 0; i < RS_CODEWORD; i += RS_SYMBOL) {
            if (input_buffer.substr(i, RS_SYMBOL) != reed_solomon_encoder_buffer.substr(i, RS_SYMBOL)) {
                different_symbols ++;
            }
        }
        if (different_symbols <= RS_CORRECTION_CAPABILITY) {
            output_file.write(reed_solomon_encoder_buffer.data(), RS_MESSAGE);
        } else if (different_symbols <= RS_DETECTION_CAPABILITY) {
            output_file.write(input_buffer.data(), RS_MESSAGE);
        } else {
            output_file.write(input_buffer.data(), RS_MESSAGE);
        }
    }
    input_file.close();
    output_file.close();
    reed_solomon_encoder_file.close();
}

void Decoder::hamming(string input_path, string output_path, string hamming_encoder_path) {
    ifstream input_file(input_path + ".txt");
    ofstream output_file(output_path + ".txt");
    ifstream hamming_encoder_file(hamming_encoder_path + ".txt");
    string input_buffer(HAMMING_CODEWORD, '0');
    string hamming_encoder_buffer(HAMMING_CODEWORD, '0');
    while (input_file.read(input_buffer.data(), HAMMING_CODEWORD) || input_file.gcount() > 0) {
        hamming_encoder_file.read(hamming_encoder_buffer.data(), HAMMING_CODEWORD);
        int different_bits = 0;
        for (int i = 0; i < HAMMING_CODEWORD; i ++) {
            if (input_buffer[i] != hamming_encoder_buffer[i]) {
                different_bits ++;
            }
        }
        if (different_bits <= HAMMING_CORRECTION_CAPABILITY) {
            output_file.write(hamming_encoder_buffer.data(), HAMMING_MESSAGE);
        } else if (different_bits <= HAMMING_DETECTION_CAPABILITY) {
            output_file.write(input_buffer.data(), HAMMING_MESSAGE);
        } else {
            output_file.write(input_buffer.data(), HAMMING_MESSAGE);
        }
    }
    input_file.close();
    output_file.close();
    hamming_encoder_file.close();
}

void Decoder::interleave(string input_path, string output_path, int coefficient) {
    ifstream input_file(input_path + ".txt");
    ofstream output_file(output_path + ".txt");
    string input_buffer(HAMMING_CODEWORD * coefficient, '0');
    string output_buffer(HAMMING_CODEWORD * coefficient, '0');
    while (input_file.read(input_buffer.data(), HAMMING_CODEWORD * coefficient) || input_file.gcount() > 0) {
        for (int i = 0; i < HAMMING_CODEWORD; i ++) {
            for (int j = 0; j < coefficient; j ++) {
                output_buffer[i * coefficient + j] = input_buffer[j * HAMMING_CODEWORD + i];
            }
        }
        output_file.write(output_buffer.data(), HAMMING_CODEWORD * coefficient);
    }
    input_file.close();
    output_file.close();
}

void Decoder::deinterleave(string input_path, string output_path, int coefficient) {
    ifstream input_file(input_path + ".txt");
    ofstream output_file(output_path + ".txt");
    string input_buffer(HAMMING_MESSAGE * coefficient, '0');
    string output_buffer(HAMMING_MESSAGE * coefficient, '0');
    while (input_file.read(input_buffer.data(), HAMMING_MESSAGE * coefficient) || input_file.gcount() > 0) {
        for (int i = 0; i < coefficient; i ++) {
            for (int j = 0; j < HAMMING_MESSAGE; j ++) {
                output_buffer[i * HAMMING_MESSAGE + j] = input_buffer[j * coefficient + i];
            }
        }
        output_file.write(output_buffer.data(), HAMMING_MESSAGE * coefficient);
    }
    input_file.close();
    output_file.close();
}

string Decoder::skip() {
    string skip_decoder_path = this->decoder_path + "_skip";
    copy(this->channel_path, skip_decoder_path);
    return skip_decoder_path;
}

string Decoder::reed_solomon() {
    string reed_solomon_decoder_path = this->decoder_path + "_reed_solomon";
    string reed_solomon_encoder_path = this->encoder_path + "_reed_solomon";
    this->reed_solomon(this->channel_path, reed_solomon_decoder_path, reed_solomon_encoder_path);
    return reed_solomon_decoder_path;
}

string Decoder::reed_solomon_hamming() {
    string hamming_decoder_path = this->decoder_path + "_hamming";
    string hamming_encoder_path = this->encoder_path + "_hamming";
    this->hamming(this->channel_path, hamming_decoder_path, hamming_encoder_path);
    string reed_solomon_decoder_path = this->decoder_path + "_reed_solomon";
    string reed_solomon_encoder_path = this->encoder_path + "_reed_solomon";
    this->reed_solomon(hamming_decoder_path, reed_solomon_decoder_path, reed_solomon_encoder_path);
    return reed_solomon_decoder_path;
}

string Decoder::reed_solomon_hamming_interleave(int coefficient) {
    string interleave_decoder_path = this->decoder_path + "_interleave"; 
    this->interleave(this->channel_path, interleave_decoder_path, coefficient);
    string hamming_decoder_path = this->decoder_path + "_hamming";
    string hamming_encoder_path = this->encoder_path + "_hamming";
    this->hamming(interleave_decoder_path, hamming_decoder_path, hamming_encoder_path);
    string deinterleave_decoder_path = this->decoder_path + "_deinterleave";
    this->deinterleave(hamming_decoder_path, deinterleave_decoder_path, coefficient);
    string reed_solomon_decoder_path = this->decoder_path + "_reed_solomon";
    string reed_solomon_encoder_path = this->encoder_path + "_reed_solomon";
    this->reed_solomon(deinterleave_decoder_path, reed_solomon_decoder_path, reed_solomon_encoder_path);
    return reed_solomon_decoder_path;
}
//

#include "sink.h"

Sink::Sink(string decoder_path, string sink_path) {
    this->decoder_path = decoder_path;
    this->sink_path = sink_path;
}

string Sink::get_image() {
    ifstream decoder_file(this->decoder_path + ".txt");
    ofstream sink_file(this->sink_path + ".txt");
    string decoder_buffer(IMAGE_BITS, '0');
    decoder_file.read(decoder_buffer.data(), IMAGE_BITS);
    sink_file << decoder_buffer;
    decoder_file.close();
    sink_file.close();
    return this->sink_path;
}

void Sink::set_image(string image_path) {
    system(("python Python/txt_to_png.py " + this->sink_path + " " + image_path).c_str());
}
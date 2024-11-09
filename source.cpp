//

#include "source.h"

Source::Source(string source_path) {
    this->source_path = source_path;
}

string Source::get_image(string image_path) {
    system(("python Python/png_to_txt.py " + image_path + " " + this->source_path).c_str());
    return this->source_path;
}
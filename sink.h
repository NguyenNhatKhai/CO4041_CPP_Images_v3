//

#ifndef _SINK_H_
#define _SINK_H_

#include <fstream>
#include <iostream>
#include <string>
#include "constant.h"
#include "helper.h"

using namespace std;

class Sink {
    public:
    string decoder_path;
    string sink_path;

    public:
    Sink() = default;
    ~Sink() = default;
    Sink(string decoder_path, string sink_path);

    public:
    string get_image();
    void set_image(string image_path);
};

#include "sink.cpp"

#endif
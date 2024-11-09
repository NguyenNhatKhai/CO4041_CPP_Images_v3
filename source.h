//

#ifndef _SOURCE_H_
#define _SOURCE_H_

#include <fstream>
#include <iostream>
#include <string>
#include "constant.h"
#include "helper.h"

using namespace std;

class Source {
    public:
    string source_path;

    public:
    Source() = default;
    ~Source() = default;
    Source(string source_path);

    public:
    string get_image(string image_path);
};

#include "source.cpp"

#endif
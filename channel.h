//

#ifndef _CHANNEL_H_
#define _CHANNEL_H_

#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include "constant.h"
#include "helper.h"

using namespace std;

random_device random_source;
mt19937 random_engine(random_source());
uniform_real_distribution<> random_distribution(0.0L, 1.0L);

class Channel {
    public:
    string encoder_path;
    string channel_path;

    public:
    Channel() = default;
    ~Channel() = default;
    Channel(string encoder_path, string channel_path);

    private:
    void random_1s1p(long double error_rate, string input_path, string output_path);
    void gilbert_elliot_2s2p(long double true_to_false_rate, long double false_to_true_rate, string input_path, string output_path);
    void gilbert_elliot_2s4p(long double true_to_false_rate, long double false_to_true_rate, long double error_in_true_rate, long double error_in_false_rate, string input_path, string output_path);

    public:
    string skip();
    string random_1s1p(long double error_rate);
    string gilbert_elliot_2s2p(long double true_to_false_rate, long double false_to_true_rate);
    string gilbert_elliot_2s4p(long double true_to_false_rate, long double false_to_true_rate, long double error_in_true_rate, long double error_in_false_rate);
};

#include "channel.cpp"

#endif
//

#include "channel.h"

Channel::Channel(string encoder_path, string channel_path) {
    this->encoder_path = encoder_path;
    this->channel_path = channel_path;
}

void Channel::random_1s1p(long double error_rate, string input_path, string output_path) {
    ifstream input_file(input_path + ".txt");
    ofstream output_file(output_path + ".txt");
    char input_character;
    while (input_file.get(input_character)) {
        if (random_distribution(random_engine) < error_rate) {
            input_character = (input_character == '0') ? '1' : '0';
        }
        output_file.put(input_character);
    }
    input_file.close();
    output_file.close();
}

void Channel::gilbert_elliot_2s2p(long double true_to_false_rate, long double false_to_true_rate, string input_path, string output_path) {
    ifstream input_file(input_path + ".txt");
    ofstream output_file(output_path + ".txt");
    bool channel_state = true;
    char input_character;
    while (input_file.get(input_character)) {
        if (channel_state) {
            if (random_distribution(random_engine) < true_to_false_rate) {
                channel_state = false;
            }
        } else {
            input_character = (input_character == '0') ? '1' : '0';
            if (random_distribution(random_engine) < false_to_true_rate) {
                channel_state = true;
            }
        }
        output_file.put(input_character);
    }
    input_file.close();
    output_file.close();
}

void Channel::gilbert_elliot_2s4p(long double true_to_false_rate, long double false_to_true_rate, long double error_in_true_rate, long double error_in_false_rate, string input_path, string output_path) {
    ifstream input_file(input_path + ".txt");
    ofstream output_file(output_path + ".txt");
    bool channel_state = true;
    char input_character;
    while (input_file.get(input_character)) {
        if (channel_state) {
            if (random_distribution(random_engine) < error_in_true_rate) {
                input_character = (input_character == '0') ? '1' : '0';
            }
            if (random_distribution(random_engine) < true_to_false_rate) {
                channel_state = false;
            }
        } else {
            if (random_distribution(random_engine) < error_in_false_rate) {
                input_character = (input_character == '0') ? '1' : '0';
            }
            if (random_distribution(random_engine) < false_to_true_rate) {
                channel_state = true;
            }
        }
        output_file.put(input_character);
    }
    input_file.close();
    output_file.close();
}

string Channel::skip() {
    string skip_channel_path = this->channel_path + "_skip";
    copy(this->encoder_path, skip_channel_path);
    return skip_channel_path;
}

string Channel::random_1s1p(long double error_rate) {
    string random_1s1p_channel_path = this->channel_path + "_random_1s1p";
    this->random_1s1p(error_rate, this->encoder_path, random_1s1p_channel_path);
    return random_1s1p_channel_path;
}

string Channel::gilbert_elliot_2s2p(long double true_to_false_rate, long double false_to_true_rate) {
    string gilbert_elliot_2s2p_channel_path = this->channel_path + "_gilbert_elliot_2s2p";
    this->gilbert_elliot_2s2p(true_to_false_rate, false_to_true_rate, this->encoder_path, gilbert_elliot_2s2p_channel_path);
    return gilbert_elliot_2s2p_channel_path;
}

string Channel::gilbert_elliot_2s4p(long double true_to_false_rate, long double false_to_true_rate, long double error_in_true_rate, long double error_in_false_rate) {
    string gilbert_elliot_2s4p_channel_path = this->channel_path + "_gilbert_elliot_2s4p";
    this->gilbert_elliot_2s4p(true_to_false_rate, false_to_true_rate, error_in_true_rate, error_in_false_rate, this->encoder_path, gilbert_elliot_2s4p_channel_path);
    return gilbert_elliot_2s4p_channel_path;
}

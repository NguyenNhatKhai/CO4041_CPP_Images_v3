//

#include "helper.h"

void copy(string input_path, string output_path) {
    ifstream input_file(input_path + ".txt");
    ofstream output_file(output_path + ".txt");
    output_file << input_file.rdbuf();
    input_file.close();
    output_file.close();
}

int segment_compare(string file_path_0, string file_path_1, int segment_length) {
    ifstream file_0(file_path_0 + ".txt");
    ifstream file_1(file_path_1 + ".txt");
    string content_0((istreambuf_iterator<char>(file_0)), istreambuf_iterator<char>());
    string content_1((istreambuf_iterator<char>(file_1)), istreambuf_iterator<char>());
    int different_segments = 0;
    for (int i = 0; i < content_0.size(); i += segment_length) {
        if (content_0.substr(i, segment_length) != content_1.substr(i, segment_length)) {
            different_segments++;
        }
    }
    return different_segments;
}

string get_current_time() {
    time_t now_time_t = time(nullptr);
    tm now_tm = *localtime(&now_time_t);
    timespec now_timespec;
    clock_gettime(CLOCK_REALTIME, &now_timespec);
    stringstream now_stringstream;
    now_stringstream << put_time(&now_tm, "%Y-%m-%d %H:%M:%S") << "." << setw(9) << setfill('0') << now_timespec.tv_nsec;
    return now_stringstream.str();
}

void write_bit_error_rate(string output_path, string source_path, string sink_path) {
    ofstream output_file(output_path + ".txt", ios::app);
    long double bit_error_rate = segment_compare(source_path, sink_path, 1) / static_cast<long double>(IMAGE_BITS);
    output_file << fixed << setprecision(16) << bit_error_rate << endl;
    output_file.close();
}
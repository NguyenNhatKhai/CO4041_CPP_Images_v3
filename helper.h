//

#ifndef _HELPER_H_
#define _HELPER_H_

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void copy(string input_path, string output_path);
int segment_compare(string file_path_0, string file_path_1, int segment_length);

string get_current_time();
void write_bit_error_rate(string output_path, string source_path, string sink_path);

#include "helper.cpp"

#endif
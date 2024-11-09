//

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define NUMBER_OF_ITERATIONS 10
#define NUMBER_OF_SCENARIOS 5

int main() {
    for (int i = 0; i < NUMBER_OF_ITERATIONS; i ++) {
        cout << "Running: " << i << "/" << NUMBER_OF_ITERATIONS - 1 << endl;
        system(("main Output/output_" + to_string(i)).c_str());
    }
    vector<long double> sums(NUMBER_OF_SCENARIOS, 0);
    for (int i = 0; i < NUMBER_OF_ITERATIONS; i ++) {
        ifstream input_file("Output/output_" + to_string(i) + ".txt");
        for (int j = 0; j < NUMBER_OF_SCENARIOS; j ++) {
            long double value;
            input_file >> value;
            sums[j] += value;
        }
        input_file.close();
    }
    ofstream output_file("Output/output.txt");
    for (int j = 0; j < NUMBER_OF_SCENARIOS; j ++) {
        output_file << fixed << setprecision(16) << sums[j] / NUMBER_OF_ITERATIONS << endl;
    }
    output_file.close();
    return 0;
}
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<utility>
#include"utils.h"

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", ",");

    // store target bus time
    int target = std::stoi(input[0]);
    std::vector<int> bus_lines;
    std::vector<int> time_diff;

    // store valid bus lines
    for (int i=1; i<input.size(); i++){

        if (input[i] == "x"){
            continue;
        }

        bus_lines.push_back(std::stoi(input[i]));
    }

    time_diff.resize(bus_lines.size());

    for (int i=0; i<bus_lines.size(); i++){

        time_diff[i] = bus_lines[i] - (target % bus_lines[i]);
    }

    auto it = std::min_element(time_diff.begin(), time_diff.end());

    std::cout << "Answer (part 1): " << bus_lines[it - time_diff.begin()]* *it   << std::endl;

    return 0;
}

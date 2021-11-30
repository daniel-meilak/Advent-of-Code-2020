#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<utility>
#include"../../Utils/utils.h"
#include"../../Utils/math_func.h"

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", ",");
    size_t size = input.size();

    // vectors to store bus line and index
    std::vector<long long> bus_line, index, time_diff; 

    for (size_t i=1; i<size; i++){
        
        // ignore "x"
        if ( input[i] == "x" ){ continue; }

        int line = std::stoi(input[i]);

        // store bus lines (n_k) and line-index (a_k) values 
        bus_line.push_back(line);
        index.push_back( line- ((i-1) % line) );
    }

    // resize vector to store values
    time_diff.resize(bus_line.size());
    int target = std::stoi(input[0]);

    // calculate the number of minutes till bus leaves from target
    for (size_t i=0; i<bus_line.size(); i++){
        time_diff[i] = bus_line[i] - (target % bus_line[i]);
    }

    // find the minimum time difference ('it' is an iterator to the position of the min)
    auto it = std::min_element(time_diff.begin(), time_diff.end());

    std::cout << "Answer (part 1): " << bus_line[it - time_diff.begin()]*(*it)   << std::endl;

    // find the answer using chinese remainder theorem
    long long answer = chinese_remainder(bus_line, index);
    
    std::cout << "Answer (part 2): " << answer << std::endl;

    return 0;
}


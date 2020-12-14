#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<utility>
#include"../utils/utils.h"
#include"../utils/math_func.h"

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", ",");

    // vectors to store bus line and index
    std::vector<long long int> bus_line, index; 

    for (int i=1; i<input.size(); i++){
        
        // ignore "x"
        if ( input[i] == "x" ){ continue; }

        int line = std::stoi(input[i]);

        bus_line.push_back(line);
        index.push_back( line- ((i-1) % line) );
    }

    long long int answer = chinese_remainder(bus_line, index);
    
    std::cout << "Answer (part 2): " << answer << std::endl;

    return 0;
}


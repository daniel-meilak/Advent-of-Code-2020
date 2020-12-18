#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<regex>
#include<cstdlib>
#include"../utils/utils.h"

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");



    return 0;
}

// takes a string containing a maths eqn with no parentheses
// evaluates from left to right 
int do_math(std::string line){

    std::regex numbers(R"(\d+)");
    std::regex signs(R"(\+|\*)");
        

}

std::string expand_brackets(std::string line){

    std::regex brackets(R"(\([0-9 \+\*]+\))");
}
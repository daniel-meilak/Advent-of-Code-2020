#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<list>
#include<unordered_map>
#include<map>
#include"utils.h"

// forward function declarations
int find_term(const std::vector<int> &input, const size_t &term);

int main(){

    // read input into vector of strings.
    std::vector<int> input = input_to_int(read_input("input_15", {","}));

    size_t part1 = 2020;
    size_t part2 = 30000000;

    std::cout << "Answer (part 1): " << find_term(input,part1) << std::endl;
    std::cout << "Answer (part 1): " << find_term(input,part2) << std::endl;

    return 0;
}

int find_term(const std::vector<int> &input, const size_t &term){

    size_t size = input.size()-1;

    // vector containing last pos of index i in sequence
    // if index i has not occured in seq it has value -1
    std::vector<int> last_pos(term,-1);

    // commit sequence up to final number
    for (size_t i=0; i<size; i++){
        last_pos[input[i]] = (int)i;
    }

    // current term starts at last term of input
    int current_term = input.back();
    int next_term;

    // continue sequence till term 'size'
    for (size_t i=size; i<term-1; i++){

        // if current term not in seq
        if ( last_pos[current_term] == -1 ){

            // change last_pos of current_term to current position
            last_pos[current_term] = (int)i;
            
            // next term is 0
            current_term = 0;
        }
        // current term is in sequence, next term is distance to 
        // last occurence
        else {

            next_term = (int)i - last_pos[current_term];
            
            // change last_post of current_term to current position
            last_pos[current_term] = (int)i;

            // change current_term to next_term
            current_term = next_term;
        }
    }

    return current_term;
}
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<list>
#include<chrono>
#include<unordered_map>
#include<map>
#include"../utils/utils.h"

int main(){

    // read input into vector of strings.
    std::vector<int> input = input_to_int(read_input("input", ","));

    // vector size
    int size = 30000000;

    // keep initial time
    auto t1 = std::chrono::high_resolution_clock::now();

    // vector containing last pos of index i in sequence
    // if index i has not occured in seq it has value -1
    std::vector<int> last_pos(size,-1);

    // commit sequence up to final number
    for (int i=0; i<input.size()-1; i++){
        last_pos[input[i]] = i;
    }

    // current term starts at last term of input
    int current_term = input.back();
    int next_term;

    // continue sequence till term 'size'
    for (int i=input.size()-1; i<size-1; i++){

        // if current term not in seq
        if ( last_pos[current_term] == -1 ){

            // change last_pos of current_term to current position
            last_pos[current_term] = i;
            
            // next term is 0
            current_term = 0;
        }
        // current term is in sequence, next term is distance to 
        // last occurence
        else {

            next_term = i - last_pos[current_term];
            
            // change last_post of current_term to current position
            last_pos[current_term] = i;

            // change current_term to next_term
            current_term = next_term;
        }
    }

    // keep final time
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();

    std::cout << "Term " << size << " is: " << current_term << std::endl; 

    // print calc time for comparing map, unordered_map, vector, list usage
    std::cout << duration << std::endl;    

    return 0;
}

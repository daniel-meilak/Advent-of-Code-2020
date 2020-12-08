#include"intcode.h"
#include<iostream>
#include<vector>
#include<string>
#include<utility>
#include<cstdlib>


// constructor for computer_t class
// requires input, i.e. the processed input file
computer_t::computer_t(std::vector<std::string> input){

    // memory is fill with instructions from input
    for (std::string line : input){
        memory.push_back({line.substr(0,3), std::stoi(line.substr(4))});
    }

    backup = memory;

    // initialise system variables
    pos_in_memory = 0;
    accumulator   = 0;
}

// reset memory and system variables to initial state
void computer_t::reset(){

    memory = backup;

    pos_in_memory = 0;
    accumulator   = 0;
}

// run computer
void computer_t::run(){
    
    running = true;

    while (running){
        execute_instructions();
    }
}

void computer_t::execute_instructions(){

    instruction = memory[pos_in_memory].first;
    value       = memory[pos_in_memory].second;

    if      ( instruction == "acc" ){ acc(); }
    else if ( instruction == "jmp" ){ jmp(); }
    else if ( instruction == "nop" ){ nop(); }
    else {
        std::cerr << "Bad instruction at memory pos: " << pos_in_memory << std::endl;
        std::exit(EXIT_FAILURE);  
    } 
}

// increment accumulator
void computer_t::acc(){
    accumulator += value;
    pos_in_memory++;
}

// jump to instruction
void computer_t::jmp(){
    pos_in_memory += value; 
}

// do nothing and continue
void computer_t::nop(){
    // do nothing
    pos_in_memory++;
}

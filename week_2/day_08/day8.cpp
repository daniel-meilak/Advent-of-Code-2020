#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<utility>
#include"../../Utils/utils.h"

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");

    // organise input into pair of <string, int>
    std::vector<std::pair<std::string, int>> memory;
    std::pair<std::string, int> instruction;
    for (std::string line : input){
        memory.push_back({line.substr(0,3), std::stoi(line.substr(4))});
    }

    // push back final instruction to memory
    memory.push_back({"end",0});

    // initialise accumulator and pos_in_memory
    // for part 2 also initialise corrector_pos
    int accumulator = 0;
    int pos_in_memory = 0;
    int corrector_pos = 0;
    int old_corrector_pos = 1;

    // for question require list of completed instructions
    std::vector<bool> completed_instructions(memory.size(), false);

    // run through memory
    bool running = true;
    while (running){

        // label current instruction as completed
        if ( !(completed_instructions[pos_in_memory]) ){
            completed_instructions[pos_in_memory] = true;
        }
        else {
            // code is looping, try swapping a "jmp" and "nop" instruction

            // swap old instruction back (only works afer first swap) 
            if ( memory[old_corrector_pos].first == "jmp" ){
                memory[old_corrector_pos].first = "nop";
            }
            else if ( memory[old_corrector_pos].first == "nop" ){
                memory[old_corrector_pos].first = "jmp";
            }

            bool swapped = false;

            // run through memory to find new instruction to swap
            while( !(swapped) ){

                // swap new instruction
                if ( memory[corrector_pos].first == "jmp" ){
                    memory[corrector_pos].first = "nop";
                    old_corrector_pos = corrector_pos;
                    corrector_pos++;
                    swapped = true;
                }
                else if ( memory[corrector_pos].first == "nop" ){
                    memory[corrector_pos].first = "jmp";
                    old_corrector_pos = corrector_pos;
                    corrector_pos++;
                    swapped = true;
                }
                else {
                    corrector_pos++;
                }
            }

            // reset code, memory and accumulator.
            pos_in_memory = 0;
            accumulator = 0;
            std::fill (completed_instructions.begin(), completed_instructions.end(), false);
        }
        // load current instruction
        instruction = memory[pos_in_memory];

        // execute instruction
        if ( instruction.first == "acc" ){
            accumulator += instruction.second;
            pos_in_memory++;
        }
        else if ( instruction.first == "jmp" ){
            pos_in_memory += instruction.second;
        }
        else if (instruction.first == "nop"){
            // do nothing and continue
            pos_in_memory++;    
        }
        else if (instruction.first == "end"){
            std::cout << "Reached end of code." << std::endl;
            std::cout << "Accumulator value: " << accumulator << std::endl;
            break;
        }
    }

    return 0;
}
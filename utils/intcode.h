#ifndef INTCODE_H
#define INTCODE_H

#include<vector>
#include<string>
#include<utility>

class computer_t{
private:

    // computer instructions
    void acc();
    void jmp();
    void nop();

    // memory created from input
    std::vector<std::pair<std::string, int>> memory;
    std::vector<std::pair<std::string, int>> backup;
    
    // direct access to current line in memory
    std::string instruction;
    int value;

    // state
    bool running;

    // link instrunction string in memory to function call
    void execute_instructions();


public:
    // constructor
    computer_t(std::vector<std::string> input);

    // public functions
    void run();
    void reset();

    // system variables
    int accumulator;
    int pos_in_memory;
};

#endif // INTCODE_H
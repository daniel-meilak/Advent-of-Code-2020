#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"utils.h"

void crab_cups(int n, std::vector<int> &cups, int start);
void part1(std::vector<int> input);
void part2(std::vector<int> input);

int main(){

    // set values for input
    std::string input = read_line("input_23");
    std::vector<int> digits;
    for ( const char &c : input){ digits.push_back(c-'0'); }

    part1(digits);
    part2(digits);

    return 0;
}

void part2(std::vector<int> input){

    // create vector with 1mil entries (ignoring 0 index)
    std::vector<int> cups(1000001);

    // vector at i contains i+1
    // i.e. each index points to the value that follows
    for (size_t i=0; i<cups.size(); i++){
        cups[i] = i+1;
    }

    // index 0 and 1mil are special cases
    // 0 points to 0 so it is never used
    // 1mill goes back to 1
    cups.front() = 0;
    cups.back() = input.front();

    // fill in start of cups using input
    for (size_t i=0; i<input.size()-1; i++){
        cups[input[i]] = input[i+1];
    }
    cups[input[input.size()-1]] = 10;

    // play cups 10 million times
    crab_cups(10000000, cups, input.front());

    long answer = 1UL * cups[1] * cups[cups[1]];

    std::cout << "Answer (part 2): " << answer << std::endl;
}

void part1(std::vector<int> input){

    // vector of cups 
    std::vector<int> cups(10);

    // fill cups with input
    for (size_t i=0; i<input.size()-1; i++){
        cups[input[i]] = input[i+1];
    }
    cups[input[input.size()-1]] = input[0];

    // special cases
    cups[0] = 0;
    
    // play cups 100 times
    crab_cups(100, cups, input.front());

    // string for answer
    std::string answer;
    int i = 1;
    for (int j=0; j<8; j++){
        answer += cups[i] + '0';
        i = cups[i];
    }

    std::cout << "Answer (part 1): " << answer << std::endl;
}


// the cups game
void crab_cups(int n, std::vector<int> &cups, int start){

    // start with first cup
    int cup = start;
    for (int i=1; i<=n; i++){
        // get the next three cups after cup
        int cup1 = cups[cup];
        int cup2 = cups[cup1];
        int cup3 = cups[cup2];

        // destination cup is cup-1
        int dest = cup-1;

        // if dest is too low, loop back
        if (dest <= 0){ dest = cups.size()-1; }

        while (dest == cup1 || dest == cup2 || dest == cup3){
            dest--;
            if (dest <= 0){ dest = cups.size()-1; }
        }

        // reassing links
        int tmp = cups[dest];
        cups[cup] = cups[cup3];
        cups[dest] = cup1;
        cups[cup3] = tmp;

        // move cup to next 
        cup = cups[cup];
    }
}
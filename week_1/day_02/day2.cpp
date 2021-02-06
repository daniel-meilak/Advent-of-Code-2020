#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include"../../Utils/utils.h"

int main(){

    // read input into vector of strings.
    std::vector<std::string> delimiters = {"-"," ",":"};
    std::vector<std::vector<std::string>> input = read_input_2D("input", delimiters);

    int min, max, matches, part1=0, part2=0;
    char letter;
    std::string line, password;

    // loop through each input
    for (const std::vector<std::string> line : input){

        // get min and max
        min = std::stoi(line[0]);
        max = std::stoi(line[1]);
      
        // get letter requirement
        letter = line[2][0];

        // get password
        password = line[3];

        // loop through password and check for number of occurences
        matches = std::ranges::count(password,letter);

        // part 1: check if number of matches is between min and max;
        if ((matches >= min) && (matches <= max)){ part1++; }

        // part 2: check if positions min and max contain required letter
        // this if statement is a logical XOR. 
        if (!(password[min-1]==letter) != !(password[max-1]==letter)){ part2++; }
    }

    std::cout << "Answer (part 1): " << part1 << std::endl;
    std::cout << "Answer (part 2): " << part2 << std::endl;

    return 0;
}
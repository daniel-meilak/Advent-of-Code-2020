#include<iostream>
#include<vector>
#include<string>
#include"../../Utils/utils.h"

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");

    int pos, min, max, matches;
    int valid = 0;
    char letter;
    std::string line, password;
    std::string min_string, max_string;


    // loop through each input
    for (unsigned int i=0; i<input.size(); i++){

        line = input[i];

        // work through the line
        pos=0;

        // extract min number
        while ( line[pos] != '-' ){
            min_string.push_back(line[pos]);
            pos++;
        }
        min = std::stoi(min_string);
        pos++;

        // extract max number
        while ( line[pos] != ' ' ){
            max_string.push_back(line[pos]);
            pos++;
        }
        max = std::stoi(max_string);
        pos++;

        // extract letter requirement
        letter = line[pos];
        pos += 3;

        // extract password
        password = line.substr(pos, line.size()-pos);

        // loop through password and check for number of occurences
        matches = 0;
        for (unsigned int j=0; j<password.size(); j++){
            if ( password[j] == letter){
                matches++;
            }
        }

        // check if number of matches is between min and max;
        if ( (matches >= min) && (matches <= max) ){
            valid++;
        }

        // empty variables for next line;
        min_string.clear();
        max_string.clear();
    }

    std::cout << "Number of valid passwords: " << valid << std::endl;

    return 0;
}
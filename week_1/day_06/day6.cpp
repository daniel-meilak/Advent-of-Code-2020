#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");

    // tally of questions answered
    int tally = 0;
    
    // list of unique questions answered by the group
    std::string questions = "";

    for (unsigned int i=0; i<input.size(); i++){

        std::string line;
        
        line = input[i];

        for (unsigned  int j=0; j<line.size(); j++ ){

            // if new question is answered, add it to questions list
            if ( questions.find(line[j]) == std::string::npos ){
                questions.push_back(line[j]);
            }
        } 

        // Reach end of group
        if ( (input[i+1] == "") || (i == input.size()-1) ){
            tally += questions.size();
            questions.clear();
        }
    }

    std::cout << "Questions answered: " << tally << std::endl;

    return 0;

}
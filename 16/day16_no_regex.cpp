#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<utility>
#include<cstdlib>
#include"../utils/utils.h"

class rule_t{
public:
    std::string name;
    std::pair<int,int> low;
    std::pair<int,int> high;
};

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");

    // vector of rules
    std::vector<rule_t> rules;

    // process rules from input, lines 0-19
    for (int i=0; i<20; i++){
        std::string line = input[i];
        rule_t rule;

        // all values are the same length
        // can use ':' an an achor for substr
        int pos = line.find(':');
        rule.name = line.substr(0,pos);

        // low range 
        rule.low.first   = std::stoi(line.substr(pos+2,2));
        rule.low.second  = std::stoi(line.substr(pos+5,3));

        // high range
        rule.high.first  = std::stoi(line.substr(pos+12,3));
        rule.high.second = std::stoi(line.substr(pos+16,3));

        rules.push_back(rule);
    }


    return 0;
}

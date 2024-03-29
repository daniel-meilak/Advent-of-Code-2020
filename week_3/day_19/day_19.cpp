#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<list>
#include<algorithm>
#include<cstdlib>
#include<regex> 
#include<unordered_map>
#include<map>
#include"utils.h"
#include"math_func.h"

// forward function declarations
std::vector<std::string> process_substring(std::string value);
int match_rules(const std::vector<std::string> &input, const std::vector<std::string>& messages);

int main(){

    // read input
    std::vector<std::string> input = read_input("input_19");

    // split into rules and messages
    std::vector<std::string> input1,input2, messages;

    bool read_rules = false;
    for (const auto& line : input){
        if (line.empty()){ read_rules = true; }

        if (!read_rules){ input1.push_back(line);   }
        else            { messages.push_back(line); }
    } 

    input2 = input1;
    auto it = std::find(input2.begin(), input2.end(), "11: 42 31");
    *it += " | 42 ^ 31";
    it = std::find(input2.begin(), input2.end(), "8: 42");
    *it += " | 42 +";

    std::cout << "Answer (part 1): " << match_rules(input1, messages) << std::endl; 
    std::cout << "Answer (part 2): " << match_rules(input2, messages) << std::endl; 

    return 0;
}

int match_rules(const std::vector<std::string> &input, const std::vector<std::string>& messages){
    
    // map of rules
    std::unordered_map<std::string, std::vector<std::string>> rules;

    for (std::string line : input){

        // colon separates rule index and value
        int pos = line.find(':');

        std::vector<std::string> subrules;

        // match index and value
        std::string index = line.substr(0,pos);
        std::string value = line.substr(pos+2);

        std::vector<std::string> substring = process_substring(value);

        rules[index] = substring;
    }

    // list to store compiled rules 
    std::list<std::string> full_rule = {};
    auto it = full_rule.begin();

    // rule storage
    std::vector<std::string> rule_tmp = rules["0"];

    // start with rule 0 (target)
    it = full_rule.insert(it, rule_tmp.begin(), rule_tmp.end());

    // string of final characters
    std::string final = "()+|ab";

    while ( it != full_rule.end() ){

        if ( final.find(*it) == std::string::npos ){

            std::string rule = *it;
            rule_tmp = rules[rule];
            it = full_rule.erase(it);
            it = full_rule.insert(it, rule_tmp.begin(), rule_tmp.end());
        }
        else { it++; }
    }


    std::stringstream regex_full;
    regex_full << "^";
    for ( std::string element : full_rule){
        regex_full << element;
    }
    regex_full << "$";

    std::regex full_match(regex_full.str());

    // tally matches
    int tally = 0;

    for (std::string message : messages){
        if (std::regex_match(message, full_match)){ tally++; }
    }

    return tally;  
}

std::vector<std::string> process_substring(std::string value){

    // final result
    std::vector<std::string> substring;

    // regex matches 
    std::regex special_1(R"((\d+) \| (\d+) \+)");
    std::regex special_2(R"((\d+) (\d+) \| (\d+) \^ (\d+))");
    std::regex double_or(R"((\d+) (\d+) \| (\d+) (\d+))");
    std::regex single_or(R"(^(\d+) \| (\d+)$)");
    std::regex double_num(R"(^(\d+) (\d+)$)");
    std::regex letter(R"(\"([a-z])\")");

    std::smatch s;
    std::string result;

    if (std::regex_match(value, special_1)){ result = std::regex_replace(value, special_1, "( $1 ) +"); }
    else if (std::regex_match(value, special_2)){
        result = std::regex_replace(value, special_2, "( $1 $2 | $1 $1 $2 $2 | $1 $1 $1 $2 $2 $2 | $1 $1 $1 $1 $2 $2 $2 $2 | $1 $1 $1 $1 $1 $2 $2 $2 $2 $2 | $1 $1 $1 $1 $1 $1 $2 $2 $2 $2 $2 $2 | $1 $1 $1 $1 $1 $1 $1 $2 $2 $2 $2 $2 $2 $2 )");
    }
    else if (std::regex_match(value, double_or)){ result = std::regex_replace(value, double_or, "( $1  $2 | $3  $4 )"); }
    else if (std::regex_match(value, single_or)){ result = std::regex_replace(value, single_or, "( $1 | $2 )" ); }
    else if (std::regex_match(value, double_num)){ result = std::regex_replace(value, double_num, "$1 $2"); }
    else if (std::regex_match(value, letter)){ result = std::regex_replace(value, letter, "$1"); }
    else { result = value; }

    // insert all components into vector for parsing
    std::vector<std::string> parse;
    std::stringstream ss(result);
    std::string element;
    while (ss >> element){
        parse.push_back(element);
    }

    return parse;
}

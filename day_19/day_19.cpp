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
#include"../utils/utils.h"
#include"../utils/math_func.cpp"

std::vector<std::string> process_substring(std::string value);

int main(){

    // read rules into vector of strings
    std::vector<std::string> input1 = read_input("rules2", "");

    // map of rules
    std::unordered_map<std::string, std::vector<std::string>> rules;

    for (std::string line : input1){

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
        else {
            it++;
        }
    }


    std::stringstream regex_full;
    regex_full << "^";
    for ( std::string element : full_rule){
        regex_full << element;
        std::cout << element;
    }
    std::cout << std::endl;
    regex_full << "$";

    std::regex full_match(regex_full.str());

    // read rules into vector of strings
    std::vector<std::string> input2 = read_input("messages", "");

    // tally matches
    int tally = 0;

    for (std::string message : input2){
        if (std::regex_match(message, full_match)){
            tally++;
        }
    }

    std::cout << "Answer: " << tally << std::endl;

    return 0;
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

    if ( std::regex_match(value, special_1) ){

        result = std::regex_replace(value, special_1, "( $1 ) +");
    }
    else if ( std::regex_match(value, special_2) ){

        //result = std::regex_replace(value, special_2, "( $1 $2 )");
        result = std::regex_replace(value, special_2, "( $1 $2 | $1 $1 $2 $2 | $1 $1 $1 $2 $2 $2 | $1 $1 $1 $1 $2 $2 $2 $2 | $1 $1 $1 $1 $1 $2 $2 $2 $2 $2 | $1 $1 $1 $1 $1 $1 $2 $2 $2 $2 $2 $2 | $1 $1 $1 $1 $1 $1 $1 $2 $2 $2 $2 $2 $2 $2 )");
    }
    else if ( std::regex_match(value, double_or) ){

        result = std::regex_replace(value, double_or, "( $1  $2 | $3  $4 )");
    }
    else if ( std::regex_match(value, single_or) ){

        result = std::regex_replace(value, single_or, "( $1 | $2 )" );
    }
    else if ( std::regex_match(value, double_num) ){
    
        result = std::regex_replace(value, double_num, "$1 $2");
    }
    else if ( std::regex_match(value, letter) ){

        result = std::regex_replace(value, letter, "$1");
    }
    else {
        result = value;
    }

    // insert all components into vector for parsing
    std::vector<std::string> parse;
    std::stringstream ss(result);
    std::string element;
    while (ss >> element){
        parse.push_back(element);
    }

    return parse;
}

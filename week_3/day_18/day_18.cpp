#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<regex>
#include<cstdlib>
#include"../../Utils/utils.h"

// forward function declarations
std::string expand_brackets(std::string &line, const bool part2);
long long do_math(std::string line, const bool part2);
bool contains_brackets(std::string &line);
std::string escape_all(std::string line);

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input_18", "");

    long long part1 = 0LL, part2 = 0LL;

    for (std::string line : input){
        part1 += do_math(line,false);
        part2 += do_math(line,true );
    }

    std::cout << "Answer (part 1): " << part1 << std::endl;
    std::cout << "Answer (part 2): " << part2 << std::endl;

    return 0;
}

// takes a string containing a maths eqn and evaluates it with +'s before *'s 
long long do_math(std::string line, const bool part2){

    // if string contains parentheses, resolve before calculating
    if (contains_brackets(line)){ expand_brackets(line,part2); }

    // regex to match integers [0-9]+ and operators +/*
    std::regex numbers(R"(\d+)");
    std::regex signs(R"(\+|\*)");

    // vector to hold ints and operators
    std::vector<long long> values; 
    std::vector<std::string> operators;

    // match ints
    auto match = std::sregex_iterator( line.begin(), line.end(), numbers );
    auto match_end = std::sregex_iterator();

    // push back integer matches
    while ( match != match_end ){
        values.push_back(std::stoll(match->str()));
        match++;
    } 

    // match operators
    match = std::sregex_iterator( line.begin(), line.end(), signs );
    match_end = std::sregex_iterator();

    // push back operators
    while ( match != match_end ){
        operators.push_back(match->str());
        match++;
    }

    // calculate
    // first perfom all additions, replacing some vector elements with 1
    // 1 * 2 + 3 * 4 -> 1 * 5 * 1 * 4
    long long answer = values[0];
    long long sum = 1ULL;

    if (part2){
        for (size_t i=0; i<operators.size(); i++){
            if ( operators[i] == "+" ){
                values[i+1] = values[i] + values [i+1];
                values[i] = 1ULL;
            }
        }
        
        // then multiply out the full line
        for (long long num : values){
            sum *= num;
        }
    }
    else {
        for (size_t i=0; i<operators.size(); i++){
            if ( operators[i] == "+" ){
                answer += values[i+1];
            }
            else {
                answer *= values[i+1];
            }
        }   
    }

    if (part2){ return sum; }
    else {return answer; }
}

std::string expand_brackets(std::string &line, const bool part2){

    // matches bracketed arithmetic expression eg "(1 + 2 * 3)"
    std::regex bracketed(R"(\([0-9 \+\*]+\))");

    // match all bracketed expressions
    std::sregex_iterator match( line.begin(), line.end(), bracketed );
    std::sregex_iterator match_end;

    while ( match != match_end ){
        std::string equation = match->str();
        
        std::string answer = std::to_string(do_math(equation.substr(1, equation.size()-2),part2));

        line = std::regex_replace(line, std::regex(escape_all(equation)), answer, std::regex_constants::format_first_only);
        
        match++;
    }

    if (contains_brackets(line)){ expand_brackets(line,part2); }

    return line;
}

// checks if an equation (string) contains parantheses
bool contains_brackets(std::string &line){

    // matches bracketed arithmetic expression eg "(1 + 2 * 3)"
    std::regex bracketed(R"(\([0-9 \+\*]+\))");
    std::smatch m;

    // if match to regex is found, return true
    return std::regex_search(line, m, bracketed);
}


// takes a string and returns a valid regex for that string by escaping special characters
std::string escape_all(std::string line){

    std::regex special_char("([()+*])");

    std::string escaped = std::regex_replace (line,special_char,"\\$1");

    return escaped;
}
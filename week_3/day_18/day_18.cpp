#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<regex>
#include<cstdlib>
#include"../../Utils/utils.h"

// forward function declarations
std::string expand_brackets(std::string &line);
long long int do_math(std::string line);
bool contains_brackets(std::string &line);
std::string escape_all(std::string line);

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");

    long long int sum = 0;

    for (std::string line : input){
        sum += do_math(line);
    }

    std::cout << "Answer: " << sum << std::endl;

    return 0;
}

// takes a string containing a maths eqn and evaluates from left to right 
long long int do_math(std::string line){

    // if string contains parentheses, resolve before calculating
    if (contains_brackets(line)){
        expand_brackets(line);
    }

    // regex to match integers [0-9]+ and operators +/*
    std::regex numbers(R"(\d+)");
    std::regex signs(R"(\+|\*)");

    // vector to hold ints and operators
    std::vector<long long int> values; 
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
    long long int answer = values[0];
    for (unsigned int i=0; i<operators.size(); i++){
        if ( operators[i] == "+" ){
            answer += values[i+1];
        }
        else {
            answer *= values[i+1];
        }
    }

    return answer;
}

std::string expand_brackets(std::string &line){

    // matches bracketed arithmetic expression eg "(1 + 2 * 3)"
    std::regex bracketed(R"(\([0-9 \+\*]+\))");

    // match all bracketed expressions
    std::sregex_iterator match( line.begin(), line.end(), bracketed );
    std::sregex_iterator match_end;

    while ( match != match_end ){
        std::string equation = match->str();
        
        std::string answer = std::to_string(do_math(equation.substr(1, equation.size()-2)));

        line = std::regex_replace(line, std::regex(escape_all(equation)), answer, std::regex_constants::format_first_only);
        
        match++;
    }

    if (contains_brackets(line)){
        expand_brackets(line);
    }

    return line;
}

// checks if an equation (string) contains parantheses
bool contains_brackets(std::string &line){

    // matches bracketed arithmetic expression eg "(1 + 2 * 3)"
    std::regex bracketed(R"(\([0-9 \+\*]+\))");

    std::smatch m;

    // if match to regex is found, return true
    if (std::regex_search(line, m, bracketed)){
        return true;
    }

    return false;

}


// takes a string and returns a valid regex for that string by escaping special characters
std::string escape_all(std::string line){

    std::regex special_char("([()+*])");

    std::string escaped = std::regex_replace (line,special_char,"\\$1");

    return escaped;
}
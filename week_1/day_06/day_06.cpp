#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"utils.h"

// forward function declarations
std::string string_intersection( std::vector<std::string> group, size_t n );

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input_06");
    size_t size = input.size();

    // tally of questions answered
    size_t part1=0, part2=0;
    
    // list of unique questions answered by the group
    std::string questions = "";

    // part 1
    for (size_t i=0; i<size; i++){

        std::string &line = input[i];

        for (const char &c : line){

            // if new question is answered, add it to questions list
            if (questions.find(c) == std::string::npos){ questions.push_back(c); }
        } 

        // Reach end of group
        if ( (input[i+1] == "") || (i == input.size()-1) ){
            part1 += questions.size();
            questions.clear();
        }
    }

    // part 2
    std::vector<std::vector<std::string>> list;
    std::vector<std::string> group;

    // sort input list into vector of groups
    for (size_t i=0; i<size; i++){

        // sort each line alphabetically 
        std::sort(input[i].begin(), input[i].end());

        // add non-blank line to group
        group.push_back(input[i]);

        // add group to list, flush group for next, skip empty line
        if ( input[i+1] == "" ){
            list.push_back(group);
            group.clear();
            i++;
        }
    }

    // for each group in list, tally nuber of questions answered by everyone
    for (std::vector<std::string> group : list){
        part2 += string_intersection(group, group.size()).size();
    }

    std::cout << "Answer (part 1): " << part1 << std::endl;
    std::cout << "Answer (part 2): " << part2 << std::endl;
    
    return 0;

}

// find the intersections of a group of strings
std::string string_intersection( std::vector<std::string> group, size_t n ){

    // if group is trivial (one person) all questions answered intersect
    if ( n == 1 ){ return group[0]; }
    else {
        // find the intersection of the group with one less person
        std::string next_iter = string_intersection(group, n-1);
        // find the previous set of answeres from the end of the group
        std::string prev_string = group[n-1];
        // variable to store common answers
        std::string intersection;

        // find the intersection of two strings
        std::set_intersection(prev_string.begin(), prev_string.end(), next_iter.begin(), next_iter.end(), std::back_inserter(intersection) );

        return intersection;
    }
}
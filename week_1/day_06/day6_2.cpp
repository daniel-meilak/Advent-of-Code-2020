#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

std::string string_intersection( std::vector<std::string> group, int n );

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");

    std::vector<std::vector<std::string>> list;
    std::vector<std::string> group;

    // sort input list into vector of groups
    for (unsigned int i=0; i<input.size(); i++){

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

    // tally of questions answered
    int tally = 0;

    // for each group in list, tally nuber of questions answered by everyone
    for (std::vector<std::string> group : list){
        tally += string_intersection(group, group.size()).size();
    }

    std::cout << "Number of questions answered: " << tally << std::endl;


    return 0;

}


// find the intersections of a group of strings
std::string string_intersection( std::vector<std::string> group, int n ){

    // if group is trivial (one person) all questions answered intersect
    if ( n == 1 ){
        return group[0];
    }
    // if group is larger than 1
    else {
        // find the intersection of the group with one less person
        std::string next_iter = string_intersection(group, n-1);
        // find the previous set of answeres from the end of the group
        std::string prev_string = group[n-1];
        // variable to store common answers
        std::string intersection;

        // find the intersection of two strings (vector of char)
        // the two strings being compaired are "prev_string" and "next_iter"
        // result stored in the string "intersection"
        std::set_intersection(prev_string.begin(), prev_string.end(), next_iter.begin(), next_iter.end(), std::back_inserter(intersection) );

        return intersection;

    }

}
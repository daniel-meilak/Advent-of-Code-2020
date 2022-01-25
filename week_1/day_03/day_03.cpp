#include<iostream>
#include<vector>
#include<string>
#include"utils.h"

long tree_count(int right, int down, std::vector<std::string>& input);

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input_03");

    // check different slopes
    long part1 = tree_count(3,1,input);
    long part2 = tree_count(1,1,input)*part1*tree_count(5,1,input)*tree_count(7,1,input)*tree_count(1,2,input);       

    std::cout << "Answer (part 1): " << part1 << std::endl;
    std::cout << "Answer (part 2): " << part2 << std::endl;

    return 0;
}


// Goes through horizontal periodic input map, moving down and right counting 
// number of trees "#" encountered in the map
long tree_count(int right, int down, std::vector<std::string>& input){

    // x in horizontal position, y is vertical. (x,y)=(0,0) is at top left
    size_t x=0;
    size_t max_y = input[0].size();

    // number of trees encountered
    long num_trees=0;
    size_t size = input.size();

    for (size_t y=down; y<size; y+=down){

        // move three steps to the right, periodic system
        x = (x+right) % max_y;

        if (input[y][x] == '#'){ num_trees++; }
    }

    return num_trees;
}
#include<iostream>
#include<vector>
#include<string>
#include"../utils/utils.h"

void tree_count(int right, int down, std::vector<std::string>& input);

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");

    // check different slopes
    tree_count(1,1,input);
    tree_count(3,1,input);
    tree_count(5,1,input);
    tree_count(7,1,input);
    tree_count(1,2,input);    

    return 0;
}


// Goes through horizontal periodic input map, moving down and right counting 
// number of trees "#" encountered in the map
void tree_count(int right, int down, std::vector<std::string>& input){

    // x in horizontal position, y is vertical. (x,y)=(0,0) is at top left
    int x=0;
    int max_y = input[0].size();

    // number of trees encountered
    int num_trees=0;

    for (int y=down; y<input.size(); y+=down){

        // move three steps to the right, periodic system
        x = (x+right) % max_y;

        if ( input[y][x] == '#' ){
            num_trees++;
        }

    }

    std::cout << "Right " << right << " Down " << down << " : " << num_trees << std::endl;

    return;

}
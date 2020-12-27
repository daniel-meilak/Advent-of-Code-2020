#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../utils/utils.h"

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");

    // add boundary to system

    // to top and bottom line
    std::string top_bottom(input[0].size()+2,'.');
    input.insert(input.begin(), top_bottom);
    input.push_back(top_bottom);

    // to left and right borders
    for (unsigned int i=1; i<input.size()-1; i++){
        input[i].insert(input[i].begin(),'.');
        input[i].push_back('.');
    }

    // create copy
    std::vector<std::string> copy = input; 
    bool running = true;
    int iter = 0;

    while (running){
        // now that we have border, can treat all relevant cells as the centre
        // loop through whole system except border
        for (unsigned int y = 1; y<input.size()-1; y++){
            for (unsigned int x = 1; x<input[0].size()-1; x++){

                // if empty and all adjacent empty -> become full
                if ( (copy[y][x] == 'L') && (copy[y+1][x] != '#') && (copy[y-1][x] != '#') && (copy[y][x+1] != '#') && (copy[y][x-1] != '#') && (copy[y+1][x+1] != '#') && (copy[y+1][x-1] != '#') && (copy[y-1][x+1] != '#') && (copy[y-1][x-1] != '#') ){
                    input[y][x] = '#';
                }
                // if full and at least 4 surrounding full -> become empty
                else if ( copy[y][x] == '#' ){
                    int full_count = 0;

                    if ( copy[y+1][x]   == '#' ){ full_count++; }
                    if ( copy[y-1][x]   == '#' ){ full_count++; }
                    if ( copy[y][x-1]   == '#' ){ full_count++; }
                    if ( copy[y][x+1]   == '#' ){ full_count++; }
                    if ( copy[y+1][x-1] == '#' ){ full_count++; }
                    if ( copy[y-1][x-1] == '#' ){ full_count++; }
                    if ( copy[y+1][x+1] == '#' ){ full_count++; }
                    if ( copy[y-1][x+1] == '#' ){ full_count++; }

                    if ( full_count >= 4 ){
                        input[y][x] = 'L';
                    }
                }

            }
        }

        if ( input == copy ){

            int tally = 0;

            // simulation has stabilised
            for (unsigned int i=1; i<input.size()-1; i++){
                for (unsigned int j=1; j<input[0].size()-1; j++){

                    if (input[i][j] == '#'){
                        tally++;
                    } 
                }
            }
            
            std::cout << "After " << iter << " iterations." << std::endl;
            std::cout << "Number of occupied seats: " << tally << std::endl;
            running = false;
        }
        else {
            iter++;
            copy = input;
        }
    }


    return 0;
}
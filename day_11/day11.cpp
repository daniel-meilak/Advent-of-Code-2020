#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../utils/utils.h"

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");

    std::cout << "Width:  " << input[0].size() << std::endl;
    std::cout << "Height: " << input.size() << std::endl;
    std::cout << "Number of cells: " << input[0].size()*input.size() << std::endl;

    int max_y = input.size()-1;
    int max_x = input[0].size()-1;

    std::vector<std::string> input_test = input;
    bool simulating = true;
    int iter = 0;

    // while sytem is changing
    while ( simulating ){

        // for each line in input
        for (int y=0;  y<input.size(); y++){
        
            // for each character in line
            for (int x=0; x<input[0].size(); x++){


                if ( y == 0 ){
                    // stuff for right edge
                    if ( x==0 ){
                        // top left
                        if ( (input_test[y][x] == 'L') && (input_test[y][x+1] != '#')  && (input_test[y+1][x] != '#') && (input_test[y+1][x+1] != '#') ){
                            input[y][x] = '#';
                        }
                    }
                    else if ( x==max_x){
                        // top right
                        if ( (input_test[y][x] == 'L') && (input_test[y][x-1] != '#') && (input_test[y+1][x] != '#') && (input_test[y+1][x-1] != '#') ){
                            input[y][x] = '#';
                        }
                    }
                    else {
                        // rest of top
                        if ( (input_test[y][x] == 'L') && (input_test[y][x+1] != '#') && (input_test[y][x-1] != '#') && (input_test[y+1][x] != '#') && (input_test[y+1][x+1] != '#') && (input_test[y+1][x-1] != '#') ){
                            input[y][x] = '#';
                        }
                        else if ( input_test[y][x] == '#' ){
                            int full_cout = 0;

                            if ( input_test[y][x+1]   == '#' ){ full_cout++; }
                            if ( input_test[y][x-1]   == '#' ){ full_cout++; }
                            if ( input_test[y+1][x]   == '#' ){ full_cout++; }
                            if ( input_test[y+1][x+1] == '#' ){ full_cout++; }
                            if ( input_test[y+1][x-1] == '#' ){ full_cout++; }

                            if ( full_cout >= 4 ){
                                input[y][x] = 'L';
                            }
                        }
                    }

                }
                else if ( y = max_y ){
                    // stuff for last line
                    if ( x==0 ){
                        // bottom left
                        if ( (input_test[y][x] == 'L') && (input_test[y][x+1] != '#') && (input_test[y-1][x] != '#') && (input_test[y-1][x+1] != '#') ){
                            input[y][x] = '#';
                        }
                    }
                    else if ( x==max_x){
                        // bottom right
                        if ( (input_test[y][x] == 'L') && (input_test[y][x-1] != '#') && (input_test[y-1][x] != '#') && (input_test[y-1][x-1] != '#') ){
                            input[y][x] = '#';
                        }
                    }
                    else {
                        // rest of bottom
                        if ( (input_test[y][x] == 'L') && (input_test[y][x+1] != '#') && (input_test[y][x-1] != '#') && (input_test[y-1][x] != '#') && (input_test[y-1][x+1] != '#') && (input_test[y-1][x-1] != '#') ){
                            input[y][x] = '#';
                        }
                        else if ( input_test[y][x] == '#' ){
                            int full_cout = 0;

                            if ( input_test[y][x+1]   == '#' ){ full_cout++; }
                            if ( input_test[y][x-1]   == '#' ){ full_cout++; }
                            if ( input_test[y-1][x]   == '#' ){ full_cout++; }
                            if ( input_test[y-1][x+1] == '#' ){ full_cout++; }
                            if ( input_test[y-1][x-1] == '#' ){ full_cout++; }

                            if ( full_cout >= 4 ){
                                input[y][x] = 'L';
                            }
                        }  
                    }                

                }
                else if ( x == 0 ){
                    // stuff for left edge
                    if ( (input_test[y][x] == 'L') && (input_test[y+1][x] != '#') && (input_test[y-1][x] != '#') && (input_test[y][x+1] != '#') && (input_test[y+1][x+1] != '#') && (input_test[y-1][x+1] != '#') ){
                        input[y][x] = '#';
                    }
                    else if ( input_test[y][x] == '#' ){
                        int full_cout = 0;

                        if ( input_test[y+1][x]   == '#' ){ full_cout++; }
                        if ( input_test[y-1][x]   == '#' ){ full_cout++; }
                        if ( input_test[y][x+1]   == '#' ){ full_cout++; }
                        if ( input_test[y+1][x+1] == '#' ){ full_cout++; }
                        if ( input_test[y-1][x+1] == '#' ){ full_cout++; }

                        if ( full_cout >= 4 ){
                            input[y][x] = 'L';
                        }
                    }
                }
                else if ( x == max_x ){
                    // stuff for right edge
                    if ( (input_test[y][x] == 'L') && (input_test[y+1][x] != '#') && (input_test[y-1][x] != '#') && (input_test[y][x-1] != '#') && (input_test[y+1][x-1] != '#') && (input_test[y-1][x-1] != '#') ){
                        input[y][x] = '#';
                    }
                    else if ( input_test[y][x] == '#' ){
                        int full_cout = 0;

                        if ( input_test[y+1][x]   == '#' ){ full_cout++; }
                        if ( input_test[y-1][x]   == '#' ){ full_cout++; }
                        if ( input_test[y][x-1]   == '#' ){ full_cout++; }
                        if ( input_test[y+1][x-1] == '#' ){ full_cout++; }
                        if ( input_test[y-1][x-1] == '#' ){ full_cout++; }

                        if ( full_cout >= 4 ){
                            input[y][x] = 'L';
                        }
                    }
                }
                else {
                    // the rest of the system
                    if ( (input_test[y][x] == 'L') && (input_test[y+1][x] != '#') && (input_test[y-1][x] != '#') && (input_test[y][x+1] != '#') && (input_test[y][x-1] != '#') && (input_test[y+1][x+1] != '#') && (input_test[y+1][x-1] != '#') && (input_test[y-1][x+1] != '#') && (input_test[y-1][x-1] != '#') ){
                        input[y][x] = '#';
                    }
                    else if ( input_test[y][x] == '#' ){
                        int full_cout = 0;

                        if ( input_test[y+1][x]   == '#' ){ full_cout++; }
                        if ( input_test[y-1][x]   == '#' ){ full_cout++; }
                        if ( input_test[y][x-1]   == '#' ){ full_cout++; }
                        if ( input_test[y][x+1]   == '#' ){ full_cout++; }
                        if ( input_test[y+1][x-1] == '#' ){ full_cout++; }
                        if ( input_test[y-1][x-1] == '#' ){ full_cout++; }
                        if ( input_test[y+1][x+1] == '#' ){ full_cout++; }
                        if ( input_test[y-1][x+1] == '#' ){ full_cout++; }

                        if ( full_cout >= 4 ){
                            input[y][x] = 'L';
                        }
                    }
                }
            }
        }
    
        if ( input == input_test){
            int tally = 0;

            for (int y=0;  y<input.size(); y++){
                for (int x=0; x<input[0].size(); x++){
                    
                    if ( input[y][x] == '#' ){
                        tally++;
                    }
                }
            }

            std::cout << "Finished after " << iter << " iterations." << std::endl;
            std::cout << "Occupied seats after simulation: " << tally << std::endl;

            simulating = false;
        }
        else {
            input_test = input;
        }

        iter ++;
    }

    return 0;
}

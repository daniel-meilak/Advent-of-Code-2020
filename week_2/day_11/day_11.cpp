#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input_11");

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

    size_t height = input.size()-1;
    size_t width  = input[0].size()-1;

    // create copy
    std::vector<std::string> copy, save = input; 

    //part1
    while (input != copy){
        
        copy = input;
        
        // now that we have border, can treat all relevant cells as the centre
        // loop through whole system except border
        for (size_t y = 1; y<height; y++){
            for (size_t x = 1; x<width; x++){

                // if empty and all adjacent empty -> become full
                if ( (copy[y][x] == 'L') && (copy[y+1][x] != '#') && (copy[y-1][x] != '#') && (copy[y][x+1] != '#') && (copy[y][x-1] != '#') && (copy[y+1][x+1] != '#') && (copy[y+1][x-1] != '#') && (copy[y-1][x+1] != '#') && (copy[y-1][x-1] != '#') ){
                    input[y][x] = '#';
                }
                // if full and at least 4 surrounding full -> become empty
                else if ( copy[y][x] == '#' ){
                    int full_count = 0;

                    if ( copy[y+1][x  ] == '#' ){ full_count++; }
                    if ( copy[y-1][x  ] == '#' ){ full_count++; }
                    if ( copy[y  ][x-1] == '#' ){ full_count++; }
                    if ( copy[y  ][x+1] == '#' ){ full_count++; }
                    if ( copy[y+1][x-1] == '#' ){ full_count++; }
                    if ( copy[y-1][x-1] == '#' ){ full_count++; }
                    if ( copy[y+1][x+1] == '#' ){ full_count++; }
                    if ( copy[y-1][x+1] == '#' ){ full_count++; }

                    if ( full_count >= 4 ){ input[y][x] = 'L'; }
                }
            }
        }

        //iter++;   
    }

    std::cout << "Answer (part 1): " << grid_count(input,'#') << std::endl;
     
    // reset grid
    input = save;

    while (input != copy){

        copy = input;

        for (size_t y = 1; y<height; y++){
            for (size_t x = 1; x<width; x++){

                // if not seat, ignore position
                if ( copy[y][x] == '.' ){ continue; }

                std::vector<bool> occupied(8,false);
                
                // directions
                size_t a,b;

                // west
                a = x+1;
                while (a!=copy[0].size()-1){

                    if ( copy[y][a] == '#' ){
                        occupied[0] = true;
                        break;
                    }
                    else if (copy[y][a] == 'L'){ break; }
                    a++;
                }

                // east
                a = x-1;
                while (a!=0){

                    if ( copy[y][a] == '#' ){
                        occupied[1] = true;
                        break;
                    }
                    else if (copy[y][a] == 'L'){ break; }
                    a--;
                }

                // north
                a = y-1;
                while (a!=0){

                    if ( copy[a][x] == '#' ){
                        occupied[2] = true;
                        break;
                    }
                    else if (copy[a][x] == 'L'){ break; }
                    a--;
                }

                // south
                a = y+1;
                while (a!=copy.size()-1){

                    if ( copy[a][x] == '#' ){
                        occupied[3] = true;
                        break;
                    }
                    else if (copy[a][x] == 'L'){ break; }
                    a++;
                }

                // north east
                a = y-1;
                b = x+1;
                while (a!=0 && b!=copy[0].size()-1){

                    if (copy[a][b] == '#' ){
                        occupied[4] = true;
                        break;
                    }
                    else if (copy[a][b] == 'L'){ break; }
                    a--;
                    b++;
                }

                // north west
                a = y-1;
                b = x-1;
                while (a!=0 && b!=0){

                    if (copy[a][b] == '#' ){
                        occupied[5] = true;
                        break;
                    }
                    else if (copy[a][b] == 'L'){ break; }
                    a--;
                    b--;
                }

                // south east
                a = y+1;
                b = x+1;
                while (a!=copy.size()-1 && b!=copy[0].size()-1){

                    if (copy[a][b] == '#' ){
                        occupied[6] = true;
                        break;
                    }
                    else if (copy[a][b] == 'L'){ break; }
                    a++;
                    b++;
                }

                // south west
                a = y+1;
                b = x-1;
                while (a!=copy.size()-1 && b!=0){
                    
                    if (copy[a][b] == '#' ){
                        occupied[7] = true;
                        break;
                    }
                    else if (copy[a][b] == 'L'){ break; }
                    a++;
                    b--;
                }

                // tally full seats
                int tally = 0;
                for (bool state : occupied){
                    if (state){ tally++; }
                }

                if ( (copy[y][x] == '#') && (tally >= 5) ){
                    input[y][x] = 'L';
                }
                else if ( (copy[y][x] == 'L') && (tally == 0) ){
                    input[y][x] = '#';
                }
            }
        }
    }

    std::cout << "Answer (part 2): " << grid_count(input,'#') << std::endl;

    return 0;
}
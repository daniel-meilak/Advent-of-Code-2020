#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

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

                // if not seat, ignore position
                if ( copy[y][x] == '.' ){
                    continue;
                }

                std::vector<bool> occupied(8,false);
                
                // directions
                unsigned int a,b;

                // west
                a = x+1;
                while ( true ){

                    if ( copy[y][a] == '#' ){
                        occupied[0] = true;
                        break;
                    }
                    else if (copy[y][a] == 'L'){
                        break;
                    }

                    if ( a == copy[0].size()-1 ){
                        break;
                    }
                    a++;
                }

                // east
                a = x-1;
                while ( true ){

                    if ( copy[y][a] == '#' ){
                        occupied[1] = true;
                        break;
                    }
                    else if (copy[y][a] == 'L'){
                        break;
                    }

                    if ( a == 0 ){
                        break;
                    }
                    a--;
                }

                // north
                a = y-1;
                while ( true ){

                    if ( copy[a][x] == '#' ){
                        occupied[2] = true;
                        break;
                    }
                    else if (copy[a][x] == 'L'){
                        break;
                    }

                    if ( a == 0 ){
                        break;
                    }
                    a--;
                }

                // south
                a = y+1;
                while ( true ){

                    if ( copy[a][x] == '#' ){
                        occupied[3] = true;
                        break;
                    }
                    else if (copy[a][x] == 'L'){
                        break;
                    }

                    if (a == copy.size()-1 ){
                        break;
                    }
                    a++;
                }

                // north east
                a = y-1;
                b = x+1;
                while ( true ){

                    if (copy[a][b] == '#' ){
                        occupied[4] = true;
                        break;
                    }
                    else if (copy[a][b] == 'L'){
                        break;
                    }

                    if ( (a == 0) || (b == copy[0].size()-1) ){
                        break;
                    }
                    a--;
                    b++;
                }

                // north west
                a = y-1;
                b = x-1;
                while ( true ){

                    if (copy[a][b] == '#' ){
                        occupied[5] = true;
                        break;
                    }
                    else if (copy[a][b] == 'L'){
                        break;
                    }

                    if ( (a == 0) || (b == 0) ){
                        break;
                    }
                    a--;
                    b--;
                }

                // south east
                a = y+1;
                b = x+1;
                while ( true ){

                    if (copy[a][b] == '#' ){
                        occupied[6] = true;
                        break;
                    }
                    else if (copy[a][b] == 'L'){
                        break;
                    }

                    if ( (a == copy.size()-1) || (b == copy[0].size()-1) ){
                        break;
                    }
                    a++;
                    b++;
                }

                // south west
                a = y+1;
                b = x-1;
                while ( true ){
                    
                    if (copy[a][b] == '#' ){
                        occupied[7] = true;
                        break;
                    }
                    else if (copy[a][b] == 'L'){
                        break;
                    }

                    if ( (a == copy.size()-1) || (b == 0) ){
                        break;
                    }
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
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"utils.h"

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");

    std::vector<int> seat_id;

    // loop through input
    for (int i=0; i<input.size(); i++){

        std::string line = input[i];
        // loop through line

        int min_row = 0;
        int max_row = 127;
        int min_col = 0;
        int max_col = 7;

        for (int j=0; j<line.size(); j++){

            if (line[j] == 'F'){
                max_row = (max_row+min_row-1)/2;
            }
            else if (line[j] == 'B'){
                min_row = (max_row+min_row+1)/2;
            }
            else if (line[j] == 'L'){
                max_col = (max_col+min_col-1)/2;
            }
            else if (line[j] == 'R'){
                min_col = (max_col+min_col+1)/2;
            }
            else {
                std::cout << "Invalid seat: " << input[i] << std::endl;
                std::exit(EXIT_FAILURE);
            }
        }

        int row    = max_row;
        int column = max_col;

        seat_id.push_back( (row*8)+ column );

    }

    std::cout << "Max id: " << *std::max_element(std::begin(seat_id), std::end(seat_id)) << std::endl;

    return 0;

}
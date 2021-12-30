#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input_05", "");

    std::vector<int> seat_id;
    int part1, part2;

    // loop through input
    for (size_t i=0; i<input.size(); i++){

        std::string &line = input[i];
        size_t size = line.size();

        int min_row = 0;
        int max_row = 127;
        int min_col = 0;
        int max_col = 7;

        // loop through line
        for (size_t j=0; j<size; j++){

            if      (line[j] == 'F'){ max_row = (max_row+min_row-1)/2; }
            else if (line[j] == 'B'){ min_row = (max_row+min_row+1)/2; }
            else if (line[j] == 'L'){ max_col = (max_col+min_col-1)/2; }
            else if (line[j] == 'R'){ min_col = (max_col+min_col+1)/2; }
            else {
                std::cout << "Invalid seat: " << input[i] << std::endl;
                std::exit(EXIT_FAILURE);
            }
        }

        int row    = max_row;
        int column = max_col;

        seat_id.push_back( (row*8)+ column );
    }

    part1 = *std::max_element(std::begin(seat_id), std::end(seat_id));

    // sort the list of ids
    std::sort(seat_id.begin(), seat_id.end());

    size_t seats = seat_id.size();
    for (size_t i=0; i<seats; i++){
        if ( (seat_id[i]+2) == seat_id[i+1] ){ part2 = seat_id[i]+1; }
    }

    std::cout << "Answer (part 1): " << part1 << std::endl;
    std::cout << "Answer (part 2): " << part2 << std::endl;

    return 0;
}
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<regex>
#include"../../utils/utils.h"

// forward function declarations
int neighbours(int tile, int width, std::vector<bool> &grid);
int count(std::vector<bool> &grid);

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");

    // regex to match directions individually
    std::regex direction(R"((nw|sw|ne|se|e|w))");

    // create a square hexagonal system 
    // have to be careful! for part 2, system grows
    // might need to increase your grid 
    int width  = 151;

    // create a hex grid 99*99 as a 1D vector -> 9801 entries
    // initialize vector of bool as true -> white
    std::vector<bool> grid(width*width, true);

    // starting position is in middle, grid[4900]
    int start = (width*width - 1)/2;

    int num_lines = input.size();

    // work through directions and tally movements
    // west = -1, east = 1
    // on an even row: ne=-(width)  , nw=-(width+1), sw=+(width-1), se=+(width)
    // on an odd row : ne=-(width-1), nw=-(width)  , sw=+(width)  , se=+(width+1)
    // first row is row 0!  

    std::vector<int> movements(num_lines, start);
    for ( int i=0; i<num_lines; i++){

        std::sregex_iterator rbegin(input[i].begin(), input[i].end(), direction);
        std::sregex_iterator rend;

        while (rbegin != rend){
            std::string match = rbegin->str();

            // check if current row is even or odd
            if ( (movements[i]/width) % 2 == 0 ){
                if      ( match == "ne" ){ movements[i] += -width  ; }
                else if ( match == "nw" ){ movements[i] += -width-1; }
                else if ( match == "sw" ){ movements[i] +=  width-1; }
                else if ( match == "se" ){ movements[i] +=  width  ; }
                else if ( match == "w"  ){ movements[i] += -1      ; }
                else if ( match == "e"  ){ movements[i] +=  1      ; }
            }
            // if on odd row
            else {
                if      ( match == "ne" ){ movements[i] += -width+1; }
                else if ( match == "nw" ){ movements[i] += -width  ; }
                else if ( match == "sw" ){ movements[i] +=  width  ; }
                else if ( match == "se" ){ movements[i] +=  width+1; }
                else if ( match == "w"  ){ movements[i] += -1      ; }
                else if ( match == "e"  ){ movements[i] +=  1      ; }
            }

            // move to next direction
            rbegin++;
        }

        // make movement and flip tile
        grid[movements[i]] = !grid[movements[i]];
    }

    std::cout << "Answer (part 1): " << count(grid) << std::endl;

    // copy of grid for checking
    std::vector<bool> grid_copy = grid;

    // loop through and flip tiles
    int grid_min = width+1;
    int grid_max = grid.size()-(width+1);
    for (int i=0; i<100; i++){

        // must skip top and bottom edges
        // sides are calc incorrectly however they should not matter
        // as flipped tiles shouldn't reach edge of system
        for (int j=grid_min; j<grid_max; j++){

            // count neighbouring black tiles
            int black_tiles = neighbours(j, width, grid);

            // apply rules
            if (!grid[j]){
                if (black_tiles == 0 || black_tiles > 2){
                    grid_copy[j] = true;
                }
            }
            else {
                if (black_tiles == 2){
                    grid_copy[j] = false;
                }
            }
        }
        // perform flips on original grid
        grid = grid_copy;
    }

    // count number of black tiles in final system
    std::cout << "Answer (part 2): " << count(grid) << std::endl;

    return 0;
}

int neighbours(int tile, int width, std::vector<bool> &grid){

    int count = 0;

    // follows same rules as explained above in part 1
    if ( (tile/width) % 2 == 0 ){
        if (!grid[tile-width  ]){ count++; }
        if (!grid[tile-width-1]){ count++; }
        if (!grid[tile+width-1]){ count++; }
        if (!grid[tile+width  ]){ count++; }
        if (!grid[tile-1      ]){ count++; }
        if (!grid[tile+1      ]){ count++; }
    }
    else {
        if (!grid[tile-width+1]){ count++; }
        if (!grid[tile-width  ]){ count++; }
        if (!grid[tile+width  ]){ count++; }
        if (!grid[tile+width+1]){ count++; }
        if (!grid[tile-1      ]){ count++; }
        if (!grid[tile+1      ]){ count++; }
    }

    return count;
}

// count the black (false) tiles
int count(std::vector<bool> &grid){
    int count = 0;
    
    for (bool tile : grid){
        if (!tile){ count++; }
    }

    return count;
}
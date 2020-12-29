#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<utility>
#include<cstdlib>
#include"../../Utils/utils.h"

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");

    // process input into pair of <string int>
    std::vector<std::pair<char, int>> nav;
    for (std::string line : input){
        nav.push_back({ line[0], std::stoi(line.substr(1)) });
    }

    // store position and direction
    // direction stored as angle on unit cell (east = 0)
    int direction = 0; 
    int x = 0, y = 0;

    // go through instructions;
    for ( auto instruction : nav ){

        switch (instruction.first){

            // Move North
            case 'N':
                y += instruction.second;
                break;
            // Move South
            case 'S':
                y -= instruction.second;
                break;
            // Move East
            case 'E':
                x += instruction.second;
                break;
            // Move West
            case 'W':
                x -= instruction.second;
                break;
            // Turn right (clockwise)
            case 'R':
                direction = (((direction - instruction.second) % 360) + 360) % 360;
                break;
            // Turn left (anticlockwise)
            case 'L':
                direction = (((direction + instruction.second) % 360) + 360) % 360;
                break;
            // Move forward according to current direction
            case 'F':
                if      ( direction == 0   ){ x += instruction.second; }
                else if ( direction == 180 ){ x -= instruction.second; }
                else if ( direction == 90  ){ y += instruction.second; }
                else if ( direction == 270 ){ y -= instruction.second; }
                break;
        }
    }

    std::cout << "Final position: " << "x=" << x << " y=" << y << std::endl;
    std::cout << "Manhattan distance: " << abs(x)+abs(y) << std::endl;

    return 0;
}

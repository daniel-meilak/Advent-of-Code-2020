#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<utility>
#include<cstdlib>
#include<cmath>
#include"../../Utils/utils.h"

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");

    // process input into pair of <string int>
    std::vector<std::pair<char, int>> nav;
    for (std::string line : input){
        nav.push_back({ line[0], std::stoi(line.substr(1)) });
    }

    // store ship and waypoint positions
    // waypoint position is relative to ship
    int ship_x = 0 , ship_y = 0;
    int way_x  = 10, way_y  = 1;

    // pi for rotations
    double pi = 2.0*acos(0.0);

    // go through instructions;
    for ( auto instruction : nav ){

        switch (instruction.first){

            // move waypoint north
            case 'N':
                way_y += instruction.second;
                break;
            // move waypoint south
            case 'S':
                way_y -= instruction.second;
                break;
            // move waypoint east
            case 'E':
                way_x += instruction.second;
                break;
            // move waypoint west
            case 'W':
                way_x -= instruction.second;
                break;
            // Rotate waypoinyt clockwise
            case 'R':{
                double ang = -instruction.second*pi/180.0; // convert to rad
                int x,y;
                x = std::round(way_x*cos(ang) - way_y*sin(ang));
                y = std::round(way_y*cos(ang) + way_x*sin(ang));
                way_x = x;
                way_y = y;
                break;
            }
            // Turn left (anticlockwise)
            case 'L':{
                double ang = instruction.second*pi/180.0; // convert to rad
                int x,y;
                x = std::round(way_x*cos(ang) - way_y*sin(ang));
                y = std::round(way_y*cos(ang) + way_x*sin(ang));
                way_x = x;
                way_y = y;
                break;
            }
            // Move forward according to current direction
            case 'F':
                ship_x += way_x*instruction.second;
                ship_y += way_y*instruction.second;
                break;
        }
    }

    std::cout << "Final position: " << "x= " << ship_x << " y= " << ship_y << std::endl;
    std::cout << "Manhattan distance: " << abs(ship_x)+abs(ship_y) << std::endl;

    return 0;
}

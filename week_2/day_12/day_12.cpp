#include<iostream>
#include<vector>
#include<numbers>
#include<string>
#include<algorithm>
#include<utility>
#include<cstdlib>
#include<cmath>
#include"../../Utils/utils.h"

// forward function declarations
int navigate(const std::vector<std::pair<char, int>> &nav, const bool part2);

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input_12");

    // process input into pair of <string int>
    std::vector<std::pair<char, int>> nav;
    for (std::string line : input){
        nav.push_back({ line[0], std::stoi(line.substr(1)) });
    }

    std::cout << "Answer (part 1): " << navigate(nav,false) << std::endl;
    std::cout << "Answer (part 2): " << navigate(nav,true ) << std::endl;
    
    return 0;
}

int navigate(const std::vector<std::pair<char, int>> &nav, const bool part2){
    
    // store ship and waypoint positions
    // waypoint position is relative to ship
    int direction = 0;
    int ship_x = 0, ship_y = 0;
    int way_x  = 0, way_y  = 0;

    if (part2){
        way_x = 10;
        way_y = 1;
    }

    // go through instructions;
    for (const auto &instruction : nav ){

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
                if (part2){
                    double ang = -instruction.second*std::numbers::pi/180.0; // convert to rad
                    int x,y;
                    x = (int)std::round(way_x*cos(ang) - way_y*sin(ang));
                    y = (int)std::round(way_y*cos(ang) + way_x*sin(ang));
                    way_x = x;
                    way_y = y;
                }
                else { direction = mod(direction-instruction.second,360); }                
                break;
            }
            // Turn left (anticlockwise)
            case 'L':{
                if (part2){
                    double ang = instruction.second*std::numbers::pi/180.0; // convert to rad
                    int x,y;
                    x = (int)std::round(way_x*cos(ang) - way_y*sin(ang));
                    y = (int)std::round(way_y*cos(ang) + way_x*sin(ang));
                    way_x = x;
                    way_y = y;
                }
                else { direction = mod(direction+instruction.second,360); }
                break;
            }
            // Move forward according to current direction
            case 'F':
                if (part2){
                    ship_x += way_x*instruction.second;
                    ship_y += way_y*instruction.second;
                }
                else {
                    if      ( direction == 0   ){ way_x += instruction.second; }
                    else if ( direction == 180 ){ way_x -= instruction.second; }
                    else if ( direction == 90  ){ way_y += instruction.second; }
                    else if ( direction == 270 ){ way_y -= instruction.second; }
                }
                break;
        }
    }

    int answer;
    if (part2){ answer = manhattan(ship_x,ship_y);  }
    else      { answer = manhattan(way_x,way_y); }

    return answer;
}
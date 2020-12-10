#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"utils.h"

int main(){

    // read input into vector of ints.
    std::vector<int> input = input_to_int(read_input("input", ""));

    // sort plugs
    std::sort(input.begin(), input.end());

    // difference counter
    // number of 1 jold diff stored in [0], 2 jolt in [1] and 3 jolt in [2]
    std::vector<int> diff = {0,0,0};

    // first adapter has 1 jolt diff and last to appliance has 3
    diff[0]++;
    diff[2]++;

    for ( int i=1; i<input.size(); i++ ){

        int step = input[i]-input[i-1];

        if ( step == 1 ){
            diff[0]++;
        }
        else if ( step == 2 ){
            diff[1]++;
        }
        else if (step == 3 ){
            diff[2]++;
        }
        else {
            std::cout << "Difference between adaptors " << i-1 << " and " 
                      << i << " is too high (" << step << ")" << std::endl; 
        }
    }

    std::cout << "Step differences: " << std::endl;
    std::cout << "1: " << diff[0] << std::endl;
    std::cout << "2: " << diff[1] << std::endl;
    std::cout << "3: " << diff[2] << std::endl << std::endl;
    std::cout << "Key: " << diff[0]*diff[2] << std::endl;

    return 0;
}

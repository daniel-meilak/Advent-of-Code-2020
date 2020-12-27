#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../utils/utils.h"

int main(){

    // read input into vector of ints.
    std::vector<int> input = input_to_int(read_input("input", ""));

    // add socket to input
    input.push_back(0);

    // sort plugs
    std::sort(input.begin(), input.end());

    // add appliance to input
    input.push_back(input[input.size()-1]+3);
    
    // vector of differences
    std::vector<int> diff;

    // find difference between each adaptor and store in diff
    for (unsigned int i=1; i<input.size(); i++){
        diff.push_back(input[i]-input[i-1]);
    }

    // number of 1 and 3 differences
    int diff_1 = std::count(diff.begin(), diff.end(), 1);
    int diff_3 = std::count(diff.begin(), diff.end(), 3);

    // output answer
    std::cout << "Answer (part 1): " << diff_1*diff_3 << std::endl;

    // consecutive diff vector
    std::vector<int> consecutive;

    int count = 1;
    // find consecutive differences
    for (unsigned int i=1; i<diff.size(); i++){

        // ignore 3's 
        if ( diff[i] == 3 ){
            continue;
        }

        // count consecutive 1's
        if ( diff[i] == diff[i-1] ){
            count++;
        }
        else {
            consecutive.push_back(count);
            count = 1;
        }
    }
    consecutive.push_back(count);

    // there is only 1 way to pass through differences of 3 (all paths pass through)
    // there are 7 ways to pass through 4 consecutive 1's
    // there are 4 ways to pass through 3 consecutive 1's
    // there are 2 ways to pass through 2 consecutive 1's
    
    long long int sum = 1;

    for (int num : consecutive){

        if ( num == 4 ){
            sum *= 7;
        }
        else if ( num == 3 ){
            sum *= 4;
        }
        else if ( num == 2 ){
            sum *= 2;
        }
    }

    std::cout << "Answer (part 2): " << sum << std::endl;

    return 0;
}

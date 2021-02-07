#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

int main(){

    // read input into vector of long long ints.
    std::vector<long long int> input = input_to_llint(read_input("input", ""));
    size_t size = input.size();

    // bool vector to check if we have found sum
    std::vector<bool> check(size, false);

    // starting from value 25, find two numbers in past 25 that sum to current
    for (size_t i=25; i<size; i++){

        // get two numbers, a and b, in past 25
        for (size_t a=(i-25); a<(i-1); a++){
            for (size_t b=(a+1); b<i; b++){
                
                // if input[a] and input[b] sum to current number, found summation
                if ( (input[a] + input[b]) == input[i] ){ check[i] = true; }
            }
        }
    }

    // for part two, save the number
    long long part1, part2;
    int invalid_index;

    // loop through check looking for false value (invalid number)
    for (size_t i=25; i<size; i++){

        if ( !check[i] ){
            part1 = input[i];
            invalid_index = i;
        }
    }


    // part two
    long long int sum = 0;
    int min = 0;

    // loop from index 0 to invalid number
    for ( int i=0; i<invalid_index; i++){

        // add together numbers until the value of invalid number is reacher or exceeded
        sum += input[i];

        if ( sum == part1 ){
            
            // add together min and max value in range to find "encryption weakness"
            long long int min_val = *std::min_element(input.begin()+min, input.begin()+i);
            long long int max_val = *std::max_element(input.begin()+min, input.begin()+i);
            
            part2 = min_val+max_val;
            break;
        }
        else if (sum > part1){

            // increase min
            min++;

            // restart from new min and reset sum
            i = min-1;
            sum = 0;
        }
    }

    std::cout << "Answer (part 1): " << part1 << std::endl;
    std::cout << "Answer (part 2): " << part2 << std::endl;

    return 0;
}

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"utils.h"

int main(){

    // read input into vector of long long ints.
    std::vector<long long int> input = input_to_llint(read_input("input", ""));

    // bool vector to check if we have found sum
    std::vector<bool> check(input.size(), false);

    // starting from value 25, find two numbers in past 25 that sum to current
    for (int i=25; i<input.size(); i++){

        // get two numbers, a and b, in past 25
        for (int a=(i-25); a<(i-1); a++){
            for (int b=(a+1); b<i; b++){
                
                // if input[a] and input[b] sum to current number, found summation
                if ( (input[a] + input[b]) == input[i] ){
                    check[i] = true;
                }
            }
        }
    }

    // output numbers that dont have sum in last 25 numbers
    std::cout << "No sum numbers: " << std::endl;

    // for part two, save the number
    long long int invalid;
    int invalid_index;

    // loop through check looking for false value (invalid number)
    for (int i=25; i<check.size(); i++){

        if ( !check[i] ){
            std::cout << i+1 << ") " << input[i] << std::endl;
            invalid = input[i];
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

        if ( sum == invalid ){
            std::cout << "Min index: " << min+1 << " Value: " << input[min] << std::endl;
            std::cout << "Max index: " << i+1   << " Value: " << input[i]   << std::endl;
            
            // add together min and max value in range to find "encryption weakness"
            long long int min_val = *std::min_element(input.begin()+min, input.begin()+i);
            long long int max_val = *std::max_element(input.begin()+min, input.begin()+i);
            
            std::cout << "Encryption weakness: " << min_val+max_val << std::endl;
            break;
        }
        else if (sum > invalid){

            // increase min
            min++;

            // restart from new min
            i = min-1;

            // reset sum
            sum = 0;
        }
    }

    return 0;
}

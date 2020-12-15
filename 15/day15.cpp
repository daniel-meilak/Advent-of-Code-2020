#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<list>
#include<chrono>
#include<unordered_map>
#include<map>
#include"../utils/utils.h"

int main(){

    // read input into vector of strings.
    std::vector<int> input = input_to_int(read_input("input", ","));

    // vector or list to store sequence
    std::vector<int> sequence;
    //std::list<int> sequence;

    // (unordered) map to store terms and the pos of last occurence
    //std::unordered_map<int,int> last_occurence;
    std::map<int,int> last_occurence;

    // fill initial sequence from input
    for ( int i=0; i<input.size()-1; i++ ){
        sequence.push_back(input[i]);
        last_occurence[input[i]] = i;
    }
    sequence.push_back(input.back());

    int sequence_length = 30000000;
    int last_term = input.back();

    // keep initial time
    auto t1 = std::chrono::high_resolution_clock::now();

    // continue sequence till sequence_length
    for ( int i=input.size()-1; i<sequence_length-1; i++ ){

        // has the term occured before
        auto it = last_occurence.find(last_term);

        // if it hasnt occured add a 0 to sequence
        if ( it == last_occurence.end() ){
            //sequence.push_back(0);
            last_occurence[last_term] = i;
            last_term = 0;
        }
        // if it has occured add the number of terms since last to seq
        else {
            int new_value = i-last_occurence[it->first];
            //sequence.push_back(new_value);
            last_occurence[it->first] = i;
            last_term = new_value;
        }
    }

    // keep final time
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();

    std::cout << "Term 30000000: " << sequence.back() << std::endl;

    // print calc time for comparing map, unordered_map, vector, list usage
    std::cout << duration << std::endl;    

    return 0;
}

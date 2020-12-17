#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<map>
#include<list>
#include"../utils/utils.h"

int main(){

    // read input into vector of ints.
    std::vector<int> input = input_to_int(read_input("input", ""));

    // sort plugs
    std::sort(input.begin(), input.end());

    int appliance_jolt = input[input.size()-1]+3;

    // add socket and appliance to vector
    input.push_back(appliance_jolt);
    input.insert(input.begin(), 0);

    

    // create a map of adaptors and the sockets they link to
    std::map<int, std::vector<int>> adaptor_links;

    // add three extra adaptors that dont link to anything 
    // to make map creation easier
    input.push_back(1000);
    input.push_back(1100);
    input.push_back(1200);

    // add all adaptors and their possible connections to adaptor_links
    for ( int i = 0; i<input.size()-3; i++ ){
        
        // add adaptor
        adaptor_links[input[i]] = {};

        // add links (possibilities are the 3 next adaptors)
        for ( int j = i+1; j<= i+3; j++){
            if ( (input[j]-input[i]) <= 3 ){
                adaptor_links[input[i]].push_back(input[j]);
            }
        }
    }

    // tally paths
    long long int num_paths = 0;
    // list of paths
    // better than vector as we only access first and last member
    std::list<int> possible_paths = {0};

    while ( possible_paths.size() > 0 ){

        // if the path gets to the end, incr path counter
        // remove path and continue;
        if ( possible_paths.front() == appliance_jolt ){
            num_paths++;
            possible_paths.pop_front();
            continue;
        }

        // for each node in path, add branches to path list
        for (int adaptor : adaptor_links[possible_paths.front()]){
            possible_paths.push_back(adaptor);
        }

        // once node is exhausted, remove from path list
        possible_paths.pop_front();
    }

    std::cout << "Number of possible adapter chains: " << num_paths << std::endl;

    return 0;
}

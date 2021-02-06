#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<map>
#include<utility>
#include<list>
#include"../../Utils/utils.h"

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "" );

    std::map<std::string, std::vector<std::pair<std::string, int>>> rules;

    // parse input
    for (const std::string &line : input){

        // search for " contains"
        size_t pos1 = line.find(" contain");

        // add bag rule to rules
        std::string bag = line.substr(0, pos1);
        rules[bag] = {};
        
        // if bag rule is empty go to next line
        if ( line.find("no") != std::string::npos ){ continue; }

        // move pos marker behind number
        pos1 += 7;

        // check for "," and create marker at it
        size_t pos2 = line.find(",");

        int num;
        std::string content;

        while ( pos2 != std::string::npos ){

            // store number 
            num = std::stoi(line.substr(pos1+2,1));

            // store bag contained
            content = line.substr(pos1+4,pos2-(pos1+4));

            // all bag names end in [...] bags (not [...] bag)
            if (content.back() != 's'){ content.push_back('s'); }

            rules[bag].push_back({content, num});

            // set pos1 to pos2 and find next comma
            pos1 = pos2;
            pos2 = line.find(",", pos2+1);
        }

        // add final content
        num = std::stoi(line.substr(pos1+2,1));
        content = line.substr(pos1+4, line.size()-(pos1+5));
        if (content.back() != 's'){ content.push_back('s'); }
        rules[bag].push_back({content, num});        
    }

    // part 1
    int num_bags1 = 0;

    // loop through map keys
    for (auto const& bag : rules){
        
        // we only care about other bags that contain shiny gold bags
        if (bag.first == "shiny gold bags"){ continue; }

        // lists are a little faster than vectors since we only access first and last elements
        std::list<std::string> possible_bags = {bag.first};

        // while we still have bags to look through
        while (!possible_bags.empty()){
            std::string test_bag = possible_bags.front();
            possible_bags.pop_front();

            // if we find gold bag move on
            if ( test_bag == "shiny gold bags" ){
                num_bags1++;
                break;
            }

            // look through bags in test_bag
            for (const auto &pair : rules[test_bag]){
                possible_bags.push_back(pair.first);
            }      
        }
    }

    std::cout << "Answer (part 1): " << num_bags1 << std::endl;

    // part 2 
    int num_bags2 = 0;

    std::list<std::pair<std::string, int>> possible_bags;
    possible_bags.push_back({"shiny gold bags",1});

    while (!possible_bags.empty()){
        std::pair<std::string, int> test_bag = possible_bags.front();
        possible_bags.pop_front();

        num_bags2 += test_bag.second;

        // add the bags in test_bag
        for (const auto &contents: rules[test_bag.first]){
            possible_bags.push_back({contents.first, contents.second*test_bag.second});
        }
    }

    // remove shiny gold bag from number
    num_bags2--;

    std::cout << "Answer (part 2): " << num_bags2 << std::endl;

    return 0;
}


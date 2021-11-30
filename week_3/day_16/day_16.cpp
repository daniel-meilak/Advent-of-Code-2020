#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<regex>
#include<unordered_map>
#include<cstdlib>
#include"../../Utils/utils.h"

class rule_t{
public:
    std::string name;
    std::vector<int> low;
    std::vector<int> high;
};

// forward function declarations
bool count(const std::vector<bool> &vec, int &n);

int main(){

    // read rules into vector of strings.
    std::vector<std::string> rule_list = read_input("rules", "");

    // vector of rules
    std::vector<rule_t> rules;

    // regex for rule name and values
    std::regex name("^[a-z ]+");
    std::regex value("([0-9]+)-([0-9]+) or ([0-9]+)-([0-9]+)");

    // mathing strings
    std::smatch matches;

    for ( std::string line : rule_list ){

        // new rule 
        rule_t rule;

        // match name;
        std::regex_search(line, matches, name);
        rule.name = matches[0];

        std::regex_search(line, matches, value);
        rule.low.push_back(std::stoi(matches[1]));
        rule.low.push_back(std::stoi(matches[2]));
        rule.high.push_back(std::stoi(matches[3]));
        rule.high.push_back(std::stoi(matches[4]));

        rules.push_back(rule);
    }
    
    // read nearby tickets
    std::vector<int> tickets_together = input_to_int<int>(read_input("nearby_tickets",","));
    std::vector<std::vector<int>> tickets;
    std::vector<int> single;
    

    // sort tickets into vector of vector
    for (size_t i=0; i<tickets_together.size(); i++){
        single.push_back(tickets_together[i]);
        if ( single.size() == 20 ){
            tickets.push_back(single);
            single.clear();
        }
    }

    long error_rate = 0;

    // check for invalid entries in each ticket
    for (size_t k=0; k<tickets.size(); k++){
        for (size_t i=0; i<tickets[i].size(); i++){

            // check ticket i
            int val = tickets[k][i];
            bool validity = false;

            // check against every rule 
            for (size_t j=0; j<rules.size(); j++){

                // invalid if less the lower min or higher max or higher than low max and lower than high min
                if ( (val>=rules[j].low[0] && val<=rules[j].low[1]) || (val>=rules[j].high[0] && val<=rules[j].high[1]) ){
                    validity = true;
                    break;
                }
            }

            // if a ticket entry is invalid, remove the ticket
            if ( !validity ){
                tickets.erase(tickets.begin()+k);
                k--;

                error_rate += val;
            }
        }
    }

    std::cout << "Answer (part 1): " << error_rate << std::endl;

    // vector of booleans for each rule column applies to
    size_t size = rules.size();
    std::vector<std::vector<bool>> validity(size,std::vector<bool>(size,true));

    // loop through columns of data in tickets
    for (size_t i=0; i<tickets[0].size(); i++){
        for (size_t j=0; j<tickets.size(); j++){

            int val = tickets[j][i];

            // loop through rules
            for (size_t k=0; k<rules.size(); k++){

                // invalid if less the lower or higher than max or higher than low max and lower than high min
                if (val<rules[k].low[0] || val>rules[k].high[1] || (val>rules[k].low[1] && val<rules[k].high[0])){ validity[i][k] = false; }
            }
        }
    }

    // map of rule and column
    std::unordered_map<int,int> link;

    // while we haven't reduced each column to one rule
    while(link.size()<20){

        for (size_t i=0; i<validity.size(); i++){
            int n;

            // if colump applies to one rule and not already resolved
            if (count(validity[i],n) && !link.contains(n)){

                // save rule column link
                link[n] = (int)i;

                // remove rule from other columns
                for (size_t j=0; j<validity.size(); j++){
                    validity[j][n] = false;
                }
            }
        }
    }

    // multiply together departure fields in my ticket
    std::vector<long long> my = input_to_int<long long>(read_input("my_ticket",","));
    long long part2 = my[link[0]]*my[link[1]]*my[link[2]]*my[link[3]]*my[link[4]]*my[link[5]];

    std::cout << "Answer (part 2): " << part2 << std::endl;    

    return 0;
}

bool count(const std::vector<bool> &vec, int &n){

    size_t size = vec.size();
    int c = 0;

    for (size_t i=0; i<size; i++){
        if (vec[i]){
            c++;
            n=(int)i;
        }
    }

    return c==1;
}
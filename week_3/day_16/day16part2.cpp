#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<regex>
#include<cstdlib>
#include"../../utils/utils.h"

class rule_t{
public:
    std::string name;
    std::vector<int> low;
    std::vector<int> high;
};

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
    std::vector<int> tickets_together = input_to_int(read_input("nearby_tickets",","));
    std::vector<std::vector<int>> tickets;
    std::vector<int> single;

    // sort tickets into vector of vector
    for (unsigned int i=0; i<tickets_together.size(); i++){
        single.push_back(tickets_together[i]);
        if ( single.size() == 20 ){
            tickets.push_back(single);
            single.clear();
        }
    }

    // check for invalid entries in each ticket
    for (unsigned int k=0; k<tickets.size(); k++){
        for (unsigned int i=0; i<tickets[i].size(); i++){

            // check ticket i
            int val = tickets[k][i];
            bool validity = false;

            // check against every rule 
            for (unsigned int j=0; j<rules.size(); j++){

                // if it is less the lower min or higher max -> invalid
                if ( (val >= rules[j].low[0]) && (val <= rules[j].low[1]) ){
                    validity = true;
                    break;
                }
                // if it is higher than low max and lower than high min -> invalid
                else if ( (val >= rules[j].high[0]) && (val <= rules[j].high[1]) ){
                    validity = true;
                    break;
                }
            }

            // if a ticket entry is invalid, remove the ticket
            if ( !validity ){
                tickets.erase(tickets.begin()+k);
                k--;
            }
        }
    }

    // loop through columns of data in tickets
    for (unsigned int i=0; i<tickets[0].size(); i++){

        // vector of booleans for each rule column applies to
        std::vector<bool> validity(rules.size(),true);

        for (unsigned int j=0; j<tickets.size(); j++){

            int val = tickets[j][i];

            // loop through rules
            for (unsigned int k=0; k<rules.size(); k++){

                // if it is less the lower min or higher max -> invalid
                if ( (val < rules[k].low[0]) || (val > rules[k].high[1]) ){
                    validity[k] = false;
                }
                // if it is higher than low max and lower than high min -> invalid
                else if ( (val > rules[k].low[1]) && (val < rules[k].high[0]) ){
                    validity[k] = false;
                }
            }
        }

        // print each rule column applies to
        std::cout << "Column " << i+1 << " applies to " << std::count(validity.begin(), validity.end(), true) << " rule(s)\t";  
        for (unsigned int r=0; r<validity.size(); r++){
            if ( validity[r] ){ std::cout << r+1 << "\t"; }
        }
        std::cout << std::endl;

        
    }
    

    return 0;
}

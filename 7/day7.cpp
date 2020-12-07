#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"utils.h"

class bag{
    public:
        bag(std::string name):name(name){};

        std::string name;
        std::vector<bag*> contains;
};

int main(){

    // read input into vector of strings.
    //std::vector<std::string> input = read_input("input", "" );

    bag red("red");
    bag yellow("yellow");

    red.contains.push_back(&yellow);

    return 0;
}

// class baggage{
//     public:
//         baggage(std::string name, std::vector<std::string> contents){
//             this->name=name;
//             this->contents=contents;
//         }

//         std::string name;
//         std::vector<std::string> contents;
// };


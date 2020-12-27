#include<iostream>
#include<list>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../utils/utils.h"

void copy_range_cyclic(std::list<int> &input, std::list<int>::iterator it, std::list<int> &output, int n);
void advance_cyclic(std::list<int> &input, std::list<int>::iterator &it, int n);

int main(){

    std::list<int> input = {7,9,2,8,4,5,1,3,6};
    //std::list<int> input = {3,8,9,1,2,5,4,6,7};

    int max_num = input.size();

    // iterator to starting value
    auto it = input.begin();

    int iter = 100;

    for (int i=0; i<iter; i++){
        // vector to store pciked up cards
        std::list<int> hand;

        // iterators for copy
        auto copy_begin = it;
        advance_cyclic(input, copy_begin, 1);

        // copy and remove next three cups
        copy_range_cyclic(input, copy_begin, hand, 3);

        // destination is current label -1
        int dest = *it -1;

        // if destination is 0, loop back round
        if (dest == 0){
            dest += max_num;
        }

        // if destination is in hand, keep decrimenting
        while ( std::find(hand.begin(), hand.end(), dest) != hand.end() ){
            dest--;
            if (dest == 0){
                dest += max_num;
            }
        }

        // insert hand into destination
        auto dest_it = std::find(input.begin(), input.end(), dest);
        advance_cyclic(input, dest_it, 1);
        input.insert(dest_it, hand.begin(), hand.end());
    
        // move current cup forward
        advance_cyclic(input, it, 1);
    }

    it = std::find(input.begin(), input.end(), 1);
    std::string answer;
    for (int i=0; i<8; i++){
        advance_cyclic(input, it, 1);
        answer.push_back(*it + '0');
    }

    std::cout << "Answer: " << answer << std::endl;

    return 0;
}

// copy n elements in input starting from iter to output and remove from input
void copy_range_cyclic(std::list<int> &input, std::list<int>::iterator it, std::list<int> &output, int n){

    for (int i=0; i<n; i++){
        output.push_back(*it);
        if ( *it == input.back() ){
            input.erase(it);
            it = input.begin();
        }
        else {
            it = input.erase(it);
        }
    }
}

// advance list iter by n, in a cyclic list
void advance_cyclic(std::list<int> &input, std::list<int>::iterator &it, int n){
    for (int i=0; i<n; i++){
        if ( *it == input.back() ){
            it = input.begin();
        }
        else {
            it++;
        }
    }
}
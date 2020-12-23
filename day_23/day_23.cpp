#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../utils/utils.h"

void copy_loop(std::vector<int> &input, std::vector<int>::iterator first, int n, std::vector<int> &result);
void erase_loop(std::vector<int> &input, std::vector<int>::iterator first, int n);
void incr_iter_loop(std::vector<int> &input, std::vector<int>::iterator &it);

int main(){

    std::vector<int> input = {7,9,2,8,4,5,1,3,6};
    //std::vector<int> input = {3,8,9,1,2,5,4,6,7};

    // for (int i=10; i<=1000000; i++){
    //     input.push_back(i);
    // }

    int max_num = input.size();

    // iterator to starting value
    auto it = input.begin();
    int current_val = *it;

    int iter = 100;

    for (int i=0; i<iter; i++){
        // vector to store pciked up cards
        std::vector<int> hand;

        // copy of next position
        auto next_it = it;
        incr_iter_loop(input, next_it);

        // pick up cups
        copy_loop(input, next_it, 3, hand);

        // remove cups from input
        erase_loop(input, next_it, 3);

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
                dest += 9;
            }
        }

        // insert hand into destination
        auto dest_it = std::find(input.begin(), input.end(), dest);
        incr_iter_loop(input, dest_it);
        input.insert(dest_it, hand.begin(), hand.end());
    
        // move current cup forward
        it = std::find(input.begin(), input.end(), current_val);
        incr_iter_loop(input, it);
        current_val = *it;
    }

    it = std::find(input.begin(), input.end(), 1);
    std::string answer;
    for (int i=0; i<8; i++){
        incr_iter_loop(input, it);
        answer.push_back(*it + '0');
    }

    std::cout << "Answer: " << answer << std::endl;

    return 0;
}

// copy_n but loops if iterator reaches end 
void copy_loop(std::vector<int> &input, std::vector<int>::iterator first, int n, std::vector<int> &result){
    result.resize(n);
    auto it = result.begin();
    while (n>0){
        *it = *first;
        ++it;
        if ( first+1 == input.end() ){
            first = input.begin();
        }
        else {
            ++first;
        }
        --n;
    }
}

// vector.erase but removes elements from beginning if range goes over vector.end()
void erase_loop(std::vector<int> &input, std::vector<int>::iterator first, int n){
    int distance = std::distance(first, input.end());
    if ( n >= distance ){
        input.erase(first, input.end());
        input.erase(input.begin(), input.begin()+(n-distance));
    }
    else {
        input.erase(first, first+n);
    }
}

// increment iterator through cyclic vector (incrementing above vector.end() allowed)
void incr_iter_loop(std::vector<int> &input, std::vector<int>::iterator &it){

    if (it+1 == input.end()){
        it = input.begin();
    }
    else {
        ++it;
    }
}
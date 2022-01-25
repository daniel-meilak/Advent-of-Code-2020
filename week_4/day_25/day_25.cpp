#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"utils.h"

long long handshake( long long subject_number, long long loop_size );

int main(){

    // read input into vector of strings.
    std::vector<int> input = input_to_int(read_input("input_25"));

    // specific loop values for door and card
    int card_loop{0};

    int loop_max = 100000000;
    int subject_number = 7;
    int modulus = 20201227;

    // trial public key and bool for ending loop
    int public_key = 1;
    bool card_found = false, door_found = false;

    for (int i=1; i<loop_max; i++){

        public_key *= subject_number;
        public_key  = public_key % modulus;

        if ( public_key == input[0] ){
            card_loop = i;
            card_found = true;
        }
        else if ( public_key == input[1] ){
            door_found = true;
        }

        // if both keys are found, break
        if (card_found && door_found){ break; }
    }

    long long encryption_key = handshake(input[1], card_loop);

    std::cout << "Answer (part 1): " << encryption_key << std::endl;

    return 0;
}

long long handshake( long long subject_number, long long loop_size ){

    long long output = 1ULL;

    for (int i=0; i<loop_size; i++){
        output *= subject_number;
        output = output % 20201227ULL;
    }

    return output;
}
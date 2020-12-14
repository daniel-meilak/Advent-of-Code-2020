#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../utils/utils.h"

int find_address( std::string line );
long int find_value( std::string line );
void apply_mask( long int &value, std::string mask );
void set_bit(long int &num, int position);
void clear_bit(long int &num, int position);

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");

    // initialize memory vector (size 100k, 0 initial)
    std::vector<long int> memory(100000,0);

    // place to hold the current mask
    std::string mask;

    // work through input
    for ( std::string line : input ){

        // check line for mask or memory address
        std::string instruction = line.substr(0,3);  

        // if mask, change mask
        if ( instruction == "mas" ){
            mask = line.substr(7);
        }
        // otherwise add to memory
        else {

            // store address and value
            int address      = find_address(line);
            long int value   = find_value(line);

            // mask value
            apply_mask(value, mask);

            // insert into memory
            memory[address] = value;
        }
    }

    // answer is sum of all memory values
    long int sum = 0;
    for ( long int value : memory){
        sum += value; 
    }

    std::cout << "Answer (part 1): " << sum << std::endl;

    return 0;
}

void apply_mask( long int &value, std::string mask ){

    for (int i=0; i<mask.size(); i++){

        if ( mask[i] == 'X' ){
            continue;
        }
        else if ( mask[i] == '1' ){
            set_bit(value, (mask.size()-i)-1 );
        }
        else if ( mask[i] == '0' ){
            clear_bit(value, (mask.size()-i)-1 );
        }
    }
}

void set_bit(long int &num, int position)
{
	long int mask = 1UL << position;
	num =  num | mask;
}

void clear_bit(long int &num, int position)
{
	long int mask = 1UL << position;
	num = num & ~mask;
}

int find_address( std::string line ){

    int pos = line.find(']');

    return std::stoi(line.substr(4, pos-4));
}

long int find_value( std::string line ){

    int pos = line.find('=');

    return std::stoi(line.substr(pos+2));
}
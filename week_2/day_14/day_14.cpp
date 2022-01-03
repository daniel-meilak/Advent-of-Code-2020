#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<bitset>
#include<list>
#include<map>
#include"../../Utils/utils.h"

// forward function declarations
long int find_address( std::string line );
long int find_value( std::string line );
std::vector<long int> apply_mask2( long int &value, std::string mask );
std::vector<long int> floating_binary( std::string line );
void apply_mask( long int &value, std::string mask );
void set_bit( long int &num, long int position );
void clear_bit( long int &num, long int position );
long long mask(const std::vector<std::string> &input, const bool part2);

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input_14");

    std::cout << "Answer (part 1): " << mask(input,false) << std::endl;
    std::cout << "Answer (part 2): " << mask(input,true ) << std::endl;

    return 0;
}

long long mask(const std::vector<std::string> &input, const bool part2){
    
    // Memory map (cant use 0-size as too large)
    std::map<long int, long int> memory;

    // place to hold the current mask
    std::string mask;

    // total to hold answer
    long long total = 0;

    // work through input
    for ( std::string line : input ){

        // check line for mask or memory address
        std::string instruction = line.substr(0,3);  

        // if mask, change mask
        if ( instruction == "mas" ){ mask = line.substr(7); }

        // otherwise add to memory
        else {

            // store address and value
            long int address = find_address(line);
            long int value   = find_value(line);


            if (part2){
                // find the floating addresses
                std::vector<long int> floating_address = apply_mask2(address,mask);

                // add values to memory map
                for ( long int index : floating_address ){
                    memory[index] = value;
                }
            }
            else {
                // mask value
                apply_mask(value, mask);
                // insert into memory
                memory[address] = value;
            }
        }
    }

    // loop through memory map and add keys (memory values)
    for ( auto const &entry : memory){
        total += entry.second;
    }

    return total;
}

// apply mask to a value
// 1 sets value to 1
// 0 sets value to 0
// X does nothing
void apply_mask( long int &value, std::string mask ){

    for (unsigned int i=0; i<mask.size(); i++){

        if ( mask[i] == 'X' ){ continue; }
        else if ( mask[i] == '1' ){ set_bit(value, (mask.size()-i)-1 ); }
        else if ( mask[i] == '0' ){ clear_bit(value, (mask.size()-i)-1 ); }
    }
}


// apply mask to a value
// 1 sets value to 1
// 0 does nothing
// X creates floating values which need to be resolved
std::vector<long int> apply_mask2( long int &value, std::string mask ){

    // conver address to binary (string)
    std::string binary = std::bitset<36>(value).to_string();

    for (unsigned int i=0; i<mask.size(); i++){

        // if mask bit == 'X' set address bit to 'X'
        if ( mask[i] == 'X' ){ binary[i] = 'X'; }
        // if mask bit == '1' set address bit to '1'
        else if ( mask[i] == '1' ){ binary[i] = '1'; }
        // if mask bit == '0' do nothing
    }

    // resolve 'X's in value
    return floating_binary(binary);
}


// finds the floating values such that string 'XX'
// become vector<string> {'11','10','01','00'}
// which is converted to vector<int> {3,2,1,0}
std::vector<long int> floating_binary( std::string line ){

    // combinations holds string, values int version
    std::vector<std::string> combinations;
    std::vector<long int> values;

    // key holds unresolved values (contain 'X')
    std::list<std::string> key;
    key.push_back(line);

    // while values remain unresolved (containing 'X')
    while ( key.size() > 0 ){
        
        // find the next 'X'
        size_t pos = key.front().find('X');
        // if value doesnt contain 'X' add to finished list and remove
        if ( pos == std::string::npos ){
            combinations.push_back(key.front());
            key.pop_front();
            continue;
        }

        // resolve current 'X' to a '0' and '1'
        // and add these back to the key incase more 'X' left over
        key.front()[pos] = '0';
        key.push_back(key.front());

        key.front()[pos] = '1';
        key.push_back(key.front());

        // remove partially resolved value
        key.pop_front();
    }

    // change values from binary (string) to int
    for ( std::string binary : combinations ){
        values.push_back(std::bitset<36>(binary).to_ulong());
    }

    return values;
}

// set bit at position to 1
void set_bit(long int &num, long int position)
{
	long int mask = 1UL << position;
	num =  num | mask;
}

// clear bit at position to 0
void clear_bit(long int &num, long int position)
{
	long int mask = 1UL << position;
	num = num & ~mask;
}

// exctract address from line
long int find_address( std::string line ){

    size_t pos = line.find(']');

    return std::stol(line.substr(4, pos-4));
}

// extract value from line
long int find_value( std::string line ){

    size_t pos = line.find('=');

    return std::stoi(line.substr(pos+2));
}
#ifndef UTILS_H
#define UTILS_H

#include<vector>
#include<string>

// read input file into vector of strings
std::vector<std::string> read_input(std::string file_name, std::string separator);

// convert strings vector to other types
std::vector<int> input_to_int(std::vector<std::string> input);
std::vector<long long int> input_to_llint(std::vector<std::string> input);
std::vector<double> input_to_double(std::vector<std::string> input);

// binary and decimal converters
int binary_to_decimal( int binary );
int decimal_to_binary( int decimal );

#endif /* UTILS_H */

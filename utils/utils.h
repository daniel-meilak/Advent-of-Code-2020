#ifndef UTILS_H
#define UTILS_H

#include<vector>
#include<string>

// read input file into vector of strings
std::vector<std::string> read_input(std::string file_name, std::string separator);

// read input file into 2D vector or vectors
std::vector<std::vector<std::string>> read_input_2D(std::string file_name, std::string separator);

// separate input into multiple vectors according to delimiter spacing
std::vector<std::vector<std::string>> split_input(std::vector<std::string> input, std::string delimiter);

// convert strings vector to int
std::vector<int> input_to_int(std::vector<std::string> input);

// convert strings vector to long long int
std::vector<long long int> input_to_llint(std::vector<std::string> input);

// convert strings vector to double
std::vector<double> input_to_double(std::vector<std::string> input);

// convert vec of vec of string to vec of vec of int
std::vector<std::vector<int>> input_to_int_2D(std::vector<std::vector<std::string>> input);

// binary to decimal converter
int binary_to_decimal( int binary );

// decimal to binary converter
int decimal_to_binary( int decimal );

// split string containing values separated by delimiter into vector of strings
std::vector<std::string> split(std::string str, std::string delimiter);

#endif /* UTILS_H */

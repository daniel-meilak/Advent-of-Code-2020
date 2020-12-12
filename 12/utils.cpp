#include"utils.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<cstdlib>
#include<cmath>

// Function to read input file "file_name" containing values separated by
// "separator" and output a vector of strings called "input"
std::vector<std::string> read_input(std::string file_name, std::string separator){

   // output vector of strings
   std::vector<std::string> input;

   // read input into "line"
   std::string line;
   std::ifstream input_file (file_name);

   // check that file exists
   if ( !(input_file.is_open()) ){
      std::cout << "Could not open file " << file_name << std::endl;
      std::exit(EXIT_FAILURE);
   }

   int line_length;
   std::string temp_val;
   while ( getline(input_file, line) ){

      line_length = line.size();

      if ( separator == "" ){
         input.push_back(line);
      }
      else {
         // loop through contents of line
         for ( int read_pos=0; read_pos<line_length; read_pos++ ){

            // if next characters != separator, add next char to temp_val
            if ( line.substr(read_pos, separator.size()) != separator ){
               temp_val.push_back(line[read_pos]);
            }
            // else add the value to input and skip the separator
            else {
               read_pos += separator.size()-1;
               input.push_back(temp_val);
               temp_val.clear();
            }
         }
         // push_back last value
         input.push_back(temp_val);
         temp_val.clear();
      }
   }

   input_file.close();

   return input;
}

// convert vector of strings to vector of ints
std::vector<int> input_to_int(std::vector<std::string> input){

   std::vector<int> output;

   for (int i=0; i<input.size(); i++){
      output.push_back(std::stoi(input[i]));
   }

   return output;
}

// convert vector of strings to vector of long long ints
std::vector<long long int> input_to_llint(std::vector<std::string> input){

   std::vector<long long int> output;

   for (int i=0; i<input.size(); i++){
      output.push_back(std::stoll(input[i]));
   }

   return output;
}

// convert vector of strings to vector of doubles
std::vector<double> input_to_double(std::vector<std::string> input){

   std::vector<double> output;

   for (int i=0; i<input.size(); i++){
      output.push_back(std::stod(input[i]));
   }

   return output;
}

// convert binary to decimal
int binary_to_decimal( int binary ){

   int decimal = 0;
   int i = 0;
   int remainder;

   while ( binary != 0 ){

      remainder = binary%10;
      binary /= 10;
      decimal += remainder*std::pow(2,i);
      ++i;
   }

   return decimal;
}


int decimal_to_binary( int decimal ){

   int binary = 0;
   int remainder, i = 1, step = 1;

   while ( decimal != 0){
      remainder = decimal%2;
      decimal /= 2;
      binary += remainder*i;
      i *= 10;
   }

   return binary;
}
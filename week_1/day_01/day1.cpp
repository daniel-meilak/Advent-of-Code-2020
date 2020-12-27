#include<iostream>
#include<vector>
#include"../../utils/utils.h"

int main(){

   std::vector<int> input = input_to_int(read_input("input", ""));

   // for (int i=0; i<input.size(); i++){
   //    std::cout << input[i] << std::endl;
   // }

   for (unsigned int i=0; i<input.size()-2; i++){
      for (unsigned int j=i+1; j<input.size()-1; j++){
         for (unsigned int k=j+1; k<input.size(); k++){

            if ( (input[i]+input[j]+input[k]) == 2020 ){
               std::cout << input[i]*input[j]*input[k] << std::endl;
            }
         }
      }
   }

   return 0;

}

#include<iostream>
#include<vector>
#include"../../Utils/utils.h"

int main(){

   std::vector<int> input = input_to_int(read_input("input", ""));

   // work through input
   const int size = input.size();
   for (int i=0; i<size-2; i++){
      for (int j=i+1; j<size-1; j++){
         for (int k=j+1; k<size; k++){

            if ( (input[i]+input[j]+input[k]) == 2020 ){
               std::cout << input[i]*input[j]*input[k] << std::endl;
            }
         }
      }
   }

   return 0;

}

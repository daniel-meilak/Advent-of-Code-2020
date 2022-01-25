#include<iostream>
#include<vector>
#include"utils.h"

int main(){

   std::vector<int> input = input_to_int(read_input("input_01"));

   // work through input
   size_t size = input.size();

   int part1{0}, part2{0};

   // i, j and k never overlap so each triplet is only checked once
   for (size_t i=0; i<size-2; i++){
      for (size_t j=i+1; j<size-1; j++){

         // part 1
         if (input[i]+input[j] == 2020){ part1 = input[i]*input[j]; }

         // part 2
         for (size_t k=j+1; k<size; k++){

            if (input[i]+input[j]+input[k] == 2020){ part2 = input[i]*input[j]*input[k]; }
         }
      }
   }

   std::cout << "Answer (part 1): " << part1 << std::endl;
   std::cout << "Answer (part 2): " << part2 << std::endl;

   return 0;

}

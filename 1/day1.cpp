#include<iostream>
#include<vector>
#include"utils.h"

int main(){

   std::vector<std::string> input = read_input("input", "");

   for (int i=0; i<input.size(); i++){
      std::cout << input[i] << std::endl;
   }

   return 0;

}

#!/bin/bash

# script for making new day folder and including files

mkdir $1

cp utils/util* $1/

echo "#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include\"utils.h\"

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input(\"input\", \"\");

    return 0;
}" >> $1/day${1}.cpp

echo "#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include\"utils.h\"

int main(){

    // read input into vector of strings.
    //std::vector<std::string> input = read_input(\"input\", \"\");

    return 0;
}" >> $1/test.cpp
#!/bin/bash

# script for making new day folder and including files

mkdir day_${1}

echo "#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include\"../Utils/utils.h\"

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input(\"input\", \"\");

    return 0;
}" >> day_${1}/day_${1}.cpp

echo "#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include\"../Utils/utils.h\"

int main(){

    // read input into vector of strings.
    //std::vector<std::string> input = read_input(\"input\", \"\");

    return 0;
}" >> day_${1}/test.cpp

echo "## Day ${1}" >> day_${1}/README.md


#include<iostream>
#include<vector>
#include<string>
#include<set>
#include"../../Utils/utils.h"

bool val_year(std::string key, std::string line, int num, int min, int max);
bool val_height(std::string key, std::string line);
bool val_hair(std::string key, std::string line);
bool val_eyes(std::string key, std::string line);
bool val_id(std::string key, std::string line);

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");

    // booleans for passport fields
    bool byr, iyr, eyr, hgt, hcl, ecl, pid; //, cid;
    
    // number of valid passports
    int part1=0, part2=0;
    size_t size = input.size();

    // run through lines of input
    for (size_t i=0; i<size; i++){
        std::string line = input[i];

        while ( input[i+1] != "" ){
            line += " "+input[i+1];
            i++;
        }

        // part 1
        if (   line.find("byr:")!=std::string::npos && line.find("iyr:")!=std::string::npos && line.find("eyr:")!=std::string::npos
            && line.find("hgt:")!=std::string::npos && line.find("hcl:")!=std::string::npos && line.find("ecl:")!=std::string::npos
            && line.find("pid:")!=std::string::npos)
        {
            part1++;
        }

        // part 2
        byr = val_year("byr", line, 4, 1920, 2002);
        iyr = val_year("iyr", line, 4, 2010, 2020);
        eyr = val_year("eyr", line, 4, 2020, 2030);
        hgt = val_height("hgt", line);
        hcl = val_hair("hcl", line);
        ecl = val_eyes("ecl", line);
        pid = val_id("pid", line);

        // if all fields are found and valid (ignoring cid) passport is valid
        if (byr && iyr && eyr && hgt && hcl && ecl && pid){ part2++; }
    }

    std::cout << "Answer (part 1): " << part1 << std::endl;
    std::cout << "Answer (part 2): " << part2 << std::endl;

    return 0;
}

// search for key in line and validate year
bool val_year(std::string key, std::string line, int num, int min, int max){

    std::size_t pos = line.find(key);
    // first check that key exists
    if (pos==std::string::npos){ return false; }

    // extract year 
    std::string year_string = line.substr(pos+4,num);
    int year = std::stoi(year_string);

    // return if year is within bounds
    return (year >= min) && (year <= max);
}

// search for key in line and validate height
bool val_height(std::string key, std::string line){

    std::size_t pos = line.find(key);
    // first check that key exists
    if (pos == std::string::npos ){ return false; }
        
    if ( line.substr(pos+7,2) == "cm" ){
        std::string height_string = line.substr(pos+4,3);
        int height = std::stoi(height_string);

        // return if year is within bounds
        return (height >= 150) && (height <= 193);
    }
    else if ( line.substr(pos+6,2) == "in" ){
        std::string height_string = line.substr(pos+4,2);
        int height = std::stoi(height_string);

        // return if year is within bounds
        return (height >= 59) && (height <= 76);
    }
    // key found but invalid units
    else { return false; }
}

// search for key in line and validate hair colour
bool val_hair(std::string key, std::string line){

    std::string valid_hex = "abcdef0123456789";

    std::size_t pos = line.find(key);
    // first check that key exists
    if (pos == std::string::npos ){ return false; }
        
    if (line.substr(pos+4,1) == "#"){

        std::string hex = line.substr(pos+5,6);
        size_t hex_size = hex.size();
        for (size_t j=0; j<hex_size; j++){
            
            // invalid hex
            if (valid_hex.find(hex[j]) == std::string::npos){ return false; }
        }

        // key found and valid hex
        return true;
    }
    // key found but no #
    else { return false; }
}

// search for key in line and validate eye colour
bool val_eyes(std::string key, std::string line){

    std::set<std::string> eye_colours = {"amb","blu","brn","gry","grn","hzl","oth"};

    std::size_t pos = line.find(key);
    // first check that key exists
    if (pos == std::string::npos){ return false; }

    std::string colour = line.substr(pos+4,3);

    // return if eye colour is valid
    return eye_colours.contains(colour);
}

// search for key in line and validate ID
bool val_id(std::string key, std::string line){

    std::size_t pos = line.find(key);
    // first check that key exists
    if (pos == std::string::npos){ return false; }
    
    std::string id = line.substr(pos+4, 10);

    // return if valid id is found
    return (id.size()==9 || (id.size()==10 && id[9]==' '));
}
#include<iostream>
#include<vector>
#include<string>
#include"utils.h"

bool find_entry(std::string key, std::string line);
bool find_validate_year(std::string key, std::string line, int num, int min, int max);
bool find_validate_height(std::string key, std::string line);
bool find_validate_hair(std::string key, std::string line);
bool find_validate_eyes(std::string key, std::string line);
bool find_validate_id(std::string key, std::string line);

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");

    // booleans for passport fields
    bool byr, iyr, eyr, hgt, hcl, ecl, pid, cid;
    
    // number of valid passports
    int valid=0;

    // run through lines of input
    for (int i=0; i<input.size(); i++){
        std::string line = input[i];

        while ( input[i+1] != "" ){
            line += " "+input[i+1];
            i++;
        }

        byr = find_validate_year("byr", line, 4, 1920, 2002);
        iyr = find_validate_year("iyr", line, 4, 2010, 2020);
        eyr = find_validate_year("eyr", line, 4, 2020, 2030);
        hgt = find_validate_height("hgt", line);
        hcl = find_validate_hair("hcl", line);
        ecl = find_validate_eyes("ecl", line);
        pid = find_validate_id("pid", line);
        cid = find_entry("cid", line);

        // if all fields are found and valid (ignoring cid) passport is valid
        if ( byr && iyr && eyr && hgt && hcl && ecl && pid ){
            valid++;
        }
    }

    std::cout << "Number of valid passports: " << valid << std::endl;

    return 0;

}

// search for key in line
bool find_entry(std::string key, std::string line){

    if ( line.find(key) != std::string::npos ){
        // key found
        return true;
    }
    else {
        // key not found
        return false;
    }

}

// search for key in line and validate year
bool find_validate_year(std::string key, std::string line, int num, int min, int max){


    std::size_t pos = line.find(key);
    if ( pos != std::string::npos ){

        // extract year 
        std::string year_string = line.substr(pos+4,num);

        int year = std::stoi(year_string);

        if ( (year >= min) && (year <= max) ){
            // key found and in bounds 
            return true;
        }
        else {
            // key found not in bounds
            return false;
        }
    }
    else {
        // key not found
        return false;
    }

}

// search for key in line and validate height
bool find_validate_height(std::string key, std::string line){

    std::size_t pos = line.find(key);
    if ( pos != std::string::npos ){
        
        if ( line.substr(pos+7,2) == "cm" ){
            std::string height_string = line.substr(pos+4,3);
            int height = std::stoi(height_string);

            if ( (height >= 150) && (height <= 193) ){
                // key found in cm in bounds
                return true;
            }
            else{
                // key found in cm not in bounds
                return false;
            }
        }
        else if ( line.substr(pos+6,2) == "in" ){
            std::string height_string = line.substr(pos+4,2);
            int height = std::stoi(height_string);

            if ( (height >= 59) && (height <= 76) ){
                // key found in inch in bounds
                return true;
            }
            else{
                // key found in inch not in bounds
                return false;
            }
        }
        else {
            // key found but invalid units
            return false;
        }
    }
    else {
        // key not found
        return false;
    }

}

// search for key in line and validate hair colour
bool find_validate_hair(std::string key, std::string line){

    std::string valid_hex = "abcdef0123456789";

    std::size_t pos = line.find(key);
    if ( pos != std::string::npos ){
        
        if ( line.substr(pos+4,1) == "#" ){

            std::string hex = line.substr(pos+5,6);
            for (int j=0; j<hex.size(); j++){
                
                if ( valid_hex.find(hex[j]) == std::string::npos ){
                    // key found but invalid hex
                    return false;
                }

            }

            // key found and valid hex
            return true;

        }
        else {
            // key found but no #
            return false;
        }

    }
    else {
        // key not found
        return false;
    }

}

// search for key in line and validate eye colour
bool find_validate_eyes(std::string key, std::string line){

    std::size_t pos = line.find(key);
    if ( pos != std::string::npos ){

        std::string colour = line.substr(pos+4,3);

        if ( (colour == "amb") || (colour == "blu") || (colour == "brn") || (colour == "gry") || (colour == "grn") || (colour == "hzl") || (colour == "oth") ){
            // key found and valid colour
            return true;
        }
        else {
            // key found but not valid colour
            return false;
        }

    }
    else {
        // key not found
        return false;
    }

}

// search for key in line and validate ID
bool find_validate_id(std::string key, std::string line){

    std::size_t pos = line.find(key);
    if ( pos != std::string::npos ){
    
        std::string id = line.substr(pos+4, 10);

        if ( id.size() == 9 ){
            // key found with valid id    
            return true;
        }
        else if ( (id.size() == 10) && (id[9] == ' ') ){
            // key found with valid id
            return true;
        }
        else {
            // key found but invalid id
            return false;
        }

    }
    else {
        // key not found
        return false;
    }

}
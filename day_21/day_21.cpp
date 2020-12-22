#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<unordered_map>
#include"../utils/utils.h"

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");

    // map of allergens and possible foods
    std::unordered_map<std::string, std::vector<std::vector<std::string>>> allergen_foods;

    // vector of unique ingredients
    std::vector<std::string> ingredients_list;

    for ( std::string line : input){
        // positions of "(" and ")"
        size_t pos1 = line.find('(');
        size_t pos2 = line.find(')');

        // store ingredients in line
        std::vector<std::string> ingredients = split(line.substr(0,pos1-1), " ");
        line.erase(0, pos1+10);
        line.resize(line.size()-1);

        // add all ingredients to list
        for (std::string ingredient : ingredients){
            //if ( std::find(ingredients_list.begin(), ingredients_list.end(), ingredient) == ingredients_list.end() ){
            ingredients_list.push_back(ingredient);
            //}
        }

        // store allergens in line
        std::vector<std::string> allergens = split(line, ", ");

        for (std::string allergen : allergens){
            allergen_foods[allergen].push_back(ingredients);
        }
    }

    // loop through allergens and reduce ingredients
    int num_not_allergen = 0;
    for (auto & [allergen, foods] : allergen_foods){
        for ( int i=0; i<foods.size(); i++ ){
            for ( int j=0; j<foods[i].size(); j++){
                std::string ingredient = foods[i][j];
                for (int k=0; k<foods.size(); k++){
                    if ( std::find(foods[k].begin(), foods[k].end(), ingredient ) == foods[k].end() ){
                        for ( auto & food : foods ){
                            food.erase(std::remove(food.begin(), food.end(), ingredient), food.end());
                            num_not_allergen++;
                        }
                        j--;
                        break;
                    }
                }
            }
        }
    }

    // new map containing allergens and all possible foods
    std::unordered_map<std::string, std::vector<std::string>> reduced_allergens;
    for (const auto & [allergen, foods] : allergen_foods){
        reduced_allergens[allergen] = {};
        for (auto ingredient : foods[0]){
            if ( std::find(reduced_allergens[allergen].begin(), reduced_allergens[allergen].end(), ingredient) == reduced_allergens[allergen].end() ){
                reduced_allergens[allergen].push_back(ingredient);
            }
        }
    }

    // find allergen with only one possibility, add it to translation list, remove from map
    // and remove all other enties of ingredient. Now another allergen should be linked with 
    // only one other ingredient. Repeat process.
    std::string link;
    std::vector<std::pair<std::string, std::string>> allergen_translation;
    int loop = reduced_allergens.size();
    for (int i=0; i<loop; i++){
        for (auto & [allergen, ingredients] : reduced_allergens){
            if ( ingredients.size() == 1 ){
                link = ingredients[0];
                allergen_translation.push_back({allergen, link});
                reduced_allergens.erase(allergen);
                break;
            }
        }
        // remove link from other foods
        for (auto & [allergen, ingredients] : reduced_allergens){
            if (std::find(reduced_allergens[allergen].begin(), reduced_allergens[allergen].end(), link) != reduced_allergens[allergen].end() ){
                ingredients.erase(std::remove(ingredients.begin(), ingredients.end(), link), ingredients.end());
            }
        }
    }

    // count number of occurences of allergens in total ingredients list
    int count = 0;
    for ( const auto & [allergen, name] : allergen_translation){
        count += std::count(ingredients_list.begin(), ingredients_list.end(), name);
    }

    // answer is num of total ingredients - count
    std::cout << "Part 1: " << ingredients_list.size()-count << std::endl;

    // sort allergens alphabetically
    std::sort(allergen_translation.begin(), allergen_translation.end());

    // output cannonical dangerous ingredient list
    for ( int i=0; i<allergen_translation.size()-1; i++ ){
        std::cout << allergen_translation[i].second << ",";
    }
    std::cout << allergen_translation.back().second << std::endl;

    // remember to remove leading comma

    return 0;
}

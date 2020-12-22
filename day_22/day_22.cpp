#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<list>
#include"../utils/utils.h"

std::string recursive_combat( std::list<int> &player1, std::list<int> &player2, std::vector<std::pair<std::string, std::string>> &history);
std::string list_to_str(std::list<int> cards);

int main(){

    // read input into vector of strings.
    std::vector<std::vector<std::string>> input = split_input(read_input("input", ""), "");

    // put both players cards into forward lists
    std::list<int> player1, player2;
    for ( int i=1; i<input[0].size(); i++ ){
        player1.push_back(std::stoi(input[0][i]));
        player2.push_back(std::stoi(input[1][i]));
    }

    std::string winner = "";
    std::vector<std::pair<std::string, std::string>> history;

    while ( winner == "" ){

        winner = recursive_combat(player1, player2, history);
        
    }

    // count winners points
    int score = 0;
    if ( winner == "player 1" ){
        int i = 1;
        for ( auto it=player1.rbegin(); it != player1.rend(); it++ ){
            score += *it * i;
            i++;
        }
    }
    else {
        int i = 1;
        for ( auto it=player2.rbegin(); it != player2.rend(); it++ ){
            score += *it * i;
            i++;
        }
    }

    std::cout << "Answer (part 1): " << score << std::endl;

    return 0;
}

std::string recursive_combat( std::list<int> &player1, std::list<int> &player2, std::vector<std::pair<std::string, std::string>> &history){

    std::string winner = "";

    // check if this game has already been played
    std::pair<std::string,std::string> game, game_opp;
    game = {list_to_str(player1), list_to_str(player2)};
    //game_opp = {list_to_str(player2), list_to_str(player1)};
    if ( (std::find(history.begin(), history.end(), game) != history.end()) ){//|| (std::find(history.begin(), history.end(), game_opp) != history.end()) ){
        winner = "player 1";
        return winner;
    }
    else {
        history.push_back(game);
    }
    

    // compare top card of each deck
    int p1_top = player1.front();
    int p2_top = player2.front();
    // remove cards from tops
    player1.pop_front();
    player2.pop_front();

    // if both players have enough cards
    if ( (player1.size() >= p1_top) && (player2.size() >= p2_top) ){
        
        // create copies of decks containing num of cards = top card
        std::list<int> p1_copy(p1_top), p2_copy(p2_top);
        std::copy_n(player1.begin(), p1_top, p1_copy.begin());
        std::copy_n(player2.begin(), p2_top, p2_copy.begin());

        // play a sub game of the copied, reduced decks.
        std::string sub_winner = "";
        std::vector<std::pair<std::string, std::string>> sub_history;
        while ( sub_winner == "" ){
            sub_winner = recursive_combat(p1_copy, p2_copy, sub_history);
        }

        // player 1 wins sub game
        if ( sub_winner == "player 1"){
            
            // winners puts card at the bottom
            player1.push_back(p1_top);
            // and the losers card underneath
            player1.push_back(p2_top);
        }
        // player 2 wins sub game
        else {

            // winners puts card at the bottom
            player2.push_back(p2_top);
            // and the losers card underneath
            player2.push_back(p1_top);
        }
    }
    // if one player doesn't have enough cards
    else {
        // player 1 wins
        if (p1_top > p2_top){
            
            // winners puts card at the bottom
            player1.push_back(p1_top);
            // and the losers card underneath
            player1.push_back(p2_top);
        }
        // player 2 wins
        else {

            // winners puts card at the bottom
            player2.push_back(p2_top);
            // and the losers card underneath
            player2.push_back(p1_top);
        }
    }

    // if a deck size goes to zero we have a winner
    if (player1.size() == 0){
        winner = "player 2";
    }
    else if (player2.size() == 0){
        winner = "player 1";
    }

    return winner;
}

std::string list_to_str(std::list<int> cards){

    std::string output = "";

    for ( int card : cards){
        output += std::to_string(card);
    }

    return output;
}
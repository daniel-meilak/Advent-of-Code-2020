#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<list>
#include<unordered_map>
#include"../utils/utils.h"

// forward function declarations
std::list<int> find_row(int id, std::unordered_map<int,std::vector<std::string>> &camera_array );
void find_neighbours(std::string border, std::list<int> &row, std::unordered_map<int,std::vector<std::string>> &camera_array, std::string side);
std::string check_piece( std::string &border, std::vector<std::string> &piece, std::string side);
void rotate( std::vector<std::string> &matrix, std::string direction );
void flip( std::vector<std::string> &matrix );
void flip_vert( std::vector<std::string> &matrix );

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");

    // map of puzzle pieces and their index
    std::unordered_map<int,std::vector<std::string>> camera_array;

    // store indexes and camera piece
    int index;
    std::vector<std::string> piece;

    for (int i=0; i<input.size(); i++){

        std::string line = input[i];

        if (line == ""){ 
            camera_array[index] = piece;
            piece.clear();
        }
        else if (line[0] == 'T'){
            
            index = std::stoi(line.substr(5,4)); 
        }
        else {
            
            piece.push_back(line);
        }
    }
    camera_array[index] = piece;

    // take the first piece in the puzzle and find the row it is in
    std::list<int> first_row = find_row(camera_array.begin()->first, camera_array);

    std::list<std::list<int>> picture;

    // from the first row, we find the colums connecting to each piece
    for (int id : first_row){

        // rotate each piece
        rotate(camera_array[id], "left");
        picture.push_back(find_row(id, camera_array));
        rotate(camera_array[id], "right");
    }

    // find answer by multiplying ids of corners
    long long int sum = 1ULL*picture.front().front()*picture.front().back()*picture.back().front()*picture.back().back();

    std::cout << "Answer: " << sum << std::endl;

    

    return 0;
}

// creates list containing all connecting puzzle pieces to left and right of input piece
std::list<int> find_row(int id, std::unordered_map<int,std::vector<std::string>> &camera_array ){

    // get piece 
    std::vector<std::string> main_piece = camera_array[id];

    // remove from map
    //camera_array.erase(id);

    // vectors containing left and right borders
    std::string l_border, r_border;
    for (int i=0; i<main_piece.size(); i++){
        l_border.push_back(main_piece[i].front());
        r_border.push_back(main_piece[i].back());
    }

    // list of row
    std::list<int> row = {id};
    
    // find left and right neighbours
    find_neighbours(l_border, row, camera_array, "left");
    find_neighbours(r_border, row, camera_array, "right");

    // we have completed the row
    return row;
}

void find_neighbours(std::string border, std::list<int> &row, std::unordered_map<int,std::vector<std::string>> &camera_array, std::string side){

    bool at_edge = false;
    std::string old_border;

    // find left neighbours
    while (!at_edge){

        old_border = border;

        // loop through each puzzle piece
        for ( auto & [next_id, piece] : camera_array){

            // ignore piece already in row
            if ( std::find(row.begin(), row.end(), next_id) != row.end() ){ continue; }

            // next border
            std::string next_border = check_piece(border, piece, side);

            // if we found a connecting piece
            if (next_border != ""){
                
                // add the piece to the row
                if (side == "left"){
                    row.push_front(next_id);
                }
                else {
                    row.push_back(next_id);
                }
                
                // get the next border and restart search
                border     = next_border;
                break;
            }   
        }
        
        // if border hasn't changed after looking for next piece
        // we've reached the edge 
        if (border == old_border){ at_edge = true; }
    }
}

// checks if piece connects to border on side (right or left)
std::string check_piece( std::string &border, std::vector<std::string> &piece, std::string side){

    // borders
    std::string top, bottom, left, right;

    top    = piece.front();
    bottom = piece.back();
    for (int i=0; i<piece.size(); i++){
        left.push_back(piece[i].front());
        right.push_back(piece[i].back());
    }

    // flipped borders
    std::string top_f = top, bottom_f = bottom, left_f = left, right_f = right;
    std::reverse(top_f.begin(), top_f.end());
    std::reverse(bottom_f.begin(), bottom_f.end());
    std::reverse(left_f.begin(), left_f.end());
    std::reverse(right_f.begin(), right_f.end());

    // result
    std::string match = "";

    // check sides
    if ( top == border ){
        if ( side == left ){
            rotate(piece, "right");
        }
        else {
            rotate(piece, "left");
        }
        match = bottom;
    }
    else if ( top_f == border ){
        flip(piece);
        if ( side == left ){
            rotate(piece, "right");
        }
        else {
            rotate(piece, "left");
        }
        match = bottom_f;
    }
    else if ( bottom == border ){
        if ( side == left ){
            rotate(piece, "left");
        }
        else {
            rotate(piece, "right");
        }
        match = top;
    }
    else if ( bottom_f == border ){
        flip(piece);
        if ( side == left ){
            rotate(piece, "left");
        }
        else {
            rotate(piece, "right");
        }
        match = top_f;
    }
    else if ( right == border ){
        if ( side == right ){
            rotate(piece, "left");
            rotate(piece, "left");
        }
        match = left;
    }
    else if ( right_f == border ){
        flip_vert(piece);
        if ( side == right ){
            rotate(piece, "left");
            rotate(piece, "left");
        }
        match = left_f;
    }
    else if ( left == border ){
        if ( side == left ){
            rotate(piece, "left");
            rotate(piece, "left");
        }
        match = right;
    }
    else if ( left_f == border ){
        flip_vert(piece);
        if ( side == left ){
            rotate(piece, "left");
            rotate(piece, "left");
        }
        match = right_f;
    }

    return match;
}



// rotates square matrix by 90deg direction = left or right
void rotate( std::vector<std::string> &matrix, std::string direction ){

    int size = matrix.size();

    // intialize output vector to correct size
    std::vector<std::string> output(size, std::string(size, ' '));

    std::string s;
    for (int i=0; i<size; i++){
        // take nth row of input matrix
        s = matrix[i];

        // turn it into nth column of output
        for (int j=size-1; j>=0; j--){
            if ( direction == "left" ){
                output[j][i] = s[size-1-j];
            }
            else if ( direction == "right" ){
                output[j][size-1-i] = s[j];
            }
            else {
                std::cout << "Invalid rotation" << std::endl;
                std::exit(EXIT_FAILURE);
            }
        }
    }

    matrix = output;
}

// horizontally flip square matrix 
void flip( std::vector<std::string> &matrix ){

    int size = matrix.size();

    // initialize output vector to correct size
    std::vector<std::string> output(size, std::string(size, ' '));

    std::string s;
    for (int y=0; y<size; y++){

        // take nth row of input matrix
        s = matrix[y];

        // flip and add to nth row of output
        for (int x=0; x<size; x++){
            output[y][x] = s[size-1-x]; 
        }
    }

    matrix = output;
}

void flip_vert( std::vector<std::string> &matrix ){

    int size = matrix.size();

    // initialize output vector to correct size
    std::vector<std::string> output(size, std::string(size, ' '));

    for (int y=0; y<size; y++){
        output[size-1-y] = matrix[y];
    }

    matrix = output;
}

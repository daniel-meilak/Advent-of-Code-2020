#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<regex>
#include<unordered_map>
#include"utils.h"

// forward function declarations
std::vector<int> find_line(int id, std::unordered_map<int,std::vector<std::string>> &camera_array, std::string row_col );
void find_monster(std::vector<std::string> &picture);
void find_neighbours(std::string border, std::vector<int> &row, std::unordered_map<int,std::vector<std::string>> &camera_array, std::string side);
std::string check_piece( std::string &border, std::vector<std::string> &piece, std::string side);
void rotate( std::vector<std::string> &matrix, std::string direction );
void flip( std::vector<std::string> &matrix );
void flip_vert( std::vector<std::string> &matrix );

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input_20");

    // map of puzzle pieces and their index
    std::unordered_map<int,std::vector<std::string>> camera_array;

    // store indexes and camera piece
    int index;
    std::vector<std::string> piece;

    for (size_t i=0; i<input.size(); i++){

        std::string line = input[i];

        if (line == ""){ 
            camera_array[index] = piece;
            piece.clear();
        }
        else if (line[0] == 'T'){ index = std::stoi(line.substr(5,4)); }
        else { piece.push_back(line); }
    }

    camera_array[index] = piece;

    // take the first piece in the puzzle and find the row it is in
    std::vector<int> first_row = find_line(camera_array.begin()->first, camera_array, "row");

    std::vector<std::vector<int>> picture;

    // from the first row, we find the colums connecting to each piece
    for (int id : first_row){
        picture.push_back(find_line(id, camera_array, "col"));
    }

    // find answer by multiplying ids of corners
    long long sum = 1ULL*picture.front().front()*picture.front().back()*picture.back().front()*picture.back().back();

    std::cout << "Answer (part 1): " << sum << std::endl;

    // remove all borders
    for (auto & pair : camera_array){

        // remove top and bottom
        pair.second.erase(pair.second.begin());
        pair.second.erase(pair.second.end());

        // remove sides
        for (size_t i=0; i<pair.second.size(); i++){
            pair.second[i] = pair.second[i].substr(1, pair.second[i].size()-2);
        }
    }

    // dimension of individual puzzle piece
    int size = camera_array.begin()->second.size();

    // height and width of puzzle
    int total_size = size*std::sqrt(camera_array.size());

    // vector<string> containing finished picture
    std::vector<std::string> finished_picture(total_size);

    for (size_t i=0; i<picture.size(); i++){
        for (size_t j=0; j<picture[0].size(); j++){
            for (size_t k=0+j*size; k<size+j*size; k++){
                finished_picture[k] += camera_array[picture[i][j]][k % size];
            }
        }
    }

    // find the monster after rotating the image
    flip(finished_picture);
    rotate(finished_picture, "right");
    rotate(finished_picture, "right");
    find_monster(finished_picture);

    // count number of leftover #
    int tally = 0;
    for (std::string line : finished_picture){
        tally += std::count(line.begin(), line.end(), '#'); 
    }

    std::cout << "Answer (part 2): " << tally << std::endl;    

    return 0;
}

void find_monster(std::vector<std::string> &picture){

    // monster body positions
    std::vector<int> monster_top = {18};
    std::vector<int> monster_mid = {0,5,6,11,12,17,18,19};
    std::vector<int> monster_bot = {1,4,7,10,13,16};

    // search for mid in 2nd to 2nd last rows
    for (size_t i=1; i<picture.size()-1; i++){
        // search along the width of the picture
        for (size_t j=0; j<picture[0].size()-20; j++){

            bool invalid = false;

            // cheack each '#' location
            for (int val : monster_mid){
                if ( picture[i][val+j] != '#' ){
                    invalid = true;
                    break;
                }
            }

            if (!invalid){
                for (int val : monster_top){
                    if (picture[i-1][val+j]!='#' || picture[i+1][val+j]!='#'){
                        invalid = true;
                        break;
                    }
                }

                // change all the monster '#' to 'O'
                for (int val : monster_bot){
                    picture[i+1][val+j] = 'O';
                }
                for (int val : monster_mid){
                    picture[i][val+j] = 'O';
                }
                for (int val : monster_top){
                    picture[i-1][val+j] = 'O';
                }
            }
        }
    }
}

// creates vector containing all connecting puzzle pieces to left and right of input piece
std::vector<int> find_line(int id, std::unordered_map<int,std::vector<std::string>> &camera_array, std::string row_col ){

    // get piece 
    std::vector<std::string> main_piece = camera_array[id];

    // create vectors for borders
    std::string l_border, r_border, t_border, b_border;
    if (row_col == "row"){
        for (unsigned int i=0; i<main_piece.size(); i++){
            l_border.push_back(main_piece[i].front());
            r_border.push_back(main_piece[i].back());
        }
    }
    else {
        t_border = main_piece.front();
        b_border = main_piece.back();
    }

    // vector of row
    std::vector<int> row = {id};
    
    // find neighbours
    if (row_col == "row"){
        find_neighbours(l_border, row, camera_array, "left");
        find_neighbours(r_border, row, camera_array, "right");
    }
    else {
        find_neighbours(t_border, row, camera_array, "top");
        find_neighbours(b_border, row, camera_array, "bottom");
    }

    // we have completed the row
    return row;
}

void find_neighbours(std::string border, std::vector<int> &row, std::unordered_map<int,std::vector<std::string>> &camera_array, std::string side){

    bool at_edge = false;
    std::string old_border;

    // find left neighbours
    while (!at_edge){

        old_border = border;

        // loop through each puzzle piece
        for (auto & [next_id, piece] : camera_array){

            // ignore piece already in row
            if ( std::find(row.begin(), row.end(), next_id) != row.end() ){ continue; }

            // next border
            std::string next_border = check_piece(border, piece, side);

            // if we found a connecting piece
            if (next_border != ""){
                
                // add the piece to the row
                if ((side == "left") || (side == "top")){ row.insert(row.begin(),next_id); }
                else { row.push_back(next_id); }
                
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
    for (unsigned int i=0; i<piece.size(); i++){
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
        if ( side == "left" ){
            rotate(piece, "right");
        }
        else if (side == "right"){
            flip(piece);
            rotate(piece, "left");
        }
        else if (side == "top"){
            flip_vert(piece);
        }
        // if bottom do nothing
        match = bottom;
    }
    else if ( top_f == border ){
        flip(piece);
        if ( side == "left" ){
            rotate(piece, "right");
        }
        else if ( side == "right"){
            flip(piece);
            rotate(piece, "left");
        }
        else if (side == "top"){
            flip_vert(piece);
        }
        match = bottom_f;
    }
    else if ( bottom == border ){
        if ( side == "left" ){
            flip(piece);
            rotate(piece, "left");
        }
        else if (side == "right"){
            rotate(piece, "right");
        }
        else if (side == "bottom"){
            flip_vert(piece);
        }
        match = top;
    }
    else if ( bottom_f == border ){
        flip(piece);
        if ( side == "left" ){
            flip(piece);
            rotate(piece, "left");
        }
        else if ( side == "right"){
            rotate(piece, "right");
        }
        else if (side == "bottom"){
            flip_vert(piece);
        }
        match = top_f;
    }
    else if ( right == border ){
        if ( side == "right"){
            flip(piece);
        }
        else if (side == "bottom"){
            rotate(piece, "left");
        }
        else if (side == "top"){
            flip(piece);
            rotate(piece, "left");
        }
        match = left;
    }
    else if ( right_f == border ){
        flip_vert(piece);
        if ( side == "right"){
            flip(piece);
        }
        else if (side == "bottom"){
            rotate(piece, "left");
        }
        else if (side == "top"){
            flip(piece);
            rotate(piece, "left");
        }
        match = left_f;
    }
    else if ( left == border ){
        if ( side == "left"){
            flip(piece);
        }
        else if (side == "bottom"){
            flip(piece);
            rotate(piece, "left");
        }
        else if (side == "top"){
            rotate(piece, "left");
        }
        match = right;
    }
    else if ( left_f == border ){
        flip_vert(piece);
        if ( side == "left"){
            flip(piece);
        }
        else if (side == "bottom"){
            flip(piece);
            rotate(piece, "left");
        }
        else if (side == "top"){
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
            if      (direction == "left" ){ output[j][i] = s[size-1-j]; }
            else if (direction == "right"){ output[j][size-1-i] = s[j]; }
            else {
                std::cout << "Invalid rotation" << std::endl;
                std::exit(EXIT_FAILURE);
            }
        }
    }

    matrix = output;
}

// horizontally flip square matrix 
void flip(std::vector<std::string> &matrix){

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

void flip_vert(std::vector<std::string> &matrix){

    int size = matrix.size();

    // initialize output vector to correct size
    std::vector<std::string> output(size, std::string(size, ' '));

    for (int y=0; y<size; y++){
        output[size-1-y] = matrix[y];
    }

    matrix = output;
}

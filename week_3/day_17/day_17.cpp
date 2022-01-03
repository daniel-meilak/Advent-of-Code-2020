#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

// forward function declaration
int active_neighbours(std::vector<std::vector<std::vector<std::vector<bool>>>> &system, int x, int y, int z, int w, bool part2);
int total_active(std::vector<std::vector<std::vector<std::vector<bool>>>> &system, int x, int y, int z, int w, bool part2);
int sim(std::vector<std::vector<std::vector<std::vector<bool>>>> &p_dim, int &buffer, std::vector<int> &max, std::vector<int> &tot, bool part2);

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input_17");

    // system buffer is number of cycles+1
    // total sizes are core size + 2*buffer
    int buffer = 7;
    std::vector<int> tot = {(int)input.size()+(buffer*2),(int)input[0].size()+(buffer*2),1+(buffer*2),1+(buffer*2)};

    // initialize 4D system vector
    std::vector<std::vector<std::vector<std::vector<bool>>>> p_dim_4D(tot[0], std::vector<std::vector<std::vector<bool>>>(tot[1], std::vector<std::vector<bool>>(tot[2], std::vector<bool>(tot[3], false))));

    // initialize 3D system vector
    std::vector<std::vector<std::vector<std::vector<bool>>>> p_dim_3D(tot[0], std::vector<std::vector<std::vector<bool>>>(tot[1], std::vector<std::vector<bool>>(tot[2], std::vector<bool>(1, false))));

    // core limits are core size + buffer
    std::vector<int> max = {buffer+(int)input.size(),buffer+(int)input[0].size(),buffer+1,buffer+1};

    // fill system with input at centre
    for (int x=buffer; x<max[0]; x++){
        for (int y=buffer; y<max[1]; y++){

            if ( input[x-buffer][y-buffer] == '#' ){
                p_dim_4D[x][y][buffer][buffer] = true;
                p_dim_3D[x][y][buffer][0]      = true;
            }
        }
    }

    std::cout << "Answer (part 1): " << sim(p_dim_3D,buffer,max,tot,false) << std::endl;
    std::cout << "Answer (part 1): " << sim(p_dim_4D,buffer,max,tot,true ) << std::endl;

    return 0;
}

int sim(std::vector<std::vector<std::vector<std::vector<bool>>>> &p_dim, int &buffer, std::vector<int> &max, std::vector<int> &tot, bool part2){
    
    // create a copy of the system
    std::vector<std::vector<std::vector<std::vector<bool>>>> p_dim_copy = p_dim;

    // 6 cycles required
    // after each cycle increase simulated zone (early sims only affect core)
    for (int cycle=1; cycle<=6; cycle++ ){
        for (int x=buffer-cycle; x<max[0]+cycle; x++){
            for (int y=buffer-cycle; y<max[1]+cycle; y++){
                for (int z=buffer-cycle; z<max[2]+cycle; z++){
                    if (part2){
                        for (int w=buffer-cycle; w<max[3]+cycle; w++){

                            // number of active neighbours
                            int num_active = active_neighbours(p_dim,x,y,z,w,part2);

                            // if active
                            if (p_dim[x][y][z][w]){
                                if ( (num_active == 2) || (num_active == 3) ){ continue; }
                                else { p_dim_copy[x][y][z][w] = false; }
                            }
                            else {
                                if ( num_active == 3 ){ p_dim_copy[x][y][z][w] = true; }
                            }
                        }
                    }
                    else {
                        int num_active = active_neighbours(p_dim,x,y,z,0,part2);

                        // if active
                        if (p_dim[x][y][z][0]){
                            if ( (num_active == 2) || (num_active == 3) ){ continue; }
                            else { p_dim_copy[x][y][z][0] = false; }
                        }
                        else {
                            if ( num_active == 3 ){ p_dim_copy[x][y][z][0] = true; }
                        }

                    }
                }
            }
        }

        // at the end of a cycle, update the whole system
        p_dim = p_dim_copy;
    }

    // output total number of active cubes
    return total_active(p_dim,tot[0],tot[1],tot[2],tot[3],part2);
}



// counts the number of active neighbours 
int active_neighbours(std::vector<std::vector<std::vector<std::vector<bool>>>> &system, int x, int y, int z, int w, bool part2){

    int num_active = 0;

    // loop through 3*3*3*3 hypercube
    for (int i=x-1; i<=x+1; i++){
        for (int j=y-1; j<=y+1; j++){
            for (int k=z-1; k<=z+1; k++){
                if (part2){
                    for (int l=w-1; l<=w+1; l++){
                        if (system[i][j][k][l]){ num_active++; }
                    }
                }
                else {
                    if (system[i][j][k][0]){ num_active++; }
                }
            }
        }
    }

    // ignore centre
    if (system[x][y][z][w]){ num_active--; }

    return num_active;
}

// counts the number of active cubes in the system
int total_active(std::vector<std::vector<std::vector<std::vector<bool>>>> &system, int x, int y, int z, int w, bool part2){

    int total = 0;

    for (int i=0; i<x; i++){
        for (int j=0; j<y; j++){
            for (int k=0; k<z; k++){
                if (part2){
                    for (int l=0; l<w; l++){
                        if (system[i][j][k][l]){ total++; }
                    }
                }
                else {
                    if (system[i][j][k][0]){ total++; }
                }
            }
        }
    }

    return total;
}
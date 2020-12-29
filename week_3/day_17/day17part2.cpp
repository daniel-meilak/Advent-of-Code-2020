#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

// forward function declaration
int active_neighbours(std::vector<std::vector<std::vector<std::vector<bool>>>> &system, int x, int y, int z, int w);
int total_active(std::vector<std::vector<std::vector<std::vector<bool>>>> &system, int x, int y, int z, int w);

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");

    // system buffer is number of cycles+1
    // total sizes are core size + 2*buffer
    int buffer = 7;
    int x_tot = input.size()+(buffer*2);
    int y_tot = input[0].size()+(buffer*2);
    int z_tot = 1+(buffer*2);
    int w_tot = 1+(buffer*2);

    // initialize 4D system vector
    std::vector<std::vector<std::vector<std::vector<bool>>>> p_dim(x_tot, std::vector<std::vector<std::vector<bool>>>(y_tot, std::vector<std::vector<bool>>(z_tot, std::vector<bool>(w_tot, false))));

    // core limits are core size + buffer
    int x_max = buffer+input.size();
    int y_max = buffer+input[0].size();
    int z_max = buffer+1;
    int w_max = buffer+1;

    // fill system with input at centre
    for (int x=buffer; x<x_max; x++){
        for (int y=buffer; y<y_max; y++){

            if ( input[x-buffer][y-buffer] == '#' ){
                p_dim[x][y][buffer][buffer] = true;
            }
        }
    }

    // create a copy of the system
    std::vector<std::vector<std::vector<std::vector<bool>>>> p_dim_copy = p_dim;

    // 6 cycles required
    // after each cycle increase simulated zone (early sims only affect core)
    for (int cycle=1; cycle<=6; cycle++ ){
        for (int x=buffer-cycle; x<x_max+cycle; x++){
            for (int y=buffer-cycle; y<y_max+cycle; y++){
                for (int z=buffer-cycle; z<z_max+cycle; z++){
                    for (int w=buffer-cycle; w<w_max+cycle; w++){

                        // number of active neighbours
                        int num_active = active_neighbours(p_dim, x, y, z, w);

                        // if active
                        if (p_dim[x][y][z][w]){
                            if ( (num_active == 2) || (num_active == 3) ){
                                continue;
                            }
                            else {
                                p_dim_copy[x][y][z][w] = false;
                            }
                        }
                        else {
                            if ( num_active == 3 ){
                                p_dim_copy[x][y][z][w] = true;
                            }
                        }
                    }
                }
            }
        }

        // at the end of a cycle, update the whole system
        p_dim = p_dim_copy;
    }

    // output total number of active cubes
    std::cout << "Total active cubes: " << total_active(p_dim,x_tot,y_tot,z_tot,w_tot) << std::endl;

    return 0;
}

// counts the number of active neighbours 
int active_neighbours(std::vector<std::vector<std::vector<std::vector<bool>>>> &system, int x, int y, int z, int w){

    int num_active = 0;

    // loop through 3*3*3*3 hypercube
    for (int i=x-1; i<=x+1; i++){
        for (int j=y-1; j<=y+1; j++){
            for (int k=z-1; k<=z+1; k++){
                for (int l=w-1; l<=w+1; l++){
                    if (system[i][j][k][l]){ num_active++; }
                }
            }
        }
    }

    // ignore centre
    if (system[x][y][z][w]){ num_active--; }

    return num_active;
}

// counts the number of active cubes in the system
int total_active(std::vector<std::vector<std::vector<std::vector<bool>>>> &system, int x, int y, int z, int w){

    int total = 0;

    for (int i=0; i<x; i++){
        for (int j=0; j<y; j++){
            for (int k=0; k<z; k++){
                for (int l=0; l<w; l++){
                
                    if (system[i][j][k][l]){ total++; }
                }
            }
        }
    }

    return total;
}
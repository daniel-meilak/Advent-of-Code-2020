#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../utils/utils.h"

// forward function declaration
int active_neighbours(std::vector<std::vector<std::vector<bool>>> &system, int x, int y, int z);
int total_active(std::vector<std::vector<std::vector<bool>>> &system, int x, int y, int z);

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");

    // system buffer is number of cycles+1
    // total sizes are core size + 2*buffer
    int buffer = 7;
    int x_tot = input.size()+(buffer*2);
    int y_tot = input[0].size()+(buffer*2);
    int z_tot = 1+(buffer*2);

    // initialize 3D system vector
    std::vector<std::vector<std::vector<bool>>> p_dim(x_tot, std::vector<std::vector<bool>>(y_tot, std::vector<bool>(z_tot,false)));

    // core limits are core size + buffer
    int x_max = buffer+input.size();
    int y_max = buffer+input[0].size();
    int z_max = buffer+1;

    // fill system with input at centre
    for (int x=buffer; x<x_max; x++){
        for (int y=buffer; y<y_max; y++){

            if ( input[x-buffer][y-buffer] == '#' ){
                p_dim[x][y][buffer] = true;
            }
        }
    }

    // create a copy of the system
    std::vector<std::vector<std::vector<bool>>> p_dim_copy = p_dim;

    // 6 cycles required
    // after each cycle increase simulated zone (early sims only affect core)
    for (int cycle=1; cycle<=6; cycle++ ){
        for (int x=buffer-cycle; x<x_max+cycle; x++){
            for (int y=buffer-cycle; y<y_max+cycle; y++){
                for (int z=buffer-cycle; z<z_max+cycle; z++){

                    // number of active neighbours
                    int num_active = active_neighbours(p_dim, x, y, z);

                    // if active
                    if (p_dim[x][y][z]){
                        if ( (num_active == 2) || (num_active == 3) ){
                            continue;
                        }
                        else {
                            p_dim_copy[x][y][z] = false;
                        }
                    }
                    else {
                        if ( num_active == 3 ){
                            p_dim_copy[x][y][z] = true;
                        }
                    }
                }
            }
        }

        // at the end of a cycle, update the whole system
        p_dim = p_dim_copy;
    }

    std::cout << "Total active cubes: " << total_active(p_dim,x_tot,y_tot,z_tot) << std::endl;

    return 0;
}

// counts the number of active neighbours 
int active_neighbours(std::vector<std::vector<std::vector<bool>>> &system, int x, int y, int z){

    int num_active = 0;

    // loop through 3*3*3 cube
    for (int i=x-1; i<=x+1; i++){
        for (int j=y-1; j<=y+1; j++){
            for (int k=z-1; k<=z+1; k++){
                if (system[i][j][k]){ num_active++; }
            }
        }
    }

    // ignore centre
    if (system[x][y][z]){ num_active--; }

    return num_active;
}

// counts the number of active cubes in the system
int total_active(std::vector<std::vector<std::vector<bool>>> &system, int x, int y, int z){

    int total = 0;

    for (int i=0; i<x; i++){
        for (int j=0; j<y; j++){
            for (int k=0; k<z; k++){
                
                if (system[i][j][k]){ total++; }
            }
        }
    }

    return total;
}
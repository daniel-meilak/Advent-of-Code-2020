#include<vector>

// modular multiplicative inverse: (int) x such that
// ax = 1 (mod m) [or for all k (+/- integers) ax = 1 + km]
// source: https://rosettacode.org/wiki/Modular_inverse
template <typename T> T mul_inv( T a, T b){

    T t, q, b0 = b;
    T x0 = 0, x1 = 1;

    if ( b == 1 ){ return 1; }

    while ( a > 1 ){
        
        q = a/b;
        t = b, b = a % b, a = t;
        t = x0, x0 = x1 - q*x0, x1 = t;
    }

    if ( x1 < 0 ){ x1 += b0; }
    
    return x1;
}

// Chinese remainder theorem
//  n = {n0, n1, n2 ... nk} are coprime positive integers
//  a = {a0, a1, a2 ... ak} integers
//  There exists an integer x such that the simultaneous congruences: 
//  x = ak mod nk
template <typename T> T  chinese_remainder( std::vector<T> n, std::vector<T> a ){

    T p, prod = 1, sum = 0;

    for ( int i=0; i<n.size(); i++ ){ prod *= n[i] ;}

    for ( int i=0; i<n.size(); i++ ){
        p = prod/n[i];
        sum += a[i]*mul_inv(p,n[i])*p;
    }

    return sum % prod;
}
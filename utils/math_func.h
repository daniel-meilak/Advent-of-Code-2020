#ifndef MATH_FUNC_H
#define MATH_FUNC_H

#include<vector>

// modular multiplicative inverse
long long int mul_inv( long long int a, long long int b);
//template<typename _Ty> _Ty mulInv(_Ty a, _Ty b);

// chinese remainder
long long int chinese_remainder(std::vector<long long int> n, std::vector<long long int> a);
//template<typename _Ty> _Ty chineseRemainder(std::vector<_Ty> n, std::vector<_Ty> a);

#endif /* MATH_FUNC_H */
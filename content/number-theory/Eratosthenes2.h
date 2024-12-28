/**
 * Author: Miguel Mini
 * Date: 2024-10-19
 * License: CC0
 * Source: https://codeforces.com/blog/entry/54090
 * Description: Prime sieve for generating all primes up to a certain limit. composite$[i]$ is true iff $i$ not's a prime.
 * Time: 1.8s | n = 5e8
 * Status: Tested [yosupo - enumeratePrimes] 
 */
#pragma once

#include <bitset>
#include <vector>

namespace nt {

    const int maxn = 5e5 + 10;
    std::bitset<maxn> composite;
    std::vector<int> prime;

    //multiplicative
    //int phi[maxn];    

    //int f[maxn]; //multiplicative function
    //int cnt[maxn]; //lamdda_p(i): exponent of p in i

    //int f_prime(int p, int k) {
    //  return ...;
    //}

    //min prime divisor
    int lp[maxn];

    void eratosthenesSieve(int n=maxn-1) {
        //phi[1]=1;
        //f[1] = 1;
        //cnt[1] = 0;
        for (int i=2; i<=n; ++i) {
            if (!composite[i]) {
                prime.emplace_back(i);
                //phi[i] = i-1;
                //f[i] = f_prime(i, 1);
                //cnt[i] = 1;
                //lp[i] = i;
            }
            for (int p : prime) {
                if (p * i > n) break;
                composite[p * i] = 1;
                //lp[p * i] = p;
                if (i % p == 0) { //update p * i = pˆk j with k > 1
                    //phi[p * i] = p * phi[i];
                    //f[p * i] = f[i] / f_prime(p, cnt[i]) * f_prime(p, cnt[i] + 1);
                    //cnt[p * i] = cnt[i] + 1;
                    break;
                } else { // minimum prime divisor de i > p
                    //phi[p * i] = (p - 1) * phi[i];
                    //f[p * i] = f[p] * f[i];
                    //cnt[p * i] = 1;
                }
            }
        }        
    }
};

/**
 * Divisores de n
 * 
 * Para n <= 1e18 -> max numero de dicisores <= 2 nˆ{1/3}
 *  
 * Suma de disivosres hasta n
 * 
 * sum sigma(n) = sum floor(n / i) <= n\log n
 * 
 * Bertrang's postulate
 * 
 *  - Para tono n >= 2, existe p tal que: n < p < 2n
 *  - El k-esimo primo p_{k+1} < 2p_k
 * 
 * Prime's gap
 * 
 * 1. n <= 10ˆ6 --> gap <= 114
 * 2. n <= 10ˆ9 --> gap <= 282
 * 3. n <= 10ˆ{19} --> gap <= 1510
 * 
 * Primes up to n
 * 
 * - aprox n / logn
 * 
 * - for k>1, kth prime is similar to klogk
 * 
 * 
 */

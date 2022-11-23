    typedef unsigned long long ull;
    const ull MOD = (ull(1) << 61) - 1;

    ull mod61(const ull a) {
        return (a & MOD) + (a >> 61);
    }

    ull mod(const ull a) {
        return mod61(mod61(a)+1)-1;
    }

    ull add(ull a, const ull b) {
        return (a += b) >= MOD ? (a -= MOD) : a;
    }   

    ull sub(ull a, const ull b) {
        return (a -= b) >= MOD ? (a += MOD) : a;
    }

    ull mul(const ull a, const ull b) {
    // Given 0 <= a, b < mod. Need to calculate (a * b) % MOD
    // a = a0 + a1 * 2^32
    // b = b0 + b1 * 2^32
    // a * b = a0 * b0 + (a0 * b1 + a1 * b0) * 2^32 + a1 * b1 * 2^64
        const ull a0 = a & ~0u, a1 = a >> 32;
        const ull b0 = b & ~0u, b1 = b >> 32;
        const ull mid = a0 * b1 + a1 * b0;
        return mod(mod61(a0 * b0) + (a1 * b1 << 3) + (mid >> 29) + (mid << 32 & MOD));
    }
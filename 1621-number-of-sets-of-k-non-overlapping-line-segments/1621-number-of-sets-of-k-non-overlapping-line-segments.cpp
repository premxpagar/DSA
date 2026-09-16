class Solution {
public:
    int numberOfSets(int n, int k) {
        const long long MOD = 1e9 + 7;

        long long ans = 1;
        int N = n + k - 1;
        int R = 2 * k;

        for (int i = 1; i <= R; i++) {
            ans = ans * (N - R + i) % MOD;

            long long base = i, power = MOD - 2;
            long long inv = 1;

            while (power) {
                if (power & 1)
                    inv = inv * base % MOD;
                base = base * base % MOD;
                power >>= 1;
            }

            ans = ans * inv % MOD;
        }

        return ans;
    }
};
class Solution {
public:
    int numberOfStableArrays(int zero, int one, int limit) {
        const int MOD = 1e9 + 7;

        vector<vector<vector<int>>> memo(
            zero + 1,
            vector<vector<int>>(one + 1, vector<int>(2, -1)));

        function<int(int,int,int)> dp = [&](int z, int o, int last) -> int {
            if (z == 0) {
                return (last == 0 || o > limit) ? 0 : 1;
            }
            if (o == 0) {
                return (last == 1 || z > limit) ? 0 : 1;
            }

            if (memo[z][o][last] != -1)
                return memo[z][o][last];

            long long ans;

            if (last == 0) {
                ans = (1LL * dp(z - 1, o, 0) + dp(z - 1, o, 1)) % MOD;
                if (z > limit) {
                    ans = (ans - dp(z - limit - 1, o, 1) + MOD) % MOD;
                }
            } else {
                ans = (1LL * dp(z, o - 1, 0) + dp(z, o - 1, 1)) % MOD;
                if (o > limit) {
                    ans = (ans - dp(z, o - limit - 1, 0) + MOD) % MOD;
                }
            }

            return memo[z][o][last] = ans;
        };

        return (dp(zero, one, 0) + dp(zero, one, 1)) % MOD;
    }
};
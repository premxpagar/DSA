class Solution {
public:
    int distinctSubseqII(string s) {
        const int MOD = 1e9 + 7;
        long long dp[26] = {};

        for (char c : s) {
            long long total = 1;
            for (int i = 0; i < 26; i++)
                total = (total + dp[i]) % MOD;

            dp[c - 'a'] = total;
        }

        long long ans = 0;
        for (long long x : dp)
            ans = (ans + x) % MOD;

        return ans;
    }
};
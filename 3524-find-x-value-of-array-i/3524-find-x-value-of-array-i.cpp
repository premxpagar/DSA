class Solution {
public:
    vector<long long> resultArray(vector<int>& a, int k) {
        vector<long long> ans(k), dp(k), ndp(k);

        for (int x : a) {
            fill(ndp.begin(), ndp.end(), 0);
            x %= k;

            ndp[x]++;
            for (int r = 0; r < k; r++)
                ndp[(r * x) % k] += dp[r];

            dp = ndp;
            for (int r = 0; r < k; r++)
                ans[r] += dp[r];
        }
        return ans;
    }
};
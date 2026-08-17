class Solution {
    vector<vector<int>> dp;
    vector<int> pre;

    int solve(int l, int r) {
        if (l >= r) return 0;
        if (dp[l][r] != -1) return dp[l][r];

        int ans = 0;

        for (int k = l; k < r; k++) {
            int left = pre[k + 1] - pre[l];
            int right = pre[r + 1] - pre[k + 1];

            if (left < right)
                ans = max(ans, left + solve(l, k));

            else if (left > right)
                ans = max(ans, right + solve(k + 1, r));

            else
                ans = max({ans,
                           left + solve(l, k),
                           right + solve(k + 1, r)});
        }

        return dp[l][r] = ans;
    }

public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();

        pre.resize(n + 1);
        for (int i = 0; i < n; i++)
            pre[i + 1] = pre[i] + stoneValue[i];

        dp.assign(n, vector<int>(n, -1));

        return solve(0, n - 1);
    }
};
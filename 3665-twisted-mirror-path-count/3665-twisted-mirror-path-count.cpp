class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;
        int m = grid.size(), n = grid[0].size();

        vector<vector<array<int, 2>>> go(m, vector<array<int, 2>>(n, {-2, -2}));

        function<int(int, int, int)> get = [&](int i, int j, int d) -> int {
            if (go[i][j][d] != -2) return go[i][j][d];

            int x = i + (d == 1);
            int y = j + (d == 0);

            if (x >= m || y >= n) return go[i][j][d] = -1;

            if (grid[x][y] == 0)
                return go[i][j][d] = x * n + y;

            return go[i][j][d] = get(x, y, 1 - d);
        };

        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (dp[i][j] == 0) continue;

                for (int d = 0; d < 2; d++) {
                    int p = get(i, j, d);

                    if (p != -1) {
                        int x = p / n, y = p % n;
                        dp[x][y] = (dp[x][y] + dp[i][j]) % MOD;
                    }
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};
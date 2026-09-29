class Solution {
    vector<vector<vector<int>>> dp;
    int m, n;

    bool dfs(vector<vector<char>>& g, int i, int j, int bal) {
        bal += g[i][j] == '(' ? 1 : -1;

        if (bal < 0) return false;
        if (i == m - 1 && j == n - 1) return bal == 0;

        if (dp[i][j][bal] != -1)
            return dp[i][j][bal];

        bool ok = false;
        if (i + 1 < m) ok |= dfs(g, i + 1, j, bal);
        if (j + 1 < n) ok |= dfs(g, i, j + 1, bal);

        return dp[i][j][bal] = ok;
    }

public:
    bool hasValidPath(vector<vector<char>>& grid) {
        m = grid.size(), n = grid[0].size();

        if ((m + n - 1) % 2 || grid[0][0] == ')' ||
            grid[m - 1][n - 1] == '(')
            return false;

        dp.assign(m, vector<vector<int>>(n, vector<int>(m + n, -1)));
        return dfs(grid, 0, 0, 0);
    }
};
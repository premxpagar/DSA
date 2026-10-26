class Solution {
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size(), ans = 0;
        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) continue;

                long long sum = 0;
                queue<pair<int, int>> q;
                q.push({i, j});
                sum += grid[i][j];
                grid[i][j] = 0;

                while (!q.empty()) {
                    auto [x, y] = q.front();
                    q.pop();

                    for (int d = 0; d < 4; d++) {
                        int a = x + dx[d], b = y + dy[d];

                        if (a >= 0 && a < m && b >= 0 && b < n &&
                            grid[a][b] > 0) {
                            sum += grid[a][b];
                            q.push({a, b});
                            grid[a][b] = 0;
                        }
                    }
                }

                if (sum % k == 0) ans++;
            }
        }
        return ans;
    }
};
class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size(), n = classroom[0].size();
        int sx, sy, L = 0;

        vector<vector<int>> id(m, vector<int>(n, -1));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S')
                    sx = i, sy = j;
                else if (classroom[i][j] == 'L')
                    id[i][j] = L++;
            }
        }

        int full = (1 << L) - 1;

        // best[x][y][mask] = maximum energy seen
        vector<vector<vector<int>>> best(
            m, vector<vector<int>>(n, vector<int>(1 << L, -1))
        );

        queue<array<int, 4>> q;
        q.push({sx, sy, 0, energy});
        best[sx][sy][0] = energy;

        int steps = 0;
        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                auto [x, y, mask, e] = q.front();
                q.pop();

                if (mask == full)
                    return steps;

                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d], ny = y + dy[d];

                    if (nx < 0 || nx >= m || ny < 0 || ny >= n ||
                        classroom[nx][ny] == 'X')
                        continue;

                    if (e == 0) continue;

                    int ne = e - 1;
                    int nmask = mask;

                    if (classroom[nx][ny] == 'L')
                        nmask |= (1 << id[nx][ny]);

                    if (classroom[nx][ny] == 'R')
                        ne = energy;

                    if (ne <= best[nx][ny][nmask])
                        continue;

                    best[nx][ny][nmask] = ne;
                    q.push({nx, ny, nmask, ne});
                }
            }

            steps++;
        }

        return -1;
    }
};
class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        vector<vector<pair<int,int>>> g(n);
        for (auto& e : edges)
            g[e[0]].push_back({e[1], e[2]});

        const long long INF = 1e18;
        vector<vector<long long>> dist(n, vector<long long>(k + 1, INF));
        using T = tuple<long long, int, int>;
        priority_queue<T, vector<T>, greater<T>> pq;

        dist[0][1] = 0;
        pq.push({0, 0, 1});

        while (!pq.empty()) {
            auto [d, u, cnt] = pq.top();
            pq.pop();

            if (d != dist[u][cnt]) continue;
            if (u == n - 1) return d;

            for (auto [v, w] : g[u]) {
                int c = labels[u] == labels[v] ? cnt + 1 : 1;
                if (c > k) continue;

                if (d + w < dist[v][c]) {
                    dist[v][c] = d + w;
                    pq.push({d + w, v, c});
                }
            }
        }

        return -1;
    }
};
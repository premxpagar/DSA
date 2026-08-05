class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> graph(n);
        
        for (auto &e : invocations)
            graph[e[0]].push_back(e[1]);

        vector<int> suspicious(n, 0);
        queue<int> q;

        q.push(k);
        suspicious[k] = 1;

        // Find all suspicious methods
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : graph[u]) {
                if (!suspicious[v]) {
                    suspicious[v] = 1;
                    q.push(v);
                }
            }
        }

        // If any safe method invokes a suspicious one,
        // nothing can be removed.
        for (auto &e : invocations) {
            if (!suspicious[e[0]] && suspicious[e[1]]) {
                vector<int> ans;
                for (int i = 0; i < n; i++)
                    ans.push_back(i);
                return ans;
            }
        }

        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (!suspicious[i])
                ans.push_back(i);
        }

        return ans;
    }
};
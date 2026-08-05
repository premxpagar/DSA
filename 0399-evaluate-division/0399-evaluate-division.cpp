class Solution {
    unordered_map<string, string> parent;
    unordered_map<string, double> weight;

    string find(string x) {
        if (parent[x] != x) {
            string p = parent[x];
            parent[x] = find(p);
            weight[x] *= weight[p];
        }
        return parent[x];
    }

public:
    vector<double> calcEquation(vector<vector<string>>& equations,
                                vector<double>& values,
                                vector<vector<string>>& queries) {

        for (int i = 0; i < equations.size(); i++) {
            string a = equations[i][0];
            string b = equations[i][1];

            if (!parent.count(a)) {
                parent[a] = a;
                weight[a] = 1.0;
            }
            if (!parent.count(b)) {
                parent[b] = b;
                weight[b] = 1.0;
            }

            string pa = find(a);
            string pb = find(b);

            if (pa != pb) {
                parent[pa] = pb;
                weight[pa] = values[i] * weight[b] / weight[a];
            }
        }

        vector<double> ans;

        for (auto &q : queries) {
            string a = q[0], b = q[1];

            if (!parent.count(a) || !parent.count(b)) {
                ans.push_back(-1.0);
                continue;
            }

            if (find(a) != find(b))
                ans.push_back(-1.0);
            else
                ans.push_back(weight[a] / weight[b]);
        }

        return ans;
    }
};
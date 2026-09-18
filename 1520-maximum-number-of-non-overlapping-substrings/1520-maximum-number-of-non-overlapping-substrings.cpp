class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.size();
        vector<int> l(26, n), r(26, -1);

        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            l[c] = min(l[c], i);
            r[c] = i;
        }

        vector<pair<int,int>> v;

        for (int c = 0; c < 26; c++) {
            if (r[c] == -1) continue;

            int a = l[c], b = r[c];
            bool ok = true;

            for (int i = a; i <= b; i++) {
                int x = s[i] - 'a';
                if (l[x] < a) {
                    ok = false;
                    break;
                }
                b = max(b, r[x]);
            }

            if (ok) v.push_back({a, b});
        }

        sort(v.begin(), v.end(), [](auto &a, auto &b) {
            return a.second < b.second;
        });

        vector<string> ans;
        int end = -1;

        for (auto [a, b] : v) {
            if (a > end) {
                ans.push_back(s.substr(a, b - a + 1));
                end = b;
            }
        }

        return ans;
    }
};
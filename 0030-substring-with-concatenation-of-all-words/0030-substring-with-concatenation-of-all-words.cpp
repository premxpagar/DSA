class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> ans;
        int n = s.size(), w = words[0].size(), total = words.size() * w;
        unordered_map<string, int> need;
        for (auto& x : words) need[x]++;

        for (int i = 0; i < w; i++) {
            unordered_map<string, int> seen;
            int left = i, count = 0;
            for (int j = i; j + w <= n; j += w) {
                string x = s.substr(j, w);
                if (!need.count(x)) {
                    seen.clear(); count = 0; left = j + w;
                } else {
                    seen[x]++; count++;
                    while (seen[x] > need[x]) {
                        seen[s.substr(left, w)]--;
                        left += w; count--;
                    }
                    if (count == (int)words.size()) {
                        ans.push_back(left);
                        seen[s.substr(left, w)]--;
                        left += w; count--;
                    }
                }
            }
        }
        return ans;
    }
};
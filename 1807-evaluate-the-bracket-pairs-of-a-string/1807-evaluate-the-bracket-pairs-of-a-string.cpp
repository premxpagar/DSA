class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string,string> mp;
        for (auto &x : knowledge) mp[x[0]] = x[1];

        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] == ')') {
                string cur;
                int j = i - 1;

                while (j >= 0 && s[j] != '(')
                    cur += s[j--];

                reverse(cur.begin(), cur.end());

                string val = mp.count(cur) ? mp[cur] : "?";
                s.replace(j, i - j + 1, val);
                i = j + val.size();
            }
        }
        return s;
    }
};
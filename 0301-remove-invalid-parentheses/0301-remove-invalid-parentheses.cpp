class Solution {
    vector<string> ans;

    void dfs(string &s, int i, int l, int r, int open, string &cur) {
        if (i == s.size()) {
            if (l == 0 && r == 0 && open == 0)
                ans.push_back(cur);
            return;
        }

        char c = s[i];

        if (c == '(') {
            if (l > 0)
                dfs(s, i + 1, l - 1, r, open, cur);

            cur += c;
            dfs(s, i + 1, l, r, open + 1, cur);
            cur.pop_back();

        } else if (c == ')') {
            if (r > 0)
                dfs(s, i + 1, l, r - 1, open, cur);

            if (open > 0) {
                cur += c;
                dfs(s, i + 1, l, r, open - 1, cur);
                cur.pop_back();
            }

        } else {
            cur += c;
            dfs(s, i + 1, l, r, open, cur);
            cur.pop_back();
        }
    }

public:
    vector<string> removeInvalidParentheses(string s) {
        int l = 0, r = 0;

        for (char c : s) {
            if (c == '(') l++;
            else if (c == ')') {
                if (l) l--;
                else r++;
            }
        }

        string cur;
        dfs(s, 0, l, r, 0, cur);
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());

        return ans;
    }
};
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> mp = {"", "", "abc", "def", "ghi", "jkl",
                             "mno", "pqrs", "tuv", "wxyz"};
        vector<string> ans;
        function<void(int, string)> dfs = [&](int i, string cur) {
            if (i == digits.size()) {
                ans.push_back(cur);
                return;
            }
            for (char c : mp[digits[i] - '0'])
                dfs(i + 1, cur + c);
        };
        dfs(0, "");
        return ans;
    }
};
class Solution {
public:
    string longestPalindrome(string s) {
        int start = 0, len = 0, n = s.size();

        for (int i = 0; i < n; i++) {
            for (int l = i, r = i; l >= 0 && r < n && s[l] == s[r]; l--, r++)
                if (r - l + 1 > len) start = l, len = r - l + 1;

            for (int l = i, r = i + 1; l >= 0 && r < n && s[l] == s[r]; l--, r++)
                if (r - l + 1 > len) start = l, len = r - l + 1;
        }
        return s.substr(start, len);
    }
};
class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // right[i] = number of characters from the suffix of word2
        // that can be matched using word1[i+1 ... n-1].
        vector<int> right(n);

        int j = m - 1;
        int cnt = 0;

        for (int i = n - 1; i >= 0; --i) {
            right[i] = cnt;

            if (j >= 0 && word1[i] == word2[j]) {
                --j;
                ++cnt;
            }
        }

        vector<int> ans;
        ans.reserve(m);

        j = 0;
        bool changed = false;

        for (int i = 0; i < n && j < m; ++i) {

            // Exact match: always take it because smaller index is better.
            if (word1[i] == word2[j]) {
                ans.push_back(i);
                ++j;
            }

            // Mismatch: use our one allowed modification
            // only if the remaining suffix can still be matched.
            else if (!changed && right[i] >= m - 1 - j) {
                ans.push_back(i);
                ++j;
                changed = true;
            }
        }

        if (j == m)
            return ans;

        return {};
    }
};
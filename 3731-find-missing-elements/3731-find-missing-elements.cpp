class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        int low = 101, high = 0;
        bool seen[101] = {};

        for (int x : nums) {
            seen[x] = true;
            low = min(low, x);
            high = max(high, x);
        }

        vector<int> ans;
        for (int i = low; i <= high; i++) {
            if (!seen[i]) ans.push_back(i);
        }

        return ans;
    }
};
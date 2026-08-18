class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();

        // Case 1: k = 1
        if (k == 1) {
            unordered_map<int, int> freq;

            for (int x : nums)
                freq[x]++;

            int ans = -1;

            for (int x : nums) {
                if (freq[x] == 1)
                    ans = max(ans, x);
            }

            return ans;
        }

        // Case 2: k = n
        if (k == n) {
            return *max_element(nums.begin(), nums.end());
        }

        // Case 3: 1 < k < n
        int first = nums[0];
        int last = nums[n - 1];

        int firstCount = count(nums.begin(), nums.end(), first);
        int lastCount = count(nums.begin(), nums.end(), last);

        if (firstCount == 1 && lastCount == 1)
            return max(first, last);

        if (firstCount == 1)
            return first;

        if (lastCount == 1)
            return last;

        return -1;
    }
};
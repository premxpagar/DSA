class Solution {
public:
    int missingInteger(vector<int>& nums) {
        // Find the longest sequential prefix.
        int prefixSum = nums[0];

        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] != nums[i - 1] + 1)
                break;

            prefixSum += nums[i];
        }

        // Check which values already exist.
        bool present[101] = {};

        for (int num : nums)
            present[num] = true;

        // Find the smallest missing value >= prefixSum.
        while (prefixSum <= 100 && present[prefixSum])
            ++prefixSum;

        return prefixSum;
    }
};
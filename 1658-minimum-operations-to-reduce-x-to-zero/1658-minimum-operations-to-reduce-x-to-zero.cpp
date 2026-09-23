class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size(), total = 0;
        for (int v : nums) total += v;

        if (x > total) return -1;

        int target = total - x;
        int sum = 0, l = 0, best = -1;

        for (int r = 0; r < n; r++) {
            sum += nums[r];

            while (sum > target)
                sum -= nums[l++];

            if (sum == target)
                best = max(best, r - l + 1);
        }

        return best == -1 ? -1 : n - best;
    }
};
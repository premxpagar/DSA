class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        vector<int> prefMax(n + 1), suffMin(n + 1, INT_MAX), drops(n);

        for (int i = 0; i < n; i++)
            prefMax[i + 1] = max(prefMax[i], nums[i]);

        for (int i = n - 1; i >= 0; i--)
            suffMin[i] = min(nums[i], suffMin[i + 1]);

        for (int i = 1; i < n; i++)
            drops[i] = drops[i - 1] + (nums[i - 1] > nums[i]);

        auto check = [&](int k) {
            for (int i = 0; i < n; i += k) {
                int j = i + k - 1;
                int d = drops[j] - drops[i] + (nums[j] > nums[i]);
                if (d > 1 || prefMax[i] > suffMin[i]) return false;
            }
            return true;
        };

        for (int k = 1; k <= n / k; k++) {
            if (n % k == 0) {
                if (check(k)) ans += k;
                if (k != n / k && check(n / k)) ans += n / k;
            }
        }
        return ans;
    }
};
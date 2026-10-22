class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int z = find(nums.begin(), nums.end(), 0) - nums.begin();
        auto check = [&](int d) {
            for (int i = 1; i < n; i++)
                if (nums[(z + (i-1)*d + n) % n] >
                    nums[(z + i*d + n) % n]) return false;
            return true;
        };

        int ans = INT_MAX;
        if (check(1)) ans = min({ans, z, n-z+2});
        if (check(-1)) ans = min({ans, z+2, n-z});
        return ans == INT_MAX ? -1 : ans;
    }
};
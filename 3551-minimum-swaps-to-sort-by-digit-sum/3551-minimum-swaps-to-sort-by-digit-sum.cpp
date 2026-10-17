class Solution {
public:
    int minSwaps(vector<int>& nums) {
        auto digitSum = [](int x) {
            int sum = 0;
            while (x) {
                sum += x % 10;
                x /= 10;
            }
            return sum;
        };

        vector<pair<int, int>> a;
        for (int i = 0; i < nums.size(); i++)
            a.push_back({nums[i], i});

        sort(a.begin(), a.end(), [&](auto x, auto y) {
            int sx = digitSum(x.first), sy = digitSum(y.first);
            return sx == sy ? x.first < y.first : sx < sy;
        });

        int n = nums.size(), ans = 0;
        vector<bool> vis(n, false);

        for (int i = 0; i < n; i++) {
            if (vis[i] || a[i].second == i) continue;

            int j = i, len = 0;
            while (!vis[j]) {
                vis[j] = true;
                j = a[j].second;
                len++;
            }
            ans += len - 1;
        }
        return ans;
    }
};
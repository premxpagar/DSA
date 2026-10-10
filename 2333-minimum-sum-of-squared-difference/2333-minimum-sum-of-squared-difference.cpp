class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2,
                               int k1, int k2) {
        int n = nums1.size(), k = k1 + k2;
        vector<int> d(n);
        int mx = 0;
        long long total = 0;

        for (int i = 0; i < n; i++) {
            d[i] = abs(nums1[i] - nums2[i]);
            total += d[i];
            mx = max(mx, d[i]);
        }

        if (total <= k) return 0;

        int l = 0, r = mx;
        while (l < r) {
            int mid = l + (r - l) / 2;
            long long need = 0;
            for (int x : d) need += max(0, x - mid);

            if (need <= k) r = mid;
            else l = mid + 1;
        }

        long long ans = 0;
        for (int &x : d) {
            k -= max(0, x - l);
            x = min(x, l);
        }

        for (int &x : d) {
            if (k > 0 && x == l && l > 0) {
                x--;
                k--;
            }
            ans += 1LL * x * x;
        }

        return ans;
    }
};
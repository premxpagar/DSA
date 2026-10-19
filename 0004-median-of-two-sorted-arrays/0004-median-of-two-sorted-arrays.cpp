class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size())
            return findMedianSortedArrays(nums2, nums1);

        int m = nums1.size(), n = nums2.size();
        int l = 0, r = m;

        while (l <= r) {
            int i = l + (r - l) / 2;
            int j = (m + n + 1) / 2 - i;

            int a = (i == 0) ? INT_MIN : nums1[i - 1];
            int b = (i == m) ? INT_MAX : nums1[i];
            int c = (j == 0) ? INT_MIN : nums2[j - 1];
            int d = (j == n) ? INT_MAX : nums2[j];

            if (a <= d && c <= b) {
                if ((m + n) % 2)
                    return max(a, c);
                return (max(a, c) + (double)min(b, d)) / 2.0;
            }

            if (a > d) r = i - 1;
            else l = i + 1;
        }
        return 0.0;
    }
};
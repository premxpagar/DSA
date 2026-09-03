class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int mnOdd = INT_MAX, mnEven = INT_MAX;

        for (int x : nums1) {
            if (x & 1) mnOdd = min(mnOdd, x);
            else mnEven = min(mnEven, x);
        }

        // Already all same parity
        if (mnOdd == INT_MAX || mnEven == INT_MAX)
            return true;

        // Smallest odd can convert every larger even to odd.
        return mnOdd < mnEven;
    }
};
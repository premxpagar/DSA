class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> mp;

        for (auto &x : reservedSeats)
            if (x[1] >= 2 && x[1] <= 9)
                mp[x[0]] |= 1 << x[1];

        long long ans = 2LL * (n - mp.size());

        for (auto &[row, m] : mp) {
            bool L = !(m & 0b0000111100); // 2-5
            bool R = !(m & 0b1111000000); // 6-9
            bool M = !(m & 0b0011110000); // 4-7

            ans += L && R ? 2 : (L || R || M);
        }

        return ans;
    }
};
class Solution {
public:
    int smallestNumber(int n, int t) {
        for (;; ++n) {
            int prod = 1;

            for (int cur = n; cur; cur /= 10)
                prod *= cur % 10;

            if (prod % t == 0)
                return n;
        }
    }
};
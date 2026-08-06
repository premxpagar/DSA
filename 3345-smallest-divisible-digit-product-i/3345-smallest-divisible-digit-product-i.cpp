class Solution {
public:
    int smallestNumber(int n, int t) {

        auto ok = [&](int x) {
            int prod = 1;
            while (x) {
                prod *= x % 10;
                x /= 10;
            }
            return prod % t == 0;
        };

        while (!ok(n))
            n++;

        return n;
    }
};
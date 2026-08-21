class Solution {
public:
    long long findKthSmallest(vector<int>& coins, int k) {
        int n = coins.size();

        auto count = [&](long long x) {
            long long ans = 0;

            for (int mask = 1; mask < (1 << n); mask++) {
                long long lcm = 1;
                int bits = 0;
                bool valid = true;

                for (int i = 0; i < n; i++) {
                    if (mask & (1 << i)) {
                        bits++;

                        long long g = gcd(lcm, (long long)coins[i]);

                        // Avoid overflow and unnecessary calculation
                        if (lcm > x / (coins[i] / g)) {
                            valid = false;
                            break;
                        }

                        lcm = lcm / g * coins[i];
                    }
                }

                if (!valid) continue;

                long long ways = x / lcm;

                if (bits % 2)
                    ans += ways;   // add odd subsets
                else
                    ans -= ways;   // subtract even subsets
            }

            return ans;
        };

        long long low = 1, high = 1LL * (*min_element(coins.begin(), coins.end())) * k;

        while (low < high) {
            long long mid = low + (high - low) / 2;

            if (count(mid) >= k)
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};
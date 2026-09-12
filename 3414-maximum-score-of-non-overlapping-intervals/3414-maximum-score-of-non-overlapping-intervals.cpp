class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        vector<pair<vector<int>, int>> a;
        for (int i = 0; i < n; i++)
            a.push_back({intervals[i], i});

        sort(a.begin(), a.end(), [](auto &x, auto &y) {
            return x.first[1] < y.first[1];
        });

        vector<vector<long long>> dp(n + 1, vector<long long>(5, 0));
        vector<vector<vector<int>>> res(n + 1, vector<vector<int>>(5));

        for (int i = 1; i <= n; i++) {
            for (int k = 1; k <= 4; k++) {
                dp[i][k] = dp[i - 1][k];
                res[i][k] = res[i - 1][k];

                int l = a[i - 1].first[0];

                int j = lower_bound(
                    a.begin(), a.begin() + i - 1, l,
                    [](const auto &x, int val) {
                        return x.first[1] < val;
                    }) - a.begin();

                long long val = dp[j][k - 1] + a[i - 1].first[2];
                vector<int> cur = res[j][k - 1];
                cur.push_back(a[i - 1].second);
                sort(cur.begin(), cur.end());

                if (val > dp[i][k] ||
                    (val == dp[i][k] && cur < res[i][k])) {
                    dp[i][k] = val;
                    res[i][k] = cur;
                }
            }
        }

        vector<int> answer;
        long long best = -1;

        for (int k = 1; k <= 4; k++) {
            if (dp[n][k] > best ||
                (dp[n][k] == best && res[n][k] < answer)) {
                best = dp[n][k];
                answer = res[n][k];
            }
        }

        return answer;
    }
};
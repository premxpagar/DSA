class Solution {
    static const int MOD = 1e9 + 7;
    long long sum[400005], sq[400005], lazy[400005];

    void push(int node, int l, int r) {
        if (!lazy[node]) return;

        long long v = lazy[node], len = r - l + 1;
        sq[node] = (sq[node] + 2 * v * sum[node] + v * v % MOD * len) % MOD;
        sum[node] = (sum[node] + v * len) % MOD;

        if (l != r) {
            lazy[node * 2] += v;
            lazy[node * 2 + 1] += v;
        }
        lazy[node] = 0;
    }

    void update(int node, int l, int r, int ql, int qr) {
        push(node, l, r);
        if (r < ql || l > qr) return;

        if (ql <= l && r <= qr) {
            lazy[node]++;
            push(node, l, r);
            return;
        }

        int mid = (l + r) / 2;
        update(node * 2, l, mid, ql, qr);
        update(node * 2 + 1, mid + 1, r, ql, qr);

        sum[node] = (sum[node * 2] + sum[node * 2 + 1]) % MOD;
        sq[node] = (sq[node * 2] + sq[node * 2 + 1]) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        memset(sum, 0, sizeof(sum));
        memset(sq, 0, sizeof(sq));
        memset(lazy, 0, sizeof(lazy));

        vector<int> last(100001, -1);
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            update(1, 0, n - 1, last[nums[i]] + 1, i);
            last[nums[i]] = i;
            ans = (ans + sq[1]) % MOD;
        }

        return ans;
    }
};
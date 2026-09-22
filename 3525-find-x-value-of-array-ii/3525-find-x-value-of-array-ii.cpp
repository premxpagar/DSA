class Solution {
    int k;
    struct N {
        int p = 1;
        long long c[5] = {};
    };

    vector<N> t;

    N merge(N a, N b) {
        N c;
        c.p = a.p * b.p % k;

        for (int i = 0; i < k; i++) {
            c.c[i] += a.c[i];
            c.c[a.p * i % k] += b.c[i];
        }
        return c;
    }

    void build(int p, int l, int r, vector<int>& a) {
        if (l == r) {
            t[p].p = a[l] % k;
            t[p].c[t[p].p] = 1;
            return;
        }

        int m = (l + r) / 2;
        build(p*2, l, m, a);
        build(p*2+1, m+1, r, a);
        t[p] = merge(t[p*2], t[p*2+1]);
    }

    void update(int p, int l, int r, int i, int x) {
        if (l == r) {
            t[p] = N();
            t[p].p = x % k;
            t[p].c[t[p].p] = 1;
            return;
        }

        int m = (l + r) / 2;
        if (i <= m) update(p*2, l, m, i, x);
        else update(p*2+1, m+1, r, i, x);

        t[p] = merge(t[p*2], t[p*2+1]);
    }

    N query(int p, int l, int r, int s) {
        if (s <= l) return t[p];

        int m = (l + r) / 2;
        if (s > m) return query(p*2+1, m+1, r, s);

        return merge(query(p*2, l, m, s), t[p*2+1]);
    }

public:
    vector<int> resultArray(vector<int>& nums, int K,
                            vector<vector<int>>& q) {
        k = K;
        int n = nums.size();
        t.resize(4 * n);

        build(1, 0, n-1, nums);

        vector<int> ans;
        for (auto x : q) {
            update(1, 0, n-1, x[0], x[1]);
            ans.push_back(query(1, 0, n-1, x[2]).c[x[3]]);
        }

        return ans;
    }
};
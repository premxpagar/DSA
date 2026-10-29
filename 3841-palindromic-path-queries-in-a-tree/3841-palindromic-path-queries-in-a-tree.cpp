class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        vector<vector<int>> g(n);
        for (auto& e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        vector<int> par(n), dep(n), sz(n), heavy(n, -1), head(n), pos(n);
        int timer = 0;

        function<void(int,int)> dfs = [&](int u, int p) {
            par[u] = p;
            sz[u] = 1;
            int mx = 0;
            for (int v : g[u]) if (v != p) {
                dep[v] = dep[u] + 1;
                dfs(v, u);
                sz[u] += sz[v];
                if (sz[v] > mx) mx = sz[v], heavy[u] = v;
            }
        };
        dfs(0, -1);

        function<void(int,int)> decomp = [&](int u, int h) {
            head[u] = h;
            pos[u] = timer++;
            if (heavy[u] != -1) decomp(heavy[u], h);
            for (int v : g[u])
                if (v != par[u] && v != heavy[u]) decomp(v, v);
        };
        decomp(0, 0);

        vector<int> seg(4*n);
        function<void(int,int,int)> build = [&](int x, int l, int r) {
            if (l == r) {
                int u = find(pos.begin(), pos.end(), l) - pos.begin();
                seg[x] = 1 << (s[u] - 'a');
                return;
            }
            int m = (l+r)/2;
            build(x*2,l,m);
            build(x*2+1,m+1,r);
            seg[x] = seg[x*2] ^ seg[x*2+1];
        };

        function<void(int,int,int,int,int)> upd = [&](int x,int l,int r,int p,int val) {
            if(l==r){seg[x]=val;return;}
            int m=(l+r)/2;
            if(p<=m) upd(x*2,l,m,p,val);
            else upd(x*2+1,m+1,r,p,val);
            seg[x]=seg[x*2]^seg[x*2+1];
        };

        function<int(int,int,int,int,int)> get = [&](int x,int l,int r,int a,int b) {
            if(a>r||b<l) return 0;
            if(a<=l&&r<=b) return seg[x];
            int m=(l+r)/2;
            return get(x*2,l,m,a,b)^get(x*2+1,m+1,r,a,b);
        };

        vector<int> at(n);
        for(int i=0;i<n;i++) at[pos[i]]=i;
        function<void(int,int,int)> build2 = [&](int x,int l,int r) {
            if(l==r){seg[x]=1<<(s[at[l]]-'a');return;}
            int m=(l+r)/2;
            build2(x*2,l,m); build2(x*2+1,m+1,r);
            seg[x]=seg[x*2]^seg[x*2+1];
        };
        build2(1,0,n-1);

        auto path = [&](int u,int v) {
            int mask=0;
            while(head[u]!=head[v]) {
                if(dep[head[u]]<dep[head[v]]) swap(u,v);
                mask ^= get(1,0,n-1,pos[head[u]],pos[u]);
                u=par[head[u]];
            }
            if(dep[u]>dep[v]) swap(u,v);
            mask ^= get(1,0,n-1,pos[u],pos[v]);
            return mask;
        };

        vector<bool> ans;
        for(auto& q:queries) {
            string op; int u,v;
            stringstream ss(q);
            ss>>op>>u;
            if(op=="update") {
                char c; ss>>c;
                s[u]=c;
                upd(1,0,n-1,pos[u],1<<(c-'a'));
            } else {
                ss>>v;
                int m=path(u,v);
                ans.push_back((m&(m-1))==0);
            }
        }
        return ans;
    }
};
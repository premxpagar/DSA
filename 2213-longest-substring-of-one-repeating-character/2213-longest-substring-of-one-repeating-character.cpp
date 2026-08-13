#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Renamed from TreeNode to SegNode to prevent collision with LeetCode's built-in TreeNode
struct SegNode {
    int max_len;
    int pref_len;
    int suff_len;
    int size;
    char pref_char;
    char suff_char;
};

class Solution {
    vector<SegNode> tree;

    void push_up(int node) {
        int left = node << 1;
        int right = node << 1 | 1;
        
        tree[node].size = tree[left].size + tree[right].size;
        tree[node].pref_char = tree[left].pref_char;
        tree[node].suff_char = tree[right].suff_char;
        
        // Calculate prefix length
        tree[node].pref_len = tree[left].pref_len;
        if (tree[left].pref_len == tree[left].size && tree[left].suff_char == tree[right].pref_char) {
            tree[node].pref_len += tree[right].pref_len;
        }
        
        // Calculate suffix length
        tree[node].suff_len = tree[right].suff_len;
        if (tree[right].suff_len == tree[right].size && tree[right].pref_char == tree[left].suff_char) {
            tree[node].suff_len += tree[left].suff_len;
        }
        
        // Calculate max contiguous repeating character length
        tree[node].max_len = max(tree[left].max_len, tree[right].max_len);
        if (tree[left].suff_char == tree[right].pref_char) {
            tree[node].max_len = max(tree[node].max_len, tree[left].suff_len + tree[right].pref_len);
        }
    }

    void build(int node, int start, int end, const string& s) {
        if (start == end) {
            tree[node] = {1, 1, 1, 1, s[start], s[start]};
            return;
        }
        int mid = start + (end - start) / 2;
        build(node << 1, start, mid, s);
        build(node << 1 | 1, mid + 1, end, s);
        push_up(node);
    }

    void update(int node, int start, int end, int idx, char val) {
        if (start == end) {
            tree[node] = {1, 1, 1, 1, val, val};
            return;
        }
        int mid = start + (end - start) / 2;
        if (idx <= mid) {
            update(node << 1, start, mid, idx, val);
        } else {
            update(node << 1 | 1, mid + 1, end, idx, val);
        }
        push_up(node);
    }

public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        int n = s.length();
        int k = queryCharacters.length();
        
        // 4 * n is the standard safe upper bound for a segment tree array
        tree.resize(4 * n + 1);
        build(1, 0, n - 1, s);
        
        vector<int> ans;
        ans.reserve(k); // Prevent runtime reallocations for better performance
        
        for (int i = 0; i < k; ++i) {
            update(1, 0, n - 1, queryIndices[i], queryCharacters[i]);
            // tree[1].max_len always holds the answer for the full string [0, n-1]
            ans.push_back(tree[1].max_len); 
        }
        
        return ans;
    }
};
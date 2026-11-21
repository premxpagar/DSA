class Solution:
    def findSubtreeSizes(self, parent: List[int], s: str) -> List[int]:
        n = len(parent)
        children = [[] for _ in range(n)]

        # Build original tree
        for i in range(1, n):
            children[parent[i]].append(i)

        # Find the closest ancestor with the same character
        new_parent = parent[:]
        last = {}

        def dfs(node):
            ch = s[node]
            old = last.get(ch)

            if old is not None:
                new_parent[node] = old

            last[ch] = node

            for child in children[node]:
                dfs(child)

            if old is None:
                last.pop(ch)
            else:
                last[ch] = old

        dfs(0)

        # Build the modified tree
        children = [[] for _ in range(n)]
        for i in range(1, n):
            children[new_parent[i]].append(i)

        # Calculate subtree sizes
        ans = [1] * n

        def calculate(node):
            for child in children[node]:
                ans[node] += calculate(child)
            return ans[node]

        calculate(0)
        return ans
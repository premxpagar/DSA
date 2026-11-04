from typing import List

class Fenwick:
    def __init__(self, n):
        self.n = n
        self.bit = [0] * (n + 1)

    def update(self, i, val):
        while i <= self.n:
            self.bit[i] += val
            i += i & -i

    def query(self, i):
        s = 0
        while i > 0:
            s += self.bit[i]
            i -= i & -i
        return s

    def kth(self, k):
        idx = 0
        step = 1 << (self.n.bit_length() - 1)

        while step:
            nxt = idx + step
            if nxt <= self.n and self.bit[nxt] < k:
                idx = nxt
                k -= self.bit[nxt]
            step >>= 1

        return idx + 1


class Solution:
    def minOperations(self, nums: List[int], x: int, k: int) -> int:
        n = len(nums)

        vals = sorted(set(nums))
        m = len(vals)
        pos = {v: i + 1 for i, v in enumerate(vals)}

        count = Fenwick(m)
        sums = Fenwick(m)

        def add(v, delta):
            p = pos[v]
            count.update(p, delta)
            sums.update(p, v * delta)

        def get_cost():
            mid_pos = count.kth((x + 1) // 2)
            median = vals[mid_pos - 1]

            left_count = count.query(mid_pos)
            left_sum = sums.query(mid_pos)

            right_count = x - left_count
            right_sum = total_sum - left_sum

            return (median * left_count - left_sum +
                    right_sum - median * right_count)

        costs = []
        total_sum = 0

        for i in range(n):
            add(nums[i], 1)
            total_sum += nums[i]

            if i >= x:
                add(nums[i - x], -1)
                total_sum -= nums[i - x]

            if i >= x - 1:
                costs.append(get_cost())

        inf = float('inf')
        dp = [[inf] * (n + 1) for _ in range(k + 1)]
        dp[0] = [0] * (n + 1)

        for j in range(1, k + 1):
            for i in range(x, n + 1):
                dp[j][i] = dp[j][i - 1]

                cost = costs[i - x]
                dp[j][i] = min(
                    dp[j][i],
                    dp[j - 1][i - x] + cost
                )

        return dp[k][n]
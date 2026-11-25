
from collections import defaultdict
from typing import List

class Solution:
    def smallestUniqueSubarray(self, nums: List[int]) -> int:
        n = len(nums)
        base = 91138233
        mod1 = 10**9 + 7
        mod2 = 10**9 + 9

        def check(length):
            power1 = pow(base, length - 1, mod1)
            power2 = pow(base, length - 1, mod2)

            h1 = h2 = 0

            for i in range(length):
                h1 = (h1 * base + nums[i]) % mod1
                h2 = (h2 * base + nums[i]) % mod2

            freq = defaultdict(int)
            freq[(h1, h2)] += 1

            for i in range(length, n):
                old = nums[i - length]
                new = nums[i]

                h1 = ((h1 - old * power1) * base + new) % mod1
                h2 = ((h2 - old * power2) * base + new) % mod2

                freq[(h1, h2)] += 1

            return any(count == 1 for count in freq.values())

        left, right = 1, n
        ans = n

        while left <= right:
            mid = (left + right) // 2

            if check(mid):
                ans = mid
                right = mid - 1
            else:
                left = mid + 1

        return ans

import heapq
from typing import List

class Solution:
    def busiestServers(self, k: int, arrival: List[int], load: List[int]) -> List[int]:
        bit = [0] + [i & -i for i in range(1, k + 1)]

        def update(i, val):
            i += 1
            while i <= k:
                bit[i] += val
                i += i & -i

        def query(i):
            s = 0
            while i > 0:
                s += bit[i]
                i -= i & -i
            return s

        def kth(rank):
            idx = 0
            step = 1 << (k.bit_length() - 1)
            while step:
                nxt = idx + step
                if nxt <= k and bit[nxt] < rank:
                    idx = nxt
                    rank -= bit[nxt]
                step >>= 1
            return idx

        busy = []
        count = [0] * k

        for i in range(len(arrival)):
            t = arrival[i]

            while busy and busy[0][0] <= t:
                _, server = heapq.heappop(busy)
                update(server, 1)

            total = query(k)
            if total == 0:
                continue

            start = i % k
            before = query(start)

            rank = before + 1 if before < total else 1
            server = kth(rank)

            update(server, -1)
            count[server] += 1

            heapq.heappush(busy, (t + load[i], server))

        maximum = max(count)
        return [i for i in range(k) if count[i] == maximum]
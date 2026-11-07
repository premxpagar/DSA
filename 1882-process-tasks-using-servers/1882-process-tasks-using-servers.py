import heapq
from typing import List

class Solution:
    def assignTasks(self, servers: List[int], tasks: List[int]) -> List[int]:
        free = [(w, i) for i, w in enumerate(servers)]
        heapq.heapify(free)

        busy = []
        ans = []

        for j, task in enumerate(tasks):
            while busy and busy[0][0] <= j:
                end, w, i = heapq.heappop(busy)
                heapq.heappush(free, (w, i))

            if free:
                w, i = heapq.heappop(free)
                heapq.heappush(busy, (j + task, w, i))
            else:
                end, w, i = heapq.heappop(busy)
                heapq.heappush(busy, (end + task, w, i))

            ans.append(i)

        return ans
class Solution:
    def minMoves(self, nums: List[int]) -> int:
        smallest = min(nums)
        moves = 0

        for num in nums:
            moves += num - smallest

        return moves
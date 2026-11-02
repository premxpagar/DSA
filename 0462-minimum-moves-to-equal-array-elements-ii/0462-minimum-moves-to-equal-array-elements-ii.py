class Solution:
    def minMoves2(self, nums: List[int]) -> int:
        nums.sort()

        middle = nums[len(nums) // 2]

        moves = 0

        for num in nums:
            moves += abs(num - middle)

        return moves
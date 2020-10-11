class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        elements = []
        answer = []

        def dfs(index, start):

            answer.append(elements[:])

            if index == len(nums):
                return

            for i in range(start, len(nums)):
                elements.append(nums[i])
                dfs(index+1, i+1)
                elements.pop()

        dfs(0, 0)
        return answer

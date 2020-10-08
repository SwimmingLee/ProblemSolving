class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        answer = []
        element = []

        def dfs(index):
            if index == len(nums):
                print(element)
                answer.append(element[:])
                return

            for i in range(len(nums)):
                if nums[i] not in element:
                    element.append(nums[i])
                    dfs(index+1)
                    element.pop()
        dfs(0)
        return answer

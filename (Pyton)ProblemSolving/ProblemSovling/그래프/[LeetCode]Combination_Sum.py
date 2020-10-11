class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        elements = []
        answer = []

        def dfs(sum_ele, start):
            if sum_ele >= target:
                if sum_ele == target:
                    answer.append(elements[:])
                return

            for i in range(start, len(candidates)):
                num = candidates[i]
                elements.append(num)
                dfs(sum_ele+num, i)
                elements.pop()

        dfs(0, 0)
        return answer

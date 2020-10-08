class Solution:
    def combine(self, n: int, k: int) -> List[List[int]]:
        answer = []
        elements = []

        def dfs(index, start):
            if index == k:
                answer.append(elements[:])
                return

            for i in range(start, n+1):
                elements.append(i)
                dfs(index+1, i+1)
                elements.pop()

        dfs(0, 1)
        return answer

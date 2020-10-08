import collections


class Solution:
    def letterCombinations(self, digits: str) -> List[str]:
        dic = {"2": "abc", "3": "def", "4": "ghi", "5": "jkl",
               "6": "mno", "7": "pqrs", "8": "tuv", "9": "wxyz"}
        answer = []

        def dfs(depth, letter):
            if depth == len(digits):
                answer.append(letter)
                return

            alphas = dic[digits[depth]]
            for alpha in alphas:
                dfs(depth+1, letter + alpha)

        if not digits:
            return []

        dfs(0, "")
        return answer

class Solution:
    def removeDuplicateLetters(self, s: str) -> str:
        str = ""
        for c in s:
            if not c in str:
                str += c
            else:
                cmp_str = str.replace(c, "") + c
                if cmp_str < str:
                    str = cmp_str
        return str

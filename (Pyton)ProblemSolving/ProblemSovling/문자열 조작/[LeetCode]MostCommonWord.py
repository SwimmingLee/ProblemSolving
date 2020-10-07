import collections
import re


class Solution:
    # def mostCommonWord(self, paragraph: str, banned: List[str]) -> str:
    #     paragraph = re.sub(r'[^\w]', ' ', paragraph).lower().split()
    #     print(paragraph)
    #     word_cnt = collections.defaultdict(int)
    #     for word in paragraph:
    #         if word in banned:
    #             continue
    #         word_cnt[word] += 1

    #     return max(word_cnt, key=word_cnt.get)

    def mostCommonWord(self, paragraph: str, banned: List[str]) -> str:
        words = [word for word in re.sub(r'[^\w]', ' ', paragraph)
                 .lower().split()
                 if word not in banned]
        word_cnt = collections.Counter(words)
        return word_cnt.most_common(1)[0][0]

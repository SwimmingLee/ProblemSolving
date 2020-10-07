import collections


class Solution:
    # def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
    #     word_pair = [("".join(sorted(word)), word) for word in strs]
    #     word_pair.sort(key=lambda x: x[0])

    #     group_chk = []
    #     answer, group = [], []
    #     for pair in word_pair:
    #         word_key, word = pair[0], pair[1]
    #         if not word_key in group_chk:
    #             group_chk.append(word_key)
    #             if len(group):
    #                 answer.append(group)
    #                 group = []

    #         group.append(word)
    #     answer.append(group)
    #     return answer
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        anagrams = collections.defaultdict(list)

        for word in strs:
            anagrams[''.join(sorted(word))].append(word)

        return anagrams.values()

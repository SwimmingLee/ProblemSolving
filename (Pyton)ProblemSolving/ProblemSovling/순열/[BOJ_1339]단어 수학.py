import sys

input = sys.stdin.readline

n_alpha = 26
n_word = int(input())
words = [0 for _ in range(n_word)]
alpha = [0 for _ in range(n_alpha)]
for idx in range(n_word):
    words[idx] = input().rstrip()
    word_sz = len(words[idx])
    for i, c in enumerate(words[idx][::-1]):
        alpha[ord(c)-ord('A')] += 10 ** i

alpha.sort(reverse=True)
answer = 0
weight = 9
for c in alpha:
    if c == 0:
        break
    answer += c * weight
    weight -= 1

print(answer)

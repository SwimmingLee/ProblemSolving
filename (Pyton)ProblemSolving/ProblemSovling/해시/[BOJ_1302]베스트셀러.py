import collections

hash_dict = collections.defaultdict(int)
answer = ""
total_cnt = 0
N = int(input())
for _ in range(N):
    word = input()
    hash_dict[word] += 1
    tmp = hash_dict[word]
    if tmp > total_cnt:
        total_cnt = tmp
        answer = word
    elif tmp == total_cnt:
        if answer > word:
            answer = word

print(answer)

import sys

input = sys.stdin.readline
TC = int(input())
for _ in range(TC):
    n_note_a = int(input())
    note_a = set(list(map(int, input().split())))
    n_note_b = int(input())
    note_b = list(map(int, input().split()))
    for num in note_b:
        if num in note_a:
            print(1)
        else:
            print(0)

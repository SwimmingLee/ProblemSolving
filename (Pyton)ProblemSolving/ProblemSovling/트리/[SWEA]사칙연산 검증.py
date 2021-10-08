# import sys
T = int(input())
op = "+-*/"
for test_case in range(1, T + 1):
    N = int(input())
    answer = 1
    for _ in range(N):
        in_node = input().split()
        has_op = False
        if op.find(in_node[1]) != -1:
            has_op = True

        if has_op and len(in_node) != 4:
            answer = 0
        elif not has_op and len(in_node) != 2:
            answer = 0
    print('#', test_case, answer)

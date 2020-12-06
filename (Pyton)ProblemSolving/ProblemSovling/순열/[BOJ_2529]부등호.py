import sys

input = sys.stdin.readline
n_sign = int(input())
equal_signs = list(input().split())
equals = [0 for _ in range(n_sign+1)]
visited = [False for _ in range(10)]
max_equals, min_equals = '', '9999999999999999'
max_num, min_num = 0, -1

def dfs(index):
    global max_num, min_num
    global max_equals, min_equals
    if index > n_sign:
        str_equals = ''.join(equals)
        num_equals = int(str_equals)

        if num_equals > max_num:
            max_num = num_equals
            max_equals = str_equals

        if min_num == -1 or num_equals < min_num:
            min_num = num_equals
            min_equals = str_equals
        return
    
    for num in range(10):
        isok = False
        if index == 0:
            isok = True
        elif equal_signs[index - 1] == '>':
            if int(equals[index-1]) > num:
                isok = True
        else: # equal_signs[index -1] == '<':
            if int(equals[index-1]) < num:
                isok = True
        
        if isok and not visited[num]:
            visited[num] = True
            equals[index] = str(num) 
            dfs(index+1) 
            visited[num] = False

dfs(0)
print(max_equals)
print(min_equals)
import sys

input = sys.stdin.readline
N = int(input())
A = list(map(int, input().split()))
cmd_cnt = list(map(int, input().split()))

# 연산자 사이에서 어떤 연산자를 고를지 완전탐색한다. 
# 같은 연산자를 고르게 되면 중복처리를 어떻게 할 것인가? 
# dfs에서 하나를 고르게 하면 딱히 중복처리를 할게 없다. 굳굳!
min_number, max_number = 1e10, -1e10
def dfs(index, number):
    global min_number, max_number
    # 연산자는 숫자의 개수-1 개 만큼 있을 수 있다.
    if index == N - 1:
        if min_number > number:
            min_number = number
        if max_number < number:
            max_number = number
        return
    for i in range(4):
        if cmd_cnt[i] > 0:
            cmd_cnt[i] -= 1
            if i == 0:
                dfs(index+1, number + A[index+1])
            elif i == 1:
                dfs(index+1, number - A[index+1])
            elif i == 2:
                dfs(index+1, number * A[index+1])
            else:
                if number < 0 and A[index+1] > 0:
                    dfs(index+1, -(-number // A[index+1]))
                else:
                    dfs(index+1, number // A[index+1])
                    
            cmd_cnt[i] += 1

dfs(0, A[0])
print(max_number)
print(min_number)
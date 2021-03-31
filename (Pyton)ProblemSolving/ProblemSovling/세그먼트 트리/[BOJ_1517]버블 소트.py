import sys
import math
input = sys.stdin.readline
N = int(input())
A = list(map(int, input().split()))

# 배열의 끝 부터 순회하면서 자신보다 작은 숫자들이 몇개 있는지 확인하기 (작은 숫자 들의 갯수 == 스왑 갯수)
size = math.ceil(math.log(N)/math.log(2))
tree = [0] * (2**(size+1))


def querySegTree(node, first, last, left, right):
    if last < left or right < first:
        return 0
    if left <= first and last <= right:
        return tree[node]

    mid = (first + last) // 2
    return querySegTree(node*2, first, mid, left, right) + querySegTree(node*2+1, mid+1, last, left, right)


def updateSegTree(node, first, last, idx):
    if last < idx or idx < first:
        return
    if first == last:
        tree[node] += 1
        return

    mid = (first + last) // 2
    updateSegTree(node*2, first, mid, idx)
    updateSegTree(node*2+1, mid+1, last, idx)
    tree[node] = tree[node*2] + tree[node*2+1]


# A에 대해서 좌표압축하는 것이 좋을 듯...
# 정렬되고 나면 A[i] --> i 이렇게 말야
sorted_array = sorted(enumerate(A), key=lambda x: x[1])

B = [0] * N
cnt = 0
pre = -1
for idx, value in sorted_array:
    if pre != value:
        cnt += 1
    B[idx] = cnt
    pre = value


answer = 0
for i in range(N-1, -1, -1):
    answer += querySegTree(1, 0, N-1, 0, B[i]-1)
    updateSegTree(1, 0, N-1, B[i])

print(answer)


# 그리고 자신의 위치를 업데이트 하기

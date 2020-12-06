import sys
input = sys.stdin.readline

elements = []
def dfs(index, start, array):
    if index == 6:
        string = ''.join(str(array[e])+' ' for e in elements)
        print(string)
        return
    
    for i in range(start, len(array)):
        elements.append(i)
        dfs(index+1, i+1, array)
        elements.pop()

while True:
    N = list(map(int, input().split()))
    if N[0] == 0:
        break
    array = N[1:]
    dfs(0, 0, array)
    print()

    
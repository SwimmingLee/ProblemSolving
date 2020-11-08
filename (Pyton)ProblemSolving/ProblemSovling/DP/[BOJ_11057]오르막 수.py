N = int(input())
cnt = 0
cache = [1 for _ in range(10)]

while cnt != N:
    for i in range(8, -1, -1):
        cache[i] = cache[i] + cache[i+1]
        cache[i] %= 10007
    cnt += 1
print(cache[0])

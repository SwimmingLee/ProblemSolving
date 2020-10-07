import sys
from math import sqrt


def getPrime(n):
    a, b = 0, 1000000
    left = 0
    while left < len(prime):
        num1 = prime[left]
        num2 = n - num1

        if num1 > num2:
            break

        if prime_chk[num2] == False and (b - a) > (num2 - num1):
            a, b = num1, num2

        left += 1
    return (a, b)


input = sys.stdin.readline
max_num = 10001

prime_chk = [0] * max_num
prime = []
for i in range(2, max_num):
    if prime_chk[i] == False:
        prime.append(i)
        for j in range(i*i, max_num, i):
            prime_chk[j] = True


TC = int(input())

for _ in range(TC):
    n = int(input())
    a, b = getPrime(n)
    print(a, b)

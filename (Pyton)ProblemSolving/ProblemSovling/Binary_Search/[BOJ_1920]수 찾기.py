"""
파이썬 
sys.stdin.readline() 을 이용하면 입력을 더 빠르게 받을 수 있다. 
map(int, intput().split())을 이용하면 반복적입력을 int형으로 받기 위해서는 map을 사용한다.
"""
import sys

N = int(sys.stdin.readline())
A = set(map(int, sys.stdin.readline().split()))
N = int(sys.stdin.readline())
B = list(map(int, sys.stdin.readline().split()))

for x in B:
    print(1) if x in A else print(0)
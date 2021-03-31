import sys
input = sys.stdin.readline


def getHistoMaxRect(histo):
    stack = []

    # 시작을 깔끔스하게
    histo.insert(0, 0)
    # 끝 처리를 깔끔하게 해주기 위해서
    histo.append(0)
    # 첫 번째 시작 인덱스 삽입
    stack.append(0)
    rect_area = 0

    for i in range(1, len(histo)):
        # stack의 top과 비교해서 더 큰지, 작은지, 같은지 확인하기
        while stack and histo[stack[-1]] > histo[i]:
            #left = stack.pop()
            height = stack.pop()
            left = stack[-1]+1
            right = i - 1
            rect_area = max(rect_area, histo[height] * (right - left + 1))

        # if stack and histo[stack[-1]] == histo[i]:
        #     continue
        stack.append(i)

    return rect_area


while True:
    A = list(map(int, input().split()))
    histo_size = A[0]
    if histo_size == 0:
        break
    histo = A[1:]

    answer = getHistoMaxRect(histo)
    print(answer)

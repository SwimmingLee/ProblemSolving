import sys
input = sys.stdin.readline


def getHistoMaxRect(histo, first, last):
    if first == last:
        return histo[first]
    mid = first + (last - first)//2
    rect_area = getHistoMaxRect(histo, first, mid)
    rect_area = max(rect_area, getHistoMaxRect(histo, mid+1, last))

    left = mid
    right = mid+1
    height = min(histo[left], histo[right])
    rect_area = max(rect_area, height * (right-left+1))

    while first <= (left-1) and (right+1) <= last:
        if histo[left-1] < histo[right+1]:
            right += 1
            height = min(height, histo[right])
        else:
            left -= 1
            height = min(height, histo[left])

        rect_area = max(rect_area, height * (right-left+1))

    while first <= (left-1):
        left -= 1
        height = min(height, histo[left])
        rect_area = max(rect_area, height * (right - left + 1))

    while (right+1) <= last:
        right += 1
        height = min(height, histo[right])
        rect_area = max(rect_area, height * (right - left + 1))

    return rect_area


while True:
    A = list(map(int, input().split()))
    histo_size = A[0]
    if histo_size == 0:
        break
    histo = A[1:]

    answer = getHistoMaxRect(histo, 0, histo_size-1)
    print(answer)

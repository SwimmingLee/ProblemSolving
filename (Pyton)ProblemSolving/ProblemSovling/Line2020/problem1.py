
product = [0] * 1000001
set_boxes = 0
notset_boxes = 0


def solution(boxes):
    global set_boxes, notset_boxes
    answer = -1
    for box in boxes:
        u, v = box
        product[u] += 1
        if product[u] % 2 == 0:
            set_boxes += 1
            notset_boxes -= 1
        else:
            notset_boxes += 1
        product[v] += 1
        if product[v] % 2 == 0:
            set_boxes += 1
            notset_boxes -= 1
        else:
            notset_boxes += 1

    answer = len(boxes) - set_boxes

    return answer


answer = solution([[1, 2], [2, 3], [3, 1]])
print("hello", answer)

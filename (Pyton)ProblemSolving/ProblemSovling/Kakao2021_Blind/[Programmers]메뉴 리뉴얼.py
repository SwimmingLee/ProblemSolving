import collections


def solution(orders, course):
    answer = []
    ele = []
    courseDict = [collections.defaultdict(int) for _ in range(11)]

    def combination(order, nfood, start):
        if len(ele) == nfood:
            food = ""
            for e in ele:
                food += e
            courseDict[nfood][food] += 1
            return

        for i in range(start, len(order)):
            ele.append(order[i])
            combination(order, nfood, i+1)
            ele.pop()

    for order in orders:
        for nfood in course:
            # print("order",  order, nfood)
            combination(sorted(order), nfood, 0)

    for nfood in course:
        max_count = 1
        candidate_course = []
        # print("nfood", nfood)
        for key, value in courseDict[nfood].items():
            # print(key, value)
            if value > max_count:
                candidate_course.clear()
                candidate_course.append(key)
                max_count = value
            elif value == max_count and value > 1:
                candidate_course.append(key)
        # print(candidate_course)
        answer.extend(candidate_course)

    answer.sort()
    # 각 손님별로 조합을 가져와야 함 .(10이하 문자열)
    # 각 손님별로 원하는 갯수에 맞춰 조합을 구함
    # 결과는 비트로 표현 ㄴㄴ

    # 결과를 딕셔너리에 담아서 숫자를 카운팅해줌
    # 단품메뉴의 개수마다 딕셔너리를 만들면 편할 듯

    # 딕셔너리 순회하면서 횟수가 많은 내용을 answer에 추가
    # 횟수가 많은 것은 우선적으로 리스트에 담고 있다가 추출하는 것이 좋음

    # 마지막으로 answer 정렬

    return answer


# print(solution(["ABCFG", "AC", "CDE", "ACDE", "BCFG", "ACDEH"], [2, 3, 4]))
# print(solution(["ABCDE", "AB", "CD", "ADE", "XYZ", "XYZ", "ACD"], [2, 3, 5]))
print(solution(["XYZ", "XWY", "WXA"], [2, 3, 4]))

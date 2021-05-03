import collections


def upper_bound(arr, first, last, value):

    res = len(arr)
    while first <= last:
        mid = (first + last) // 2
        if arr[mid] >= value:
            last = mid - 1
            if mid < res:
                res = mid
        elif arr[mid] < value:
            first = mid + 1

    return res


def solution(info, query):
    answer = []
    employeeList = [[[[[] for _ in range(3)] for _ in range(
        3)] for _ in range(3)] for _ in range(4)]
    # 개발언어, 직군, 경력, 소울프드, 코테점수

    # 질문 - 개발언어, 100점 이상

    # dict[개발언어][직군][경력][소울푸드] = [코테점수, ..]
    # dict[-][직군][경력]
    lang_dict = dict()
    lang_dict["-"] = 0
    lang_dict["cpp"] = 1
    lang_dict["java"] = 2
    lang_dict["python"] = 3

    domain_dict = dict()
    domain_dict["-"] = 0
    domain_dict["backend"] = 1
    domain_dict["frontend"] = 2

    skill_dict = dict()
    skill_dict["-"] = 0
    skill_dict["junior"] = 1
    skill_dict["senior"] = 2

    soul_dict = dict()
    soul_dict["-"] = 0
    soul_dict["chicken"] = 1
    soul_dict["pizza"] = 2

    for employee_info in info:
        lang, domain, skill, soul, score = employee_info.split()
        for i in range(1 << 4):
            lang_tmp = 0
            domain_tmp = 0
            skill_tmp = 0
            soul_tmp = 0

            if i & (1 << 0):
                lang_tmp = lang_dict[lang]
            if i & (1 << 1):
                domain_tmp = domain_dict[domain]
            if i & (1 << 2):
                skill_tmp = skill_dict[skill]
            if i & (1 << 3):
                soul_tmp = soul_dict[soul]

            employeeList[lang_tmp][domain_tmp][skill_tmp][soul_tmp].append(
                int(score))

    for li in range(4):
        for di in range(3):
            for si in range(3):
                for sfi in range(3):
                    employeeList[li][di][si][sfi].sort()

    for q in query:
        q_tmp = q.split()
        lang, domain, skill, soul, score = q_tmp[0], q_tmp[2], q_tmp[4], q_tmp[6], q_tmp[7]

        lang = lang_dict[lang]
        domain = domain_dict[domain]
        skill = skill_dict[skill]
        soul = soul_dict[soul]
        score = int(score)

        # print(employeeList[lang][domain][skill][soul])
        list_size = len(employeeList[lang][domain][skill][soul])
        uidx = upper_bound(
            employeeList[lang][domain][skill][soul], 0, list_size - 1, score)

        # print(uidx)
        answer.append(list_size - uidx)

    return answer


# print(solution(["java backend junior pizza 150", "python frontend senior chicken 210", "python frontend senior chicken 150", "cpp backend senior pizza 260", "java backend junior chicken 80", "python backend senior chicken 50"], [
    #   "java and backend and junior and pizza 100", "python and frontend and senior and chicken 200", "cpp and - and senior and pizza 250", "- and backend and senior and - 150", "- and - and - and chicken 100", "- and - and - and - 150"]))

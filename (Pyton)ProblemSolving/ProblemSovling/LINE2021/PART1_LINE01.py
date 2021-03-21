
subject_score = dict()
domains = []
lang_priority = dict()


def solution(table, languages, preference):
    answer = ''
    # 점수 표 만들기
    for subject in table:
        tmp = subject.split()
        domain = tmp[0]
        ranks = tmp[1:]
        domains.append(domain)
        subject_score[domain] = dict()

        score = 5
        for lang in ranks:
            subject_score[domain][lang] = score
            score -= 1

    # 언어 선호도 별로 점수 만들기
    for i in range(len(languages)):
        lang = languages[i]
        lang_priority[lang] = preference[i]

    # 도메인별로 점수 계산하기
    max_score = 0
    for domain in domains:
        score = 0
        for lang in languages:
            if lang in subject_score[domain]:
                score += lang_priority[lang] * subject_score[domain][lang]

        if score > max_score:
            max_score = score
            answer = domain
        elif score == max_score:
            if answer > domain:
                answer = domain
        print(domain, score)
    return answer


answer = solution(["SI JAVA JAVASCRIPT SQL PYTHON C#", "CONTENTS JAVASCRIPT JAVA PYTHON SQL C++", "HARDWARE C C++ PYTHON JAVA JAVASCRIPT", "PORTAL JAVA JAVASCRIPT PYTHON KOTLIN PHP", "GAME C++ C# JAVASCRIPT C JAVA"],
                  ["PYTHON", "C++", "SQL"], [7, 5, 5])
print(answer)

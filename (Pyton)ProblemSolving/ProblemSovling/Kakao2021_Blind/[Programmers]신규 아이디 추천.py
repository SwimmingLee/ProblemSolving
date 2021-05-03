import sys
input = sys.stdin.readline


def isAccepChar(c):
    if '0' <= c <= '9':
        return True
    elif 'a' <= c <= 'z':
        return True
    elif c == '-' or c == '_' or c == '.':
        return True

    return False


def trimDot(new_id):
    while new_id[0] == '.' and len(new_id) > 1:
        new_id = new_id[1:]

    while new_id[-1] == '.' and len(new_id) > 1:
        new_id = new_id[:-1]

    if new_id[0] == '.':
        new_id = ''
    return new_id


def solution(new_id):
    # 1단계 소문자 친환
    tmp_id = new_id.lower()

    new_id = tmp_id
    tmp_id = ''
    # 2단계 문자 제거
    for c in new_id:
        if isAccepChar(c):
            tmp_id += c

    new_id = tmp_id
    tmp_id = ''
    continous_dot = 0
    # 3단계 .. 연속 제거
    for c in new_id:
        if c == '.':
            continous_dot += 1
        else:
            continous_dot = 0

        if continous_dot <= 1:
            tmp_id += c

    new_id = tmp_id
    # 4단계 처음과 끝에 있는 .문자 제거
    new_id = trimDot(new_id)
    # print(new+id)
    # while new_id[0] == '.' and len(new_id) > 1:
    #     new_id = new_id[1:]

    # while new_id[-1] == '.' and len(new_id) > 1:
    #     new_id = new_id[:-1]

    # if new_id[0] == '.':
    #     new_id = ''

    # 5 단계 빈 문자열 확인
    if len(new_id) == 0:
        new_id = 'a'

    # 6 단계 15자 이상이면 자르기
    new_id = new_id[:15]
    new_id = trimDot(new_id)
    # while new_id[0] == '.':
    #     new_id = new_id[1:]

    # while new_id[-1] == '.':
    #     new_id = new_id[:-1]

    # # 7단계
    while len(new_id) <= 2:
        new_id += new_id[-1]

    answer = new_id
    return answer


print(solution("...!@BaT#*..y.abcdefghijklm"))
print(solution("z-+.^."))
print(solution("=.="))
print(solution("123_.def"))
print(solution("abcdefghijklmn.p"))

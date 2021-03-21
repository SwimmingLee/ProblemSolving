import collections

# 커맨드를 프로그램과 옵션(플래그, 플래그 아큐먼트 타입)을 분리


def split_command(command):
    command_list = command.split()
    options = None

    program_name = command_list[0]
    if len(command) != 0:
        options = command_list[1:]

    return [program_name, options]


def isstring(s):
    for c in s:
        if 'a' <= c <= 'z' or 'A' <= c <= 'Z':
            pass
        else:
            return False
    return True


def isnumber(s):
    for c in s:
        if '0' <= c <= '9':
            pass
        else:
            return False
    return True


def chk_command(command, program, flag_rule_dict):
    program_name, options = split_command(command)

    # command_program_name과 제시된 pragram이 일치하는지 확인
    if program_name != program:
        return False

    flag_name_first = True
    rule = "NULL"
    contious_arg_type_cnt = 0

    for option in options:

        if rule == "NUMBERS" or rule == "STRINGS":
            if contious_arg_type_cnt >= 1 and option[0] == '-':
                flag_name_first = True

        # flag_name이 들어와야 하는 자리에 flag_name이 있는지 확인
        if flag_name_first:
            if option[0] != '-':
                return False

            # flag_rule_dict에 등록되어 있는 flag_name인지 확인
            if not option in flag_rule_dict:
                return False

            # 다음인자로 검사해야 할 flag_rule 확인
            rule = flag_rule_dict[option]
            if rule != "NULL":
                flag_name_first = False

            contious_arg_type_cnt = 0
        else:
            if rule == "STRING" or rule == "STRINGS":
                contious_arg_type_cnt += 1
                rule_matching = isstring(option)
                if not rule_matching:
                    return False
            elif rule == "NUMBER" or rule == "NUMBERS":
                contious_arg_type_cnt += 1
                rule_matching = isnumber(option)
                if not rule_matching:
                    return False

            if rule == "STRINGS" or rule == "NUMBERS":
                flag_name_first = False
            else:
                flag_name_first = True

    return True


def solution(program, flag_rules, commands):
    answer = []

    # flag rule을 dict 형태로 변환
    flag_rule_dict = dict()
    for flag_rule in flag_rules:
        flag_name, flag_argument_type = list(flag_rule.split())
        flag_rule_dict[flag_name] = flag_argument_type

    # commands 검사
    for command in commands:
        rule_matching = chk_command(command, program, flag_rule_dict)
        answer.append(rule_matching)
    return answer

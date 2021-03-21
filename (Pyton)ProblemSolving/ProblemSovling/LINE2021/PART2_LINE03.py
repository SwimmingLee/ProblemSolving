def split_command(command):
    command = command.split()
    options = None

    program_name = command[0]
    if len(command) != 0:
        options = command[1:]

    return [program_name, options]


def solution(program, flag_rules, commands):
    answer = []

    flag_rule_chk = dict()
    alias_flag_rule = dict()

    for flag_rule in flag_rules:
        flag_rule = flag_rule.split()

        if len(flag_rule) == 2:
            flag_name, flag_argument_type = flag_rule[0], flag_rule[1]
            flag_rule_chk[flag_name] = flag_argument_type
        elif len(flag_rule) == 3:
            alias_flag_name, flag_name = flag_rule[0], flag_rule[2]
            alias_flag_rule[alias_flag_name] = flag_name

    for command in commands:
        program_name, options = split_command(command)

        count_flag_name = dict()
        # 커맨드 프로그램 이름과 프로그램이 일치하는지 확인
        if program_name != program:
            answer.append(False)
            continue

        flag_name_first = True
        rule_matching = True
        rule = "NULL"
        continous_arg_type = 0
        for option in options:
            # 플래그 이름이 들어와야 하는 자리에 플래그 이름이 안들어는지 확인
            if rule == "NUMBERS" or rule == "STRINGS":
                if continous_arg_type >= 1 and option[0] == '-':
                    flag_name_first = True

            if flag_name_first:
                if option[0] != '-':
                    rule_matching = False
                    break
                print(option)
                # print(flag_rule_chk)
                # flag_rule_chk에 추가되어있는 플러그 이름을 준 것인지 확인
                if not option in flag_rule_chk:
                    if option in alias_flag_rule:
                        option = alias_flag_rule[option]
                    else:
                        rule_matching = False
                        break

                if not option in count_flag_name:
                    count_flag_name[option] = 0

                count_flag_name[option] += 1
                if count_flag_name[option] > 1:
                    rule_matching = False
                    break

                rule = flag_rule_chk[option]
                continous_arg_type = 0
                if rule != "NULL":
                    flag_name_first = False
            else:
                print("[]", option)
                if rule == "STRING" or rule == "STRINGS":
                    continous_arg_type += 1
                    rule_matching = True
                    for c in option:
                        if 'a' <= c <= 'z' or 'A' <= c <= 'Z':
                            pass
                        else:
                            rule_matching = False
                            break
                    if not rule_matching:
                        break
                elif rule == "NUMBER" or rule == "NUMBERS":
                    continous_arg_type += 1
                    for c in option:
                        if '0' <= c <= '9':
                            pass
                        else:
                            rule_matching = False
                            break
                    if not rule_matching:
                        break

                if rule == "STRINGS" or rule == "NUMBERS":
                    flag_name_first = False
                else:
                    flag_name_first = True
        answer.append(rule_matching)
        print(program_name, options)
    return answer

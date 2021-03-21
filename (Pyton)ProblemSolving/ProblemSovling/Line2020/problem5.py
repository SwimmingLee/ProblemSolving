
def split_card(user, card):
    num = len(user)
    if card == 1:
        for i in range(num):
            user.append(user[i]+11)
            user[i] += 1
    elif card <= 10:
        for i in range(num):
            user[i] += card
    else:
        for i in range(num):
            user[i] += 10


def get_score(user):
    score = -1
    for s in user:
        if s > 21:
            continue
        else:
            if s > score:
                score = s
    return score if score != -1 else 22


def compare_score(diller, player):
    diller_score = get_score(diller)
    player_score = get_score(player)

    print("ASD", player_score, diller_score)
    if diller_score == player_score:
        return 0
    elif player_score == 21:
        return 2
    elif player_score > diller_score:
        return 1
    else:
        return 3


def solution(cards):
    answer = 0

    idx, start_idx = 0, 0
    while True:
        is_finish = False
        diller_front = 0
        diller, player = [0], [0]
        start_idx = idx

        print("game_start: ", start_idx)
        print("current_score: ", answer)
        while True:  # game start
            print(idx)
            if (idx - start_idx) == 0:
                split_card(player, cards[idx])
            elif (idx - start_idx) == 1:
                split_card(diller, cards[idx])
            elif (idx - start_idx) == 2:
                split_card(player, cards[idx])
            elif (idx - start_idx) == 3:
                diller_front = cards[idx]
                split_card(diller, cards[idx])

                player_score = get_score(player)
                if player_score == 21:
                    answer += 3
                    is_finish = True
                elif player_score > 21:
                    answer -= 2
                    is_finish = True
                else:
                    if diller_front == 1 or diller_front >= 7:
                        player_score = get_score(player)
                        # print("***", player_score)
                        while player_score < 17:
                            if idx+1 == len(cards):
                                return answer
                            idx += 1
                            split_card(player, cards[idx])
                            player_score = get_score(player)

                        if player_score > 21:
                            answer -= 2
                            is_finish = True

                    elif diller_front == 4 or diller_front == 5:
                        pass
                    else:  # 2,3 == diller_front
                        player_score = get_score(player)
                        while player_score < 12:
                            if idx+1 == len(cards):
                                return answer
                            idx += 1
                            split_card(player, cards[idx])
                            player_score = get_score(player)

                        if player_score > 21:
                            answer -= 2
                            is_finish = True

                    if is_finish:
                        continue

                    diller_score = get_score(diller)
                    while diller_score < 17:
                        if idx+1 == len(cards):
                            return answer
                        idx += 1
                        split_card(diller, cards[idx])
                        diller_score = get_score(diller)

                    if diller_score > 21:
                        answer += 2
                        is_finish = True

                    if is_finish:
                        continue

                    print("***", diller_score)
                    res = compare_score(diller, player)
                    if res == 0:  # 비김
                        is_finish = True
                    elif res == 1:  # 플레이어 승
                        answer += 2
                        is_finish = True
                    elif res == 2:  # 플레이어 블랙잭
                        answer += 3
                        is_finish = True
                    else:  # 딜러 승
                        answer -= 2
                        is_finish = True

            if idx+1 == len(cards):
                return answer
            idx += 1

            if is_finish:
                break

    return answer


answer = solution([10, 13, 10, 1, 2, 3, 4, 5, 6, 2])
print(answer)

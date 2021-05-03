def solution(food_times, k):
    answer = 0
    """
    1. [index, food] 정렬

    2. 해치운 음식 수 + (남아있는 음식 수 * 남아 있는 메뉴 수) < k
    2-1. 인덱스를 증가하면서 계속해서 반복함
    2-2. 해치운 음식 수 + (남이있는 음식 수 * 남아 있는 메뉴 수) >= k
        해치운 음식 수 + (남이있는 음식 수--) * 남아 있는 메뉴 수 < k 가 되는지 확인

        그럼 남은 숫자 + 다 먹어버린 메뉴 에 해당하는 메뉴면 되지 않을까?

    """
    foods = [ft for ft in food_times]
    remain_food = len(food_times)
    foods.sort()

    ate_dish = 0
    ate_dish_per_food = 0
    for food_time in foods:
        for remain_dish in range(food_time - ate_dish_per_food, 0, -1):
            if ate_dish + remain_dish * remain_food <= k:
                ate_dish += remain_dish * remain_food
                ate_dish_per_food += remain_dish
                break

        if food_time <= ate_dish_per_food:
            remain_food -= 1
        else:
            break

    eatable_cnt = 0
    eatable_dish = k - ate_dish + 1
    for i in range(len(food_times)):
        if food_times[i] > ate_dish_per_food:
            eatable_cnt += 1

        if eatable_cnt == eatable_dish:
            answer = i + 1
            break

    if remain_food == 0:
        answer = -1

    return answer


print(solution([3, 1, 2], 1))
print(solution([3, 1, 2], 2))
print(solution([3, 1, 2], 3))
print(solution([3, 1, 2], 4))
print(solution([3, 1, 2], 5))
print(solution([3, 1, 2], 6))

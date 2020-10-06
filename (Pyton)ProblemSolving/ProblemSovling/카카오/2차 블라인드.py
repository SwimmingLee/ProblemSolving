import requests
import json
import math
from collections import deque


base_url = 'https://pegkq2svv6.execute-api.ap-northeast-2.amazonaws.com/prod/users'
base_headers = {'Content-Type': 'application/json',
                'X-Auth-Token': 'e7997f7b68b465c6f112182585d0bf53'}
sim_headers = {'Content-Type': 'application/json', 'Authorization': ''}

commands = []
sim_data = {}

# 시나리오 시작하기, auth key 받아오기


def start_simulate(problem):
    base_data = {'problem': problem}
    r = requests.post(base_url + '/start', headers=base_headers,
                      data=json.dumps(base_data))
    res = r.json()

    auth_key = res['auth_key']
    sim_headers['Authorization'] = auth_key


# 각 대여소마다 자건거의 위치를 확인한다.
def check_rental_office():
    r = requests.get(base_url + '/locations', headers=sim_headers)
    res = r.json()

    board_sz = int(math.sqrt(len(res['locations'])))
    office_board = [[0] * board_sz for i in range(board_sz)]

    for office in res['locations']:
        id, n_bike = office['id'], office['located_bikes_count']
        #office_board[board_sz - 1 - id%board_sz][id//board_sz] = n_bike
        office_board[id//board_sz][id % board_sz] = n_bike

    return office_board


# 현재 트럭의 상태를 확인한다
def check_truck_status():
    r = requests.get(base_url + '/trucks', headers=sim_headers)
    res = r.json()

    truck_status = []
    for truck in res['trucks']:
        id, n_bike, office_id = truck['id'], truck['loaded_bikes_count'], truck['location_id']
        truck_status.append({'n_bike': n_bike, 'office_id': office_id})
    return truck_status


def BFS_with_adj_list(graph, root):
    visited = []  # visited = 방문한 노드들을 기록한 리스트
    queue = deque([root])  # bfs는 queue개념을 이용한다.

    while(queue):  # queue에 남은 것이 없을 때까지 반복
        node = queue.pop()  # node : 현재 방문하고 있는 노드

        # 현재 node를 방문한 적 없다. -> visited에 추가
        # visited에 추가 후, 해당 노드의 자식 노드들을 queue에 추가
        if node not in visited:
            visited.append(node)
            queue.extendleft(graph[node])
    return visited


def truck_work(office_board, truck_status, idx):
    # 1 번 트럭같은 경우에는 (0,0) - (2,3)
    # if idx != 0:
    #     return [1, 1, 1, 1, 1]

    # print(truck_status)
    a = [[(0, 3), (0, 2)], [(3, 5), (2, 5)], [(0, 3), (2, 5)],
         [(3, 5), (0, 2)], [(2, 3), (2, 3)]]
    board_sz = len(office_board)
    from_row, from_col = truck_status['office_id']//board_sz, truck_status['office_id'] % board_sz
    to_row, to_col = 0, 0
    max_bike = 0
    up = False
    if truck_status['n_bike'] < 2:
        up = True
        for row in range(a[idx][0][0], a[idx][0][1]):
            for col in range(a[idx][1][0], a[idx][1][1]):
                if office_board[row][col] >= max_bike:
                    max_bike = office_board[row][col]
                    to_row = row
                    to_col = col
    else:
        for row in range(a[idx][0][0], a[idx][0][1]):
            for col in range(a[idx][1][0], a[idx][1][1]):
                if office_board[row][col] < 2:
                    to_row = row
                    to_col = col

    command = []
    k = 0
    while from_row != to_row and k < 5:
        if from_row > to_row:
            from_row -= 1
            command.append(4)
        else:
            from_row += 1
            command.append(2)
        k += 1

    while from_col != to_col and k < 5:
        if from_col > to_col:
            from_col -= 1
            command.append(3)
        else:
            from_col += 1
            command.append(1)
        k += 1

    n_bike = truck_status['n_bike']

    if up == True and k < 5:
        command.append(6)
        n_bike += 1
        k += 1pp
    else:
        command.append(5)
        n_bike -= 1
        k += 1

    # if up == True:
    #     for row in range(a[idx][0][0], a[idx][0][1]):
    #         for col in range(a[idx][1][0], a[idx][1][1]):
    #             if office_board[row][col] < 2:
    #                 to_row = row
    #                 to_col = col

    #     while from_row != to_row and k < 5:
    #         if from_row > to_row:
    #             from_row -= 1
    #             command.append(4)
    #         else :
    #             from_row += 1
    #             command.append(2)
    #         k+=1

    #     while from_col != to_col and k < 5:
    #         if from_col > to_col :
    #             from_col -= 1
    #             command.append(3)
    #         else :
    #             from_col += 1
    #             command.append(1)
    #         k+=1

    return command


# 시뮬레이터 진행시키기
def simulate():
    # print(sim_data)
    # 시뮬레이션 트럭 명령어 세팅

    office_board = check_rental_office()
    truck_status = check_truck_status()

    # 각 트럭 마다 할당 구역이 나눠준다
    # 그래서 각 트럭을 독립적으로 생각해보자(일단)

    # 하나의 트럭이 자신의 구역에서 어떻게 자건거를 배달하는게 효율적일까
    # grid하게 생각해보자
    # 일단 각 셀마다 2개 이상은 꼭 있어야 하게끔 만든다
    # 자건거가 3개 이상 있으면 자건거를 챙겨서 나눠준다.

    # 가능하면 턴이 끝났을 때에는 트럭에 자전거가 없어야 한다
    # 이렇게 하려면 가까이에 있는 자전가만 옮길 수 있다.
    # 턴이 지속되더라도 자전거를 효과적으로 옮기게 하려면 어떻게 해야할까?

    # 정말 단순하게 생각해보자
    # 트럭이 자전거를 가지고 있다면? 근처에 자전거가 없는 곳이 있다면 그곳으로간다

    n_truck = (5 if problem == 1 else 10)

    for i in range(n_truck):
        command = truck_work(office_board, truck_status[i], i)
        # print(command)
        commands.append({"truck_id": i, "command": command})

    sim_data = {
        'commands': commands
    }

    r = requests.put(base_url + '/simulate',
                     headers=sim_headers, data=json.dumps(sim_data))
    res = r.json()
    return res
    # print(res)


def check_score():
    r = requests.get(base_url + '/score', headers=sim_headers)
    res = r.json()
    print("최종 결과는--- 두구두구")
    print(res)


test_url = 'https://grepp-cloudfront.s3.ap-northeast-2.amazonaws.com/programmers_imgs/competition-imgs/2021kakao/problem1_day-1.json'


def analysis_move():
    r = requests.get(test_url)
    res = r.json()

    time_analysis = []
    hour_move = []
    for i in range(12):
        hour_move.append(dict())

    for key, value in res.items():
        # 언제 어디서 출발하는지
        # 언제 어디에 도착하는지
        # 시간 간격으로 분석하고자 한다.
        key = int(key)
        for i in value:
            start_spot, end_spot, time = i
            #print(start_spot, end_spot, time, key, hour_move[key//60])
            if not hour_move[key//60].get('start'):
                hour_move[key//60]['start'] = [0]*25

            hour_move[key//60]['start'][start_spot] += 1

            if (key + time)//60 >= 12:
                continue

            if not hour_move[(key + time)//60].get('end'):
                hour_move[(key + time)//60]['end'] = [0] * 25

            hour_move[(key + time)//60]['end'][end_spot] += 1

    print(hour_move)
    start_count = [0] * 25
    end_count = [0] * 25
    for i in hour_move:
        for j in range(len(i['start'])):
            start_count[j] += i['start'][j]
            end_count[j] += i['end'][j]

    print(start_count)
    print(end_count)


if __name__ == '__main__':    # 프로그램의 시작점일 때만 아래 코드 실행
    problem = 1
    n_command = 720
    # analysis_move()
    start_simulate(problem)
    for i in range(n_command):
        status = simulate()
        if i % 36 == 0:
            print(int(i/n_command * 100), "% 완료")
            res = check_rental_office()
            for j in range(len(res)):
                for k in range(len(res)):
                    print(res[j][k], end=' ')
                print()

            print(status)
    check_score()

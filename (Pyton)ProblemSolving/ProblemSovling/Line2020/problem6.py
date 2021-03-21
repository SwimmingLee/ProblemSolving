
app_state = [[0] for _ in range(26)]
com_state = [[] for _ in range(26)]


def get_app(readyapps, priority, limit):
    app = []
    num = 0
    for u in priority:
        if u in readyapps:
            app.append(u)
            num += 1
            if num > limit:
                return app

    return app


def solution(companies, applicants):
    answer = []
    # for company in companies:
    #     name, priority, limit = list(company.split())
    #     com_state[name-'a'] = [0, limit, priority]  # idex, limit, priority

    # for applicant in applicants:
    #     name, priority, limit = list(applicant.split())
    #     app_state[name-'a'] = [0, limit, priority]  # idex, limit, priority

    while True:
        # 모든 지원자들이 도전
        for applicant in applicants:
            app_name, app_priority, app_limit = list(applicant.split())

            #app_goal = app_state[0]
            if app_state[app_name-'a'] < app_limit:
                com_state[app_name-'a'].append(app_name)

        # 기업이 지원자 쳐냄
        for company in companies:
            com_name, com_priority, com_limit = list(applicant.split())

            if len(com_state[com_name - 'a']) <= com_limit:
                pass
            else:
                apps = get_app(com_state[com_name - 'a'],
                               com_priority, com_limit)
                for u in com_state[com_name-'a']:
                    if not u in apps:
                        app_state[u-'a'] += 1
                com_state[com_name-'a'] = apps

    return answer

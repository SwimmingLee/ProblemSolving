# import collections


# class Solution:
#     def findItinerary(self, tickets: List[List[str]]) -> List[str]:
#         graph = collections.defaultdict(list)
#         route = []

#         def dfs(city):
#             while graph[city]:
#                 dfs(graph[city].pop(0))
#             route.append(city)

#         for ticket in tickets:
#             from_city, to_city = ticket
#             graph[from_city].append(to_city)

#         for key, value in graph.items():
#             value.sort()

#         dfs("JFK")
#         return route[::-1]


import collections


def findItinerary(tickets):
    graph = collections.defaultdict(list)
    route = []

    def dfs(city):
        print("Start", city)
        while graph[city]:
            dfs(graph[city].pop(0))
        route.append(city)
        print("End", city)

    for ticket in tickets:
        from_city, to_city = ticket
        graph[from_city].append(to_city)
    for key, value in graph.items():
        value.sort()
    dfs("JFK")
    return route[::-1]


answer = findItinerary([["JFK", "KUL"], ["JFK", "NRT"], ["NRT", "JFK"]])
print(answer)

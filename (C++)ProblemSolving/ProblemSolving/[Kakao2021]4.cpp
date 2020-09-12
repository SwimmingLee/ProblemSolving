#include <string>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

struct Edge {
    int to;
    int cost;
    Edge(int to, int cost) : to(to), cost(cost) {
    }
};

//vector<vector<int>> adj;
vector<Edge> adj[205];
int inf = 98798798;
int cost[205][205];


void djk(int start, int n) {
    for (int i = 1; i <= n; i++) {
        cost[start][i] = inf;
    }
    cost[start][start] = 0;
    priority_queue<pair<int, int>> q;
    q.push(make_pair(0, start));
    vector<bool> chk(n + 1, false);
    while (!q.empty()) {
        auto p = q.top();
        q.pop();
        int x = p.second;
        if (chk[x]) continue;
        chk[x] = true;

        for (int i = 0; i < adj[x].size(); i++) {
            //if (adj[x][i] == -1) continue;
            //int next = i;
            int next = adj[x][i].to;
            if (cost[start][next] > cost[start][x] + adj[x][i].cost) {

                cost[start][next] = cost[start][x] + adj[x][i].cost;
                q.push({ -cost[start][next], next });
            }
        }
    }
}
int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = 0;
    //adj.resize(n + 1, vector<int>(n + 1, -1));

    for (int i = 0; i < fares.size(); i++) {
        int u = fares[i][0];
        int v = fares[i][1];
        int c = fares[i][2];
        adj[u].push_back({ v, c });
        adj[v].push_back({ u, c });
        //adj[u][v] = c;
        //adj[v][u] = c;
    }
    for (int i = 1; i <= n; i++) {
        djk(i, n);
    }
 
    for (int i = 1; i <= n; i++) {
        int tmp = cost[s][i] + cost[i][a] + cost[i][b];
        if (answer == 0 || answer > tmp) answer = tmp;
    }
    return answer;
}

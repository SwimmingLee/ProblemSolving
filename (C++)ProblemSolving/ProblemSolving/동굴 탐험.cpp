#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

vector<int> adj[200000];
int key[200000];
bool lock[200000];
int chk[200000];
int visited[200000];
bool solution(int n, vector<vector<int>> path, vector<vector<int>> order) {
    bool answer = true;
    int k = 0;
    for (auto& p : path) {
        int u = p[0];
        int v = p[1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (auto& o : order) {
        int u = o[0];
        int v = o[1];
        key[u] = v;
        lock[v] = true;
    }
    queue<int> q;
    q.push(0);
    visited[0] = true;
    //int seq = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        chk[cur] = false;
        if (lock[cur]) {
            ////cout << "[xx] " << cur << endl;
            //if (chk[cur] == seq) {
            //    answer = false;
            //    break;
            //}
            //chk[cur] = seq;
            //q.push(cur);
            continue;
        }
        
        if (key[cur] != 0 && lock[key[cur]]) {
            lock[key[cur]] = false;
            //cout << "[good key] " << key[cur] << endl;
            if (!chk[key[cur]] && visited[key[cur]]) {
                q.push(key[cur]);
                chk[key[cur]] = true;
            }
            //seq++;
        }
        //cout << cur << endl;
        k++;
        //cout << " [] " << cur << endl;
        for (int i = 0; i < adj[cur].size(); i++) {
            int next = adj[cur][i];
            if (!visited[next]) {
                visited[next] = true;
                q.push(next);
                chk[next] = true;
                //seq++;
            }
        }
    }
    cout << k << endl;
    if (k != n) answer = false;
    return answer;
}
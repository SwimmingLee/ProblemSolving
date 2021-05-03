import java.util.ArrayList;

class Solution {
    int n_passenger;

    int[][] adj = new int[10000+1][10000+1];
    boolean visited[] = new boolean[10000+1];
    
    int max_passenger = 0;
    int terminal = 0;
    
    public void dfs(int node, int passenger_cnt, int[] passenger) {
        visited[node] = true;
        //System.out.printf("Node: %d %d\n", node, passenger_cnt);
        if (passenger_cnt > max_passenger) {
            max_passenger = passenger_cnt;
            terminal = node;
        }
        else if (passenger_cnt == max_passenger) {
            if (node > terminal) {
                terminal = node;
            }
        }
        
        for (int next = 1; next <= n_passenger; next++) {
            if (next == node) continue;
            if (adj[node][next] == 0 || visited[next]) continue;
            dfs(next, passenger_cnt + passenger[next-1], passenger);
            visited[next] = false;
        }
    }
    
    public int[] solution(int n, int[] passenger, int[][] train) {
        int[] answer = {0, 0};
        n_passenger = passenger.length;
        
        // train => adj 로 표현
        for (int i = 0; i < train.length; i++) {
            int u, v;
            u = train[i][0];
            v = train[i][1];
            
            adj[u][v] = 1;
            adj[v][u] = 1;
        }
        
        // dfs 돌려
        dfs(1, passenger[0], passenger);
        answer[0] = terminal;
        answer[1] = max_passenger;
        return answer;
    }
}
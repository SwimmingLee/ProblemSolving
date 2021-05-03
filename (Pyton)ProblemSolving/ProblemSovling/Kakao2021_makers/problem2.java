class Solution {
    int row, column;
    int m;
    int needs_bit[] = new int[1001];
    int answer = 0;
    public void dfs(int idx, int start, int combination) {
        if (idx == m) {
            
            int cnt = 0;
            for (int i = 0; i < row; i++) {
                if ((needs_bit[i] & combination) == needs_bit[i]) {
                    cnt += 1;
                }
            }
            if (answer < cnt)
                answer = cnt;
            
            return;
        }
        for (int i = start; i < column; i++) {
            dfs(idx+1, i+1, combination | (1 << i));
        }
    }
    public int solution(int[][] needs, int r) {
        
        row = needs.length;
        column = needs[0].length;
        
        // bit mask로 needs 가지고 있기
        for (int i = 0; i < row; i++) {
            int mask = 0;
            for (int j = 0; j < column; j++) {
                if (needs[i][j] == 0) continue;
                mask |= (1 << j);
            }
            needs_bit[i] = mask;
            //System.out.printf("%d \n", needs_bit[i]);
        }
        
        m = r;
        dfs(0, 0, 0);
        
        return answer;
    }
}
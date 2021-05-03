class Solution {
    
    public int solution(int[] gift_cards, int[] wants) {
        int answer = 0;
        int cards[] = new int[100000+1];
        for (int i = 0; i < gift_cards.length; i++) {
            cards[gift_cards[i]]++;
        }
        int cnt = 0;
        for (int i = 0; i < wants.length; i++) {
            if (cards[wants[i]] > 0) {
                cards[wants[i]]--;
                cnt += 1;
            }
        }
        answer = wants.length - cnt;
        
        return answer;
    }
}
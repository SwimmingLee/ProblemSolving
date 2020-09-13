#include <string>
#include <vector>
#include <iostream>
using namespace std;

void addCard(int* sum, int* n_jocker, int idx, vector<int>& cards) {
    
    if (cards[idx] == 1) {
        *sum += 11;
        (*n_jocker)++;
    }
    else if (cards[idx] > 10) {
        *sum += 10;
    }
    else {
        *sum += cards[idx];
    }
}

int solution(vector<int> cards) {
    int answer = 0;
    int idx = 0;
    while (idx <= cards.size()) {
        bool blackjack = false;
        // 플레이어는 카드를 더 고를지 고민
        int player_sum, n_player_jocker;
        int diller_sum, n_diller_jocker;
        player_sum = n_player_jocker = 0;
        diller_sum = n_diller_jocker = 0;

        if (idx + 3 >= cards.size())
            break;
        // 카드 배포
        int look_card = cards[idx + 3];
        //cout << "DAS " << idx << " " << look_card << endl;
        addCard(&player_sum, &n_player_jocker, idx++, cards);
        addCard(&diller_sum, &n_diller_jocker, idx++, cards);
        addCard(&player_sum, &n_player_jocker, idx++, cards);
        addCard(&diller_sum, &n_diller_jocker, idx++, cards);

        // 조커를 가지고 있는데 21이 넘으면 안되니까
        while (player_sum > 21 && n_player_jocker > 0) {
            player_sum -= 10;
            n_player_jocker -= 1;
        }
        cout << "[게임 시작]" << idx << "\n";
        // 21을 넘기면 바로 끝
        if (player_sum > 21) {
            answer -= 2;
            continue;
        }
        else if (player_sum == 21) {
            // 딜러 패 확인
            blackjack = true;
        }
        else {
            if (look_card == 1 || look_card >= 7) {
                // 카드가 플레이어 점수가 17이상이 될떄까지 받음
                bool bfinish = false;
                while (player_sum < 17) {
                    if (idx >= cards.size()) {
                        bfinish = true;
                        break;
                    }
                    addCard(&player_sum, &n_player_jocker, idx++, cards);
                   
                    while (player_sum > 21 && n_player_jocker) {
                        player_sum -= 10;
                        n_player_jocker -= 1;
                    }
                }
                if (bfinish) break;
                while (player_sum > 21 && n_player_jocker) {
                    player_sum -= 10;
                    n_player_jocker -= 1;
                }
              

            }
            else if (look_card >= 4 && look_card <= 6) {
                // 더 이상 받지 않음
                // 딜러 패 확인
                
            }
            else {
                // 카드가 12이상이 될때까지 받음
                bool bfinish = false;
                while (player_sum < 12) {
                    if (idx >= cards.size()) {
                        bfinish = true;
                        break;
                    }
                    addCard(&player_sum, &n_player_jocker, idx++, cards);

                    while (player_sum > 21 && n_player_jocker) {
                        player_sum -= 10;
                        n_player_jocker -= 1;
                    }
                }
                if (bfinish) break;
                while (player_sum > 21 && n_player_jocker) {
                    player_sum -= 10;
                    n_player_jocker -= 1;
                }

            }
        }

        // 딜러 패 확인할 차례
        bool bfinish = false;
        if (!blackjack) {
            while (diller_sum < 17) {
                if (idx >= cards.size()) {
                    bfinish = true;
                    break;
                }
                cout << idx << " " << diller_sum << endl;
                addCard(&diller_sum, &n_diller_jocker, idx++, cards);
                while (diller_sum > 21 && n_diller_jocker) {
                    diller_sum -= 10;
                    n_diller_jocker -= 1;
                }
            }
            cout << "{} " << bfinish << idx << endl;
            if (bfinish) break;
            while (diller_sum > 21 && n_diller_jocker) {
                diller_sum -= 10;
                n_diller_jocker -= 1;
            }
        }
        if (diller_sum > 21) {
            answer += 2;
        }
        else if (diller_sum == player_sum) {
            
        }
        else if (diller_sum > player_sum) {
            answer -= 2;
        }
        else {
            answer += 2;
            if (blackjack) {
                answer += 1;
            }
        }

        cout << diller_sum << " " << player_sum << endl;
    }
    return answer;
}
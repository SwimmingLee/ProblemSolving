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
        // �÷��̾�� ī�带 �� ���� ���
        int player_sum, n_player_jocker;
        int diller_sum, n_diller_jocker;
        player_sum = n_player_jocker = 0;
        diller_sum = n_diller_jocker = 0;

        if (idx + 3 >= cards.size())
            break;
        // ī�� ����
        int look_card = cards[idx + 3];
        //cout << "DAS " << idx << " " << look_card << endl;
        addCard(&player_sum, &n_player_jocker, idx++, cards);
        addCard(&diller_sum, &n_diller_jocker, idx++, cards);
        addCard(&player_sum, &n_player_jocker, idx++, cards);
        addCard(&diller_sum, &n_diller_jocker, idx++, cards);

        // ��Ŀ�� ������ �ִµ� 21�� ������ �ȵǴϱ�
        while (player_sum > 21 && n_player_jocker > 0) {
            player_sum -= 10;
            n_player_jocker -= 1;
        }
        cout << "[���� ����]" << idx << "\n";
        // 21�� �ѱ�� �ٷ� ��
        if (player_sum > 21) {
            answer -= 2;
            continue;
        }
        else if (player_sum == 21) {
            // ���� �� Ȯ��
            blackjack = true;
        }
        else {
            if (look_card == 1 || look_card >= 7) {
                // ī�尡 �÷��̾� ������ 17�̻��� �ɋ����� ����
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
                // �� �̻� ���� ����
                // ���� �� Ȯ��
                
            }
            else {
                // ī�尡 12�̻��� �ɶ����� ����
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

        // ���� �� Ȯ���� ����
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
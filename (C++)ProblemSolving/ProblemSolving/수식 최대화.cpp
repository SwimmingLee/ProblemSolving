#include <string>
#include <vector>
#include <iostream>
using namespace std;
typedef pair<long long, char> plc;
int ppo[3] = { 2, 1, 0 };

bool isHighPri(char op1, char op2) {
    int op1_num, op2_num;

    if (op1 == '*') op1_num = ppo[0];
    else if (op1 == '-') op1_num = ppo[1];
    else op1_num = ppo[2]; // +

    if (op2 == '*') op2_num = ppo[0];
    else if (op2 == '-') op2_num = ppo[1];
    else op2_num = ppo[2]; // +

    return op1_num > op2_num;
}
long long covertOp(char op) {
    if (op == '*') return -1;
    else if (op == '+') return -2;
    else return -3;
}
long long calc(const string& expression) {
    long long num = 0;
    int num_sz = 0;
    vector<plc> num_stack;
    vector<char> op_stack;
    for (int i = 0; i < expression.size(); i++) {
        if ('0' <= expression[i] && expression[i] <= '9') {
            num = num * 10 + expression[i] - '0';
            num_sz += 1;
        }
        else {
            if (num_sz != 0)
                num_stack.push_back({ num, 0 });
            num = num_sz = 0;
            while (!op_stack.empty() && !isHighPri(expression[i], op_stack.back())) {
                char op = op_stack.back();
                op_stack.pop_back();
                num_stack.push_back({ 0, op });
            }
            op_stack.push_back(expression[i]);
        }
    }
    if (num_sz != 0)
        num_stack.push_back({ num, 0 });
    while (!op_stack.empty()) {
        char op = op_stack.back();
        op_stack.pop_back();
        num_stack.push_back({ 0, op });
    }

    long long tmp = 0;
    vector<long long> tmp_stack;
    for (int i = 0; i < num_stack.size(); i++) {
        plc cur = num_stack[i];
        //cout << cur.first << " " << cur.second << endl;
        if (cur.second == 0) {
            tmp_stack.push_back(cur.first);
        }
        else {
            long long oprand1 = tmp_stack.back(); tmp_stack.pop_back();
            long long oprand2 = tmp_stack.back(); tmp_stack.pop_back();

            if (cur.second == '*') {
                tmp_stack.push_back(oprand2 * oprand1);
            }
            else if (cur.second == '-') {
                tmp_stack.push_back(oprand2 - oprand1);
            }
            else {
                tmp_stack.push_back(oprand2 + oprand1);
            }
        }
    }
    /*for (int i = 0; i < tmp_stack.size(); i++) {
        cout << "[] " << tmp_stack[i] << endl;
    }*/
    return abs(tmp_stack[0]);

}
long long res = 0;
void permu(const string& expressoin, int depth, int chk) {
    if (depth == 3) {
        long long tmp = calc(expressoin);
        if (tmp > res) res = tmp;
        return;
    }
    for (int i = 0; i < 3; i++) {
        if ((chk & (1 << i)) == 0) {
            ppo[depth] = i;
            permu(expressoin, depth + 1, chk | (1 << i));
        }
    }
}
long long solution(string expression) {
    long long answer = 0;
    permu(expression, 0, 0);
    answer = res;
    return answer;
}

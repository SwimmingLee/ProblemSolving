
/*
* 그때그때 업데이트하면 왜 틀리는지 궁금..
* 다시 풀어볼까 고민중
*/
#include <iostream>
#include <vector>
#include <set>
using namespace std;
#define MAXR		99
#define MAXC		26

enum {
	NONE=0,
	CONST,
	ADD,
	SUB,
	DIV,
	MUL,
	MIN,
	MAX,
	SUM
};

int tableR, tableC;
int tableValue[MAXR * MAXC];
int tableOperator[MAXR * MAXC];
int tableUpdate[MAXR * MAXC];
int upCnt;
int tableOpAddr[MAXR * MAXC][2];

int max(int a, int b) {
	return a > b ? a : b;
}
int min(int a, int b) {
	return a > b ? b : a;
}

void init(int C, int R) {
	upCnt = 0;
	tableR = R;
	tableC = C;
	for (int i = 0; i < tableR * tableC; ++i) {
		tableValue[i] = 0;
		tableOperator[i] = NONE;
		tableUpdate[i] = 0;
	}
}

int getOper(char input[]) {
	int oper = NONE;
	// input이 숫자인지 검사
	if (('0' <= input[0] && input[0] <= '9') || input[0] == '-') {
		oper = CONST;
	}
	// input이 어떤 명령어인지 검사
	else {
		if (input[0] == 'A') {
			oper = ADD;
		}
		else if (input[0] == 'S') {
			if (input[2] == 'B') {
				oper = SUB;
			}
			else if (input[2] == 'M') {
				oper = SUM;
			}
		}
		else if (input[0] == 'M') {
			if (input[1] == 'U') {
				oper = MUL;
			}
			else if (input[1] == 'A') {
				oper = MAX;	
			}
			else if (input[1] == 'I') {
				oper = MIN;
			}
		}
		else if (input[0] == 'D') {
			oper = DIV;
		}
	}
	return oper;
}

int getNumber(char input[]) {
	int positive = 1;
	if (*input == '-') {
		input++;
		positive = -1;
	}
	int c;
	int num = 0;
	while (c = *input++) {
		num = num * 10 + c - '0';
	}
	return positive * num;
}

void getTaskAddr(char input[], int* addr1, int* addr2) {
	int addrR, addrC;
	char c;

	*addr1 = 0;
	*addr2 = 0;
	addrR = addrC = 0;
	while (c = *input++) {
		if (c == ',') {
			addrR -= 1;
			*addr1 = addrR * tableC + addrC;
			addrR = addrC = 0;
			continue;
		}
		else if (c == ')') {
			addrR -= 1;
			*addr2 = addrR * tableC + addrC;
			addrR = addrC = 0;
			continue;
		}

		if ('A' <= c && c <= 'Z') {
			addrC = c - 'A';
		}
		else {
			addrR = addrR * 10 + c - '0';
		}
	}
}

void set(int col, int row, char input[]) {
	col -= 1;
	row -= 1;

	int id = row * tableC + col;
	int preVal = tableValue[id];

	int oper = getOper(input);
	tableOperator[id] = oper;

	if (oper == CONST) {
		int num = getNumber(input);
		tableValue[id] = num;
	}
	else {
		int addr1, addr2;
		getTaskAddr(input + 4, &addr1, &addr2);
		tableOpAddr[id][0] = addr1;
		tableOpAddr[id][1] = addr2;
	}
}

int calcTable(int id) {
	if (tableUpdate[id] == upCnt) 
		return tableValue[id];

	tableUpdate[id] = upCnt;

	int op = tableOperator[id];
	if (op == NONE) {
		return tableValue[id];
	}
	else if (op == CONST) {
		return tableValue[id];
	}

	int addr1, addr2;
	addr1 = tableOpAddr[id][0];
	addr2 = tableOpAddr[id][1];
	if (op == ADD || op == SUB || op == DIV || op == MUL) {
		int left = calcTable(addr1);
		int right = calcTable(addr2);
		if (op == ADD) {
			return tableValue[id] = left + right;
		}
		else if (op == SUB) {
			return tableValue[id] = left - right;
		}
		else if (op == DIV) {
			return tableValue[id] = left / right;
		}
		else { //if (op == MUL) {
			return tableValue[id] = left * right;
		}
	}
	else { // op == MIN, MAX, SUM
		int val = ((op == SUM) ? 0 : calcTable(addr1));
		if ((addr2 - addr1) < tableC) {
			for (int cur = addr1; cur <= addr2; ++cur) {
				if (op == MIN) {
					val = min(val, calcTable(cur));
				}
				else if (op == MAX) {
					val = max(val, calcTable(cur));
				}
				else if (op == SUM) {
					val += calcTable(cur);
				}
			}
		}
		else {
			for (int cur = addr1; cur <= addr2; cur += tableC) {
				if (op == MIN) {
					val = min(val, calcTable(cur));
				}
				else if (op == MAX) {
					val = max(val, calcTable(cur));
				}
				else if (op == SUM) {
					val += calcTable(cur);
				}
			}
		}
		return tableValue[id] = val;
	}
}


void update(int value[MAXR][MAXC]) {
	upCnt++;
	for (int r = 0; r < tableR; ++r) {
		for (int c = 0; c < tableC; ++c) {
			value[r][c] = calcTable(r * tableC + c);
		}
	}
}
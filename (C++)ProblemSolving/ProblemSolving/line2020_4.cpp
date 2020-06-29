#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;
#define TRANSACTION_ID 100001
map<string, long long> accounts;

int string2num(const string& s) {
	int num = 0;
	for (auto c : s) {
		num = num * 10 + c - '0';
	}
	return num;
}
string num2string(long long num) {
	string s;
	while (num) {
		s.push_back(num % 10 + '0');
		num /= 10;
	}
	reverse(s.begin(), s.end());
	return s;
}
vector<vector<string>> solution(vector<vector<string>> snapshots, vector<vector<string>> transactions) {
	vector<vector<string>> answer;
	vector<bool> chk(TRANSACTION_ID, false);
	for (auto& account : snapshots) {
		string account_id = account[0];
		long long num = (long long)string2num(account[1]);
		accounts[account_id] = num;
	}

	for (auto& transaction : transactions) {
		string method = transaction[1];
		string account_id = transaction[2];
		int transaction_id = string2num(transaction[0]);
		int num = string2num(transaction[3]);

		if (chk[transaction_id]) continue;
		chk[transaction_id] = true;

		if (method == "SAVE") {
			/**/
			if (accounts.find(account_id) == accounts.end()) {
				accounts[account_id] = (long long)num;
			}
			else {
				accounts[account_id] += (long long)num;
			}
		}
		else if (method == "WITHDRAW") {
			accounts[account_id] -= (long long)num;
		}
	}

	for (auto& account : accounts) {
		vector<string> tmp;
		//cout << account.first << " " << account.second << endl;
		tmp.push_back(account.first);
		tmp.push_back(num2string(account.second));
		answer.push_back(tmp);
	}
	return answer;
}

void inputSnapshot(vector<vector<string>>& snapshots, string account_id, string num) {
	vector<string> tmp;
	tmp.push_back(account_id);
	tmp.push_back(num);

	snapshots.push_back(tmp);
}

void inputTransaction(vector<vector<string>>& transactions, string id, string method, string account_id, string num) {
	vector<string> tmp;
	tmp.push_back(id);
	tmp.push_back(method);
	tmp.push_back(account_id);
	tmp.push_back(num);

	transactions.push_back(tmp);
}
int main(void) {
	vector<vector<string>> snapshots;
	vector<vector<string>> transactions;
	
	inputSnapshot(snapshots, "ACCOUNT1", "100"); /**/
	inputSnapshot(snapshots, "ACCOUNT2", "150");

	inputTransaction(transactions, "1", "SAVE", "ACCOUNT2", "100");
	inputTransaction(transactions, "2", "WITHDRAW", "ACCOUNT1", "50");
	inputTransaction(transactions, "1", "SAVE", "ACCOUNT2", "100");
	inputTransaction(transactions, "4", "SAVE", "ACCOUNT3", "500");
	inputTransaction(transactions, "3", "WITHDRAW", "ACCOUNT2", "30");

	vector<vector<string>> answer = solution(snapshots, transactions);
	for (auto& account : answer) {
		for (auto& s : account) {
			cout << s << ' ';
		}
		cout << endl;
	}
	return 0;
}
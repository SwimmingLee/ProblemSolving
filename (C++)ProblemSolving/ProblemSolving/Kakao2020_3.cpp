#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> ban_list;
void dfs(int cnt, int chk, vector<vector<int>>& ban) {
	int ans = 0;
	if (cnt == ban.size()) {
		ban_list.push_back(chk);
		return;
	}
	for (int i = 0; i < ban[cnt].size(); i++) {
		int user_idx = ban[cnt][i];
		if (!(chk & (1 << user_idx))) {
			dfs(cnt + 1, chk | (1 << user_idx), ban);
		}
	}
	return;
} //dfs(0, 0, ban)

int solution(vector<string> user_id, vector<string> banned_id) {
	vector<vector<int>> ban(banned_id.size());

	for (int ban_index = 0; ban_index < banned_id.size(); ban_index++) {
		string& ban_name = banned_id[ban_index];

		for (int user_index = 0; user_index < user_id.size(); user_index++) {
			string& user_name = user_id[user_index];

			int user_sz = user_name.size();
			int ban_sz = ban_name.size();
			if (user_sz != ban_sz) continue;

			for (int i = 0; i < user_sz; i++) {
				if (ban_name[i] == '*' || ban_name[i] == user_name[i]) {
					if (i == user_sz - 1) {
						ban[ban_index].push_back(user_index);
					}
				}
				else {
					break;
				}
			}
		}
	}
	cout << ban.size() << endl;
	for (auto& a : ban) {
		cout << a.size() << endl;
	}
	int answer = 0;
	dfs(0, 0, ban);

	sort(ban_list.begin(), ban_list.end());
	ban_list.erase(unique(ban_list.begin(), ban_list.end()), ban_list.end());
	answer = ban_list.size();
	return answer;
}

int main() {
	vector<string> user_id;
	user_id.push_back("frodo");
	user_id.push_back("fradi");
	user_id.push_back("crodo");
	user_id.push_back("abc123");
	user_id.push_back("frodoc");

	vector<string> banned_id;
	banned_id.push_back("fr*d*");
	banned_id.push_back("abc1**");
	solution(user_id, banned_id);
}
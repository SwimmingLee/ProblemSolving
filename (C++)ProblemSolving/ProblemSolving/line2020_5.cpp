#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

vector<string> solution(vector<vector<string>> dataSource, vector<string> tags) {
	vector<string> answer;

	vector<set<string>> doc_tag(dataSource.size());
	vector<string> doc_name(dataSource.size());

	for (int i = 0; i < dataSource.size(); i++) {
		vector<string>& doc = dataSource[i];
		doc_name[i] = doc[0];
		for (int j = 1; j < doc.size(); j++) {
			doc_tag[i].insert(doc[j]);
		}
	}

	vector<pair<int, string>> tmp;
	for (int i = 0; i < dataSource.size(); i++) {
		int cnt = 0;
		for (int j = 0; j < tags.size(); j++) {
			if (doc_tag[i].count(tags[j])) cnt++;
		}
		if (cnt > 0) {
			tmp.push_back({ -cnt, doc_name[i] });
		}
	}
	sort(tmp.begin(), tmp.end());
	for (int i = 0; i < tmp.size() && i < 10; i++) {
		answer.push_back(tmp[i].second);
	}
	return answer;
}

void inputDataSource(vector<vector<string>>& dataSource, string doc_name, string tag1, string tag2, string tag3) {
	vector<string> tmp;
	tmp.push_back(doc_name);
	tmp.push_back(tag1);
	tmp.push_back(tag2);
	tmp.push_back(tag3);
	dataSource.push_back(tmp);
}
void inputTags(vector<string>& tags, string tag1, string tag2, string tag3) {
	tags.push_back(tag1);
	tags.push_back(tag2);
	tags.push_back(tag3);
}

int main(void) {
	vector<vector<string>> dataSource;
	vector<string> tags;
	vector<string> answer;

	inputDataSource(dataSource, "doc1", "t1", "t2", "t3");
	inputDataSource(dataSource, "doc2", "t0", "t2", "t3");
	inputDataSource(dataSource, "doc3", "t1", "t6", "t7");
	inputDataSource(dataSource, "doc4", "t1", "t2", "t4");
	inputDataSource(dataSource, "doc5", "t6", "t100", "t8");
	inputTags(tags, "t1", "t2", "t3");
	answer = solution(dataSource, tags);
	for (auto& s : answer) {
		cout << s << ' ';
	}
	cout << "\n";

	return 0;
}
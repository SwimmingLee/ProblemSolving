#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
struct Log {
	long long start_time;
	long long end_time;
	bool operator< (const Log& rhs) {
		if (start_time == rhs.start_time) {
			return end_time < rhs.end_time;
		}
		else {
			return start_time < rhs.start_time;
		}
	}
};
long long convert(string s) {
	s.push_back(':');
	long long time = 0;
	long long num = 0;
	int seq = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == ':') {
			if (seq == 0) {
				time += num * 3600;
			}
			else if (seq == 1) {
				time += num * 60;
			}
			else if (seq == 2) {
				time += num;
			}
			seq++;
			num = 0;
			continue;
		}
		num = num * 10 + s[i] - '0';
	}
	return time;
}
string inverse(long long t) {
	string res;
	string tmp = to_string(t / 3600);
	while (tmp.size() < 2) {
		tmp = "0" + tmp;
	}
	res += tmp;
	res += ":";

	t = t % 3600;
	tmp = to_string(t / 60);
	while (tmp.size() < 2) {
		tmp = "0" + tmp;
	}
	res += tmp;
	res += ":";

	t = t % 60;
	tmp = to_string(t);
	while (tmp.size() < 2) {
		tmp = "0" + tmp;
	}
	res += tmp;
	return res;
}
string solution(string play_time, string adv_time, vector<string> logs) {
	string answer = "";
	vector<Log> l(logs.size(), { 0, 0 });
	for (int i = 0; i < logs.size(); i++) {
		string& time_str = logs[i];
		string st;
		string et;
		for (int j = 0; j < time_str.size(); j++) {
			if (time_str[j] == '-') {
				st = time_str.substr(0, j);
				et = time_str.substr(j + 1);
				break;
			}
		}
		l[i].start_time = convert(st);
		l[i].end_time = convert(et);
		//cout << st << " " << et << endl;
		//cout << l[i].start_time << " " << l[i].end_time << endl;
	}
	sort(l.begin(), l.end());
	long long t_play = convert(play_time);
	long long t_adv = convert(adv_time);

	long long total = 0;
	long long res = 0;


	for (int i = 0; i < l.size(); i++) {
		int j = i - 1;
		long long t_ptotal = 0;
		
		while (j >= 0 && l[j].end_time > l[i].start_time) {
			long long t_pend;
			if (l[j].end_time < l[i].start_time + t_adv) {
				t_pend = l[j].end_time;
			}
			else {
				t_pend = l[i].start_time + t_adv;
			}
			t_ptotal += (t_pend - l[i].start_time);
			j--;
		}

		j = i + 1;
		while (j < l.size() && l[j].start_time < l[i].start_time + t_adv) {
			long long t_pend;
			if (l[j].end_time < l[i].start_time + t_adv) {
				t_pend = l[j].end_time;
			}
			else {
				t_pend = l[i].start_time + t_adv;
			}
			t_ptotal += (t_pend - l[i].start_time);
			j++;
		}
		if (total < t_ptotal) {
			total = t_ptotal;
			res = l[i].start_time;
		}
	}

	int j = 0;
	long long t_ptotal = 0;
	while (j < l.size() && l[j].start_time < t_adv) {
		long long t_pend;
		if (l[j].end_time < t_adv) {
			t_pend = l[j].end_time;
		}
		else {
			t_pend = t_adv;
		}
		t_ptotal += t_pend;
		j++;
	}
	if (total < t_ptotal) {
		total = t_ptotal;
		res = 0;
	}

	answer = inverse(res);
	return answer;
}
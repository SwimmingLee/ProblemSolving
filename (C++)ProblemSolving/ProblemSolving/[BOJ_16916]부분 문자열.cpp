#include <iostream>
using namespace std;

const long long mod = 2147483647;
const int base = 256;

long long GetRabinCarpFirst(int pattern_sz) {
	long long first = 1;
	for (int i = 0; i < pattern_sz - 1; i++) {
		first = (first * base) % mod;
	}
	return first;
}

long long hashFunc(string str) {
	long long value = 0;
	for (char c : str) {
		value = (value * base + c ) % mod;
	}
	return value % mod;
}
bool match(string& pattern, string& str) {
	int pattern_sz = pattern.size();
	int str_sz = str.size();
	if (pattern_sz > str_sz) return false;

	long long hash_p = hashFunc(pattern);
	long long hash_s = hashFunc(str.substr(0, pattern_sz));

	long long first = GetRabinCarpFirst(pattern_sz);
	for (int i = 0; i <= str_sz - pattern_sz; i++) {

		if (hash_p == hash_s && str.substr(i, pattern_sz) == pattern) {
			return true;
		}
		if (i < str_sz - pattern_sz){
			hash_s = hash_s - (str[i] * first) % mod;
			hash_s = (hash_s + mod) % mod;
			hash_s = ((hash_s * base) % mod + str[i + pattern_sz]) % mod;
		}
	}
	return false;
}

int main(void) {
	string pattern, str;
	cin >> str >> pattern;
	if (match(pattern, str)) cout << "1\n";
	else cout << "0\n";
	return 0;
}
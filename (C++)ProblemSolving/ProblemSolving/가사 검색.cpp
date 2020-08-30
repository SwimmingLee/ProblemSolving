#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

struct Trie {
    Trie* child[26];
    int val;
    Trie() {
        val = 0;
        for (int i = 0; i < 26; i++) {
            child[i] = NULL;
        }
    }
    void insert(string& s, int d) {
        val++;
        if (s.size() == d) {
            return;
        }
        int next = s[d] % 26;
        if (child[next] == NULL) {
            child[next] = new Trie();
        }
        child[next]->insert(s, d+1);
    }
    void insert(string& s) {
        insert(s, 0);
    }
    int search(string& s, int d) {
        if (s.size() == d) {
            return 1;
        }
        int res = 0;
        if (s[d] != '?') {
            int next = s[d] % 26;
            if (child[next] != NULL)
                res += child[next]->search(s, d+1);
        }
        else {
            return val;
        }
        return res;
    }
};
Trie* froot[10001];
Trie* broot[10001];

vector<int> solution(vector<string> words, vector<string> queries) {
    vector<int> answer;
    for (string& s : words) {
        int sz = s.size();
        if (froot[sz - 1] == NULL)
            froot[sz - 1] = new Trie;
        froot[sz-1]->insert(s);
        
        reverse(s.begin(), s.end());
        if (broot[sz - 1] == NULL)
            broot[sz - 1] = new Trie;
        broot[sz-1]->insert(s);
    }
    int tmp = 0;
    for (string& s : queries) {
        int sz = s.size();
        int cnt = 0;
        if (froot[sz - 1] == NULL) {
            answer.push_back(0);
            continue;
        }

        if (s[0] == '?') {
            reverse(s.begin(), s.end());
            cnt = broot[sz - 1]->search(s, 0);
        }
        else if (s[sz - 1] == '?') {
            cnt = froot[sz - 1]->search(s, 0);
        }
        else {
            cnt = froot[sz - 1]->search(s, 0);
        }
        answer.push_back(cnt);
    }
    return answer;
}
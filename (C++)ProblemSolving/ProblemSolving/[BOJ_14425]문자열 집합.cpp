b#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 이문제는 unordered_map를 쓰는 것이 훨씬더 빠르다.
// 어째서? Trie를 쓰는 게 더 느리지?? 이유가 무엇인가
struct Trie {
    struct Node {
        int children[26];
        bool valid;
        Node() { 
            for (int i = 0; i < 26; i++) {
                children[i] = -1;
            }
            valid = false;
        }
    };
    vector<Node> trie;
    int root;
    int init() {
        Node x;
        trie.push_back(x);
        return (int)trie.size() - 1;
    }
    Trie() {
        root = init();
    }
    void add(int node, string& s, int index) {
        if (index == s.size()) {
            trie[node].valid = true;
            return;
        }
        int c = s[index] - 'a';
        if (trie[node].children[c] == -1) {
            int next = init();
            trie[node].children[c] = next;
        }
        int child = trie[node].children[c];
        add(child, s, index + 1);
    }
    void add(string& s) {
        add(root, s, 0);
    }
    bool search(int node, string& s, int index) {
        if (node == -1) return false;
        if (index == s.length()) return trie[node].valid;
        int c = s[index] - 'a';
        int child = trie[node].children[c];
        return search(child, s, index + 1);
    }
    bool search(string& s) {
        return search(root, s, 0);
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    Trie trie;
    while (n--) {
        string s;
        cin >> s;
        trie.add(s);
    }
    int ans = 0;
    while (m--) {
        string s;
        cin >> s;
        if (trie.search(s)) {
            ans += 1;
        }
    }
    cout << ans << '\n';

    return 0;
}
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Node {
	vector<Node*> children;
	string file_name;
	Node(string _file_name) :file_name(_file_name) {};
	~Node(){
		for (int i = 0; i < children.size(); i++)
			delete children[i];
	}
};

vector<string> split(string& s, char del) {
	vector<string> res;
	s.push_back(del);
	int start = -1;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == del) {
			if (start + 1 == i) {
				start = i;
				continue;
			}
			string sub = s.substr(start + 1, i - start - 1);
			start = i;
			res.push_back(sub);
		}
	}
	s.pop_back();
	return res;
}
void mkdir(Node* root, string path) {
	Node* cur = root;
	vector<string> dir = split(path, '/');
	for (int j = 0; j < dir.size(); j++) {
		if (j == dir.size() - 1) {
			Node* c = new Node(dir[j]);
			cur->children.push_back(c);
		}
		else {
			for (int k = 0; k < cur->children.size(); k++) {
				if (dir[j] == cur->children[k]->file_name) {
					cur = cur->children[k];
					break;
				}
			}
		}
	}
}
void rm(Node* root, string path) {
	Node* cur = root;
	vector<string> dir = split(path, '/');
	for (int j = 0; j < dir.size(); j++) {
		if (j == dir.size() - 1) {
			Node* del = NULL;
			for (int k = 0; k < cur->children.size(); k++) {
				if (dir[j] == cur->children[k]->file_name) {
					del = cur->children[k];
					for (int i = k + 1; i < cur->children.size(); i++) {
						cur->children[i - 1] = cur->children[i];
					}
					cur->children.pop_back();
					delete del;
					break;
				}
			}
		}
		else {
			for (int k = 0; k < cur->children.size(); k++) {
				if (dir[j] == cur->children[k]->file_name) {
					cur = cur->children[k];
					break;
				}
			}
		}
	}
}
Node* deepcopy(Node* cur) {
	Node* node = new Node(cur->file_name);
	for (int i = 0; i < cur->children.size(); i++) {
		Node* c = deepcopy(cur->children[i]);
		node->children.push_back(c);
	}
	return node;
}
void search(vector<string>& dir, Node* cur, string path) {
	if (cur->file_name != "/") {
		path = path + "/" + cur->file_name;
		dir.push_back(path);
	}
	for (int i = 0; i < cur->children.size(); i++) {
		search(dir, cur->children[i], path);
	}
}

void cp(Node* root, string src_path, string dst_path) {
	Node* cur = root;
	Node* copy;
	vector<string> dir = split(src_path, '/');
	for (int j = 0; j < dir.size(); j++) {
		if (j == dir.size() - 1) {
			for (int k = 0; k < cur->children.size(); k++) {
				if (dir[j] == cur->children[k]->file_name) {
					cur = cur->children[k];
					copy = deepcopy(cur);
					break;
				}
			}
		}
		else {
			for (int k = 0; k < cur->children.size(); k++) {
				if (dir[j] == cur->children[k]->file_name) {
					cur = cur->children[k];
					break;
				}
			}
		}
	}

	dir.clear();
	cur = root;
	dir = split(dst_path, '/');
	if (dir.size() == 0) {
		cur->children.push_back(copy);
	}
	else {
		for (int j = 0; j < dir.size(); j++) {
			if (j == dir.size() - 1) {
				for (int k = 0; k < cur->children.size(); k++) {
					if (dir[j] == cur->children[k]->file_name) {
						cur = cur->children[k];
						cur->children.push_back(copy);
						break;
					}
				}
			}
			else {
				for (int k = 0; k < cur->children.size(); k++) {
					if (dir[j] == cur->children[k]->file_name) {
						cur = cur->children[k];
						break;
					}
				}
			}
		}
	}

}

vector<string> solution(vector<string> directory, vector<string> command) {
	vector<string> answer;
	Node* root = new Node("/");

	for (int i = 0; i < directory.size(); i++) {
		mkdir(root, directory[i]);
	}

	for (int i = 0; i < command.size(); i++) {
		vector<string> sub = split(command[i], ' ');
		string method = sub[0];
		string src_path = sub[1];
		if (method == "mkdir") {
			mkdir(root, src_path);
		}
		else if (method == "cp") {
			string dst_path = sub[2];
			cp(root, src_path, dst_path);
		}
		else if (method == "rm") {
			rm(root, src_path);
		}
	}
	answer.push_back("/");
	search(answer, root, "");
	sort(answer.begin(), answer.end());
	return answer;
}

void inputDirectory(vector<string>& directory, string path) {
	directory.push_back(path);
}

void inputCommand(vector<string>& command, string cmd) {
	command.push_back(cmd);
}

int main(void) {
	vector<string> answer;
	vector<string> directory;
	vector<string> command;

	//inputDirectory(directory, "/");
	//inputDirectory(directory, "/hello");
	//inputDirectory(directory, "/hello/tmp");
	//inputDirectory(directory, "/root");
	//inputDirectory(directory, "/root/abcd");
	//inputDirectory(directory, "/root/abcd/etc");
	//inputDirectory(directory, "/root/abcd/hello");


	//inputCommand(command, "mkdir /root/tmp");
	//inputCommand(command, "cp /hello /root/tmp");
	//inputCommand(command, "rm /hello");

	inputDirectory(directory, "/");

	inputCommand(command, "mkdir /a");
	inputCommand(command, "mkdir /a/b");
	inputCommand(command, "mkdir /a/b/c");
	inputCommand(command, "cp /a/b /");
	inputCommand(command, "rm /a/b/c");


	answer = solution(directory, command);
	for (auto& s : answer) {
		cout << s << endl;
	}
	return 0;
}
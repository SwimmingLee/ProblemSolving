//#include <iostream>
//#include <vector>
//#include <string>
//#include <queue>
//
//using namespace std;
//
//int arr[100][100];
//string str[100];
//
//char convert(char c) {
//	if (c == '.') return '.';
//	else if (c == 'O') return 'O';
//	else if (c == '-') return '|';
//	else if (c == '|') return '-';
//	else if (c == '/') return '\\';
//	else if (c == '\\') return '/';
//	else if (c == '^') return '<';
//	else if (c == '<') return 'v';
//	else if (c == 'v') return '>';
//	else if (c == '>') return '^';
//	return c;
//}
//
//int main(void) {
//	int height, width;
//	cin >> height >> width;
//	
//	for (int h = 0; h < height; h++) {
//		cin >> str[h];
//	}
//	
//
//	//cout << width - 1 << endl;
//	for (int w = width-1; w >= 0; w--) {
//		for (int h = 0; h < height; h++) {
//			cout << convert(str[h][w]);
//		}
//		cout << "\n";
//	}
//	return 0;
//}	
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int height, width;
int num_sticker;
vector<pair<int, int>> sticker;

bool AttachSticker(int h1, int w1, int h2, int w2) {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			if (h1 <= height && w1 <= width) {
				if ((height - h1) >= h2 && w2 <= width)
					return true;
				else if ((width - w1) >= w2 && h2 <= height)
					return true;
				else if ((height - h1) >= w2 && h2 <= width)
					return true;
				else if ((width - w1) >= h2 && w2 <= height)
					return true;
			}
			swap(h1, w1);
		} 
		swap(h1, h2);
		swap(w1, w2);
	}
	return false;
}
int GetMaxStickerRange() {
	int range = 0;
	for (int i = 0; i < num_sticker - 1; i++) {
		for (int j = i + 1; j < num_sticker; j++) {
			int h1 = sticker[i].first, w1 = sticker[i].second;
			int h2 = sticker[j].first, w2 = sticker[j].second;
			if (AttachSticker(h1, w1, h2, w2)) {
				range = max(range, h1*w1+h2*w2);
			}
		}
	}
	return range;
}

int main(void) {
	cin >> height >> width >> num_sticker;
	sticker.resize(num_sticker);
	for (int i = 0; i < num_sticker; i++) {
		int h, w;
		cin >> h >> w;
		sticker[i] = { h, w };
	}

	cout << GetMaxStickerRange() << '\n';
	return 0;
}
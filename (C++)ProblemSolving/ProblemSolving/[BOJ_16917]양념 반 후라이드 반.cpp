#include <iostream>
#include <algorithm>
using namespace std;

int cost_fried, cost_seasoning, cost_half, fried, seasoning;

int GetMinValue() {
	int ans = 987987987;
	int max_chiken = max(fried, seasoning);
	
	for (int nhalf = 0; nhalf <= max_chiken * 2; nhalf += 2) {
		int nfried = fried - (nhalf >> 1);
		nfried =  nfried > 0 ? nfried : 0;
		int nseasoning = seasoning - (nhalf >> 1);
		nseasoning = nseasoning > 0 ? nseasoning : 0;
		int tmp = cost_fried * nfried + cost_seasoning * nseasoning + cost_half * nhalf;
		if (tmp < ans)
			ans = tmp;
	}
	return ans;
}


int main(void) {
	cin >> cost_fried >> cost_seasoning >> cost_half >> fried >> seasoning;
	cout << GetMinValue() << '\n';
	return 0;
}
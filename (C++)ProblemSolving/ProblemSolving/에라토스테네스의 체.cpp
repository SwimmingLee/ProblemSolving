#include <iostream>
using namespace std;

#define MAX_PRIME	30000000
#define START		29999990
#define END			MAX_PRIME
unsigned int prime[MAX_PRIME / 32 + 1];

int main(void) {
	for (long long i = 2; i*i <= MAX_PRIME; i++) {
		if (!(prime[i / 32] & (1 << (i % 32)))) {
			for (int j = i * i; j <= MAX_PRIME; j += i) {
				prime[j / 32] |= (1 << (j % 32));
			}
		}
	}
	
	for (long long i = START; i <= END; i++) {
		if (!(prime[i / 32] & (1 << (i % 32))))
			cout << i << ' ';
	}
}
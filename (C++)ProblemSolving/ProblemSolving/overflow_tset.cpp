#include <iostream>
#include <vector>
using namespace std;

struct drop {
	int cell_idx;
	int cell_pixel_x;
	int cell_pixel_y;
	int nozzle_idx;
	double glass_x;
	double glass_y;
	double volume;
};

int main(void) {
	vector<int> int_vector;
	cout << "vector<int>.max_size :" << int_vector.max_size() << endl;
	cout << "vector<int>.max_size * sizeof(int):" << int_vector.max_size() * sizeof(int) << endl;

	vector<drop> drop_vector;
	cout << "vector<drop>.max_size :" << drop_vector.max_size() << endl;
	cout << "vector<drop>.max_size  * sizeof(drop):" << drop_vector.max_size() * sizeof(drop)<< endl;

	cout << "UINT32_MAX : " << UINT32_MAX << endl;
	cout << "UINT64_MAX : " << UINT64_MAX << endl;
	return 0;
}
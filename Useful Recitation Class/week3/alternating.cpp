#include <iostream>
#include <cassert>

using namespace std;

bool is_alternating(int num, int base) {
    // TODO: Your implementation here
    assert(base > 1);
	int count = 0;
	int tmp = num;
	while(tmp > 0){
		tmp /= base;
		count++;
	}
	bool result_1;
	bool result_2;
	tmp = num;
	// int *arr = new int[count];
	for(int i = 0; i < count; i++){
		int digit = tmp % 10;
		if(i % 2 == digit % 2)
			result_1 = false;
		if(i % 2 != digit % 2)
			result_2 = false;
		tmp /= 10;
	}
	// delete[] arr;
    return result_1 || result_2;
}

void test_alternating() {
	assert(!is_alternating(10, 3));
	assert(!is_alternating(7, 2));
    assert(!is_alternating(24, 10));  // 24 is not an alternating number in base 10
    // TODO: Add more test cases
    cout << "Alternating number tests passed!" << endl;
}

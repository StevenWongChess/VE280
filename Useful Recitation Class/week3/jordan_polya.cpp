#include <iostream>
#include <cassert>

using namespace std;
int factorial(int n);

bool is_jordan_polya(int num) {
    // TODO: Your implementation here
	// we only need to consider 10! at most
	for(int i = 1; i < 11; i++){
		if (num == factorial(i))
			return true;
	}
	for(int i = 2; i < 11; i++){
		return (num % factorial(i) == 0) && is_jordan_polya(num / factorial(i));
	}
    return false;
}

void test_jordan_polya() {
    assert(!is_jordan_polya(5));  // 5 is not a Jordan-Polya number
    // TODO: Add more test cases
    cout << "Jordan-Polya number tests passed!" << endl;
}

int factorial(int n){
	if(n <= 1)
		return 1;
	return n * factorial(n - 1);
}
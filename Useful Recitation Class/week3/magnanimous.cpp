#include <iostream>
#include <cassert>
#include <cmath>
using namespace std;
bool isprime(int n);
int power(int base, int n);

bool is_magnanimous(int num) {
    // TODO: Your implementation here
    int count = 0;
    int tmp = num;
	while(tmp > 0){
		tmp /= 10;
		count++;
	}
    for(int i = 1; i < count; i++){
        if(isprime(num % (power(10, i)) + num / (power(10, i))))
            return true;
    }
    return false;
}

void test_magnanimous() {
    // assert(!isprime(1));
    // assert(isprime(2));
    // assert(isprime(3));
    // assert(!isprime(4));
    assert(is_magnanimous(1316));
    assert(is_magnanimous(23));
    assert(!is_magnanimous(9));
    assert(!is_magnanimous(15));  // 15 is not a magnanimous number
    // TODO: Add more test cases
    cout << "Magnanimous number tests passed!" << endl;
}

int power(int base, int n){
    if (n == 0)
        return 1;
    return base * power(base, n - 1);
}

bool isprime(int n){
    if(n < 2)
        return false;
    for(int i = 2; i <= sqrt(n); i++){
        if(n % i == 0)
            return false;
    }
    return true;
}


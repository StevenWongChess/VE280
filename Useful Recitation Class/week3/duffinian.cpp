#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;
int gcd(int a, int b);
extern bool isprime(int n);

bool is_duffinian(int num) {
    // TODO: Your implementation here
    if (isprime(num))
    	return false;
    int sum = 0;
    for(int i = 1; i <= num; i++){
    	if(num % i == 0)
    		sum += i;
    }
    return gcd(sum, num) == 1;
}

void test_duffinian() {
	assert(is_duffinian(35));
    assert(!is_duffinian(6));  // 6 is not a Duffinian number
    // TODO: Add more test cases
    cout << "Duffinian number tests passed!" << endl;
}

int gcd(int a, int b){
	if(a == 0 || b == 0)
		return a + b;
	return a >= b ? gcd(a % b, b) : gcd(a, b % a);
}

// bool isprime(int n){
//     if(n < 2)
//         return false;
//     for(int i = 2; i <= sqrt(n); i++){
//         if(n % i == 0)
//             return false;
//     }
//     return true;
// }
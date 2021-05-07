#include <iostream>
#include <cmath>
#include <string>
//#include <stdlib>
using namespace std;
const int ARRAY_SIZE = 8;
int triangle(int number);
int palindrome(int number);
int odious(int number);
int extravagant(int number);
int count_digit(int number);
int prime(int number);

int main() {
	int number = 0;
	int option = 0;
	while(number < 1 || number > 10000000 || option < 1 || option > 4){
		cout << "Please enter the integer and the test number: ";
		cin >> number >> option;
	}
	if (option == 1)
		cout << triangle(number) << endl;
	else if (option == 2)
		cout << palindrome(number) << endl;
	else if (option == 3)
		cout << odious(number) << endl;
	else if (option == 4)
		cout << extravagant(number) << endl;
	else
		cout << "Error happens\n";
	return 0;
}

int triangle(int number){
	int root = sqrt(8 * number + 1);
	return root * root == 8 * number + 1;
}
int palindrome(int number){
	int origin = number;
	int reverse = 0;
	while(origin){
		reverse = 10 * reverse + origin % 10;
		origin /= 10;
	}
	return reverse == number;
}
int odious(int number){
	int tmp = number;
	int count = 0;
	while(tmp){
		count += (tmp % 2);	
		tmp /= 2;
	}
	return count % 2;
}
int extravagant(int number){
	int length_origin = count_digit(number);
	int base[ARRAY_SIZE];
	int power[ARRAY_SIZE];
	for(int i=0;i<ARRAY_SIZE;i++){
		base[i] = 0; power[i] = 0;
	}

	int tmp = number;
	int num_of_base = 0;
	while(tmp > 1){
		for(int i = 2; i < tmp + 1; i++){
			if ( tmp % i == 0 && prime(i) ){
				if(i == base[num_of_base]){
					power[num_of_base] ++;
				}
				else{
					num_of_base ++;
					base[num_of_base] = i;
					power[num_of_base] ++;
				}
				tmp /= i;
				break;
			}
		}
	}

	int length_sum = 0;
	for(int i=0;i<ARRAY_SIZE;i++){
		// if ( base[i] > 0 )
		// 	cout << base[i] << " " << power[i] << endl;
		length_sum += ( count_digit(base[i]) + count_digit(power[i]) );
	}
	return ( length_origin < length_sum );
}
int prime(int number){
	if (number < 2)
		return 0;
	for(int i = 2; i <= sqrt(number); i++){
		if (number % i == 0){
			return 0;
		}
	}
	return 1;
}
int count_digit(int number){
	int count = 0;
	while (number){
		count ++;
		number /= 10;
	}
	return count;
}









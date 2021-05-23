#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>
#include "dlist.h"
using namespace std;
const string opAll = "+-*/rndpcaq";

void zeronary_op(Dlist<int> &stack, int index);
void unary_op(Dlist<int> &stack, int index);
void binary_op(Dlist<int> &stack, int index);

int main(int argc, char const *argv[])
{
	Dlist<int> stack;
	while(true){
		try{
			string str = "";
			cin >> str;	
			if(str.length() > 1){
				int value = 0;
				int symbol = 1;
				for(int i = 0; i < static_cast<int>(str.length()); i++){
					if(i == 0 && str[i] == '-'){
						symbol = -1;
						continue;
					}
					int digit  = str[i] - '0';
					if(digit >= 0 && digit <= 9){
						value = value * 10 + digit;
					}
					else{
						throw(1.1);
					}
				}
				stack.insertFront(new int(symbol * value));
				continue;
			}
			if(str.length() == 1 && str[0] >= '0' && str[0] <= '9'){
				stack.insertFront(new int(str[0] - '0'));
				continue;
			}

			int index = -1;
			char op = str[0];
			for(int i = 0; i < static_cast<int>(opAll.length()); i++){
				if(op == opAll[i]){
					index = i;
					break;
				}
			}
			if(index >= 0 && index <= 4){
				binary_op(stack, index);
			}
			else if(index >= 5 && index <= 7){
				unary_op(stack, index);
			}
			else if(index >= 8 && index < static_cast<int>(opAll.length())){
				zeronary_op(stack, index);
				if(index == 10){
					break;
				}
			}
			else{
				throw(1.1);
			}
		}
		catch(double e){
			cout << "Bad input\n";
		}
		catch(emptyList e){
			cout << "Not enough operands\n";
		}
		catch(int e){
			cout << "Divide by zero\n";
		}
	}

	return 0;
}

void zeronary_op(Dlist<int> &stack, int index){
	if(index == 8){
		while(!stack.isEmpty()){
			int* tmp = stack.removeFront();
			delete tmp;
		}
	}
	else if(index == 9){
		Dlist<int> cc(stack);
		while(!cc.isEmpty()){
			int* tmp = cc.removeFront();
			cout << *tmp << " ";
			delete tmp;
		}
		cout << endl;
	}
	else if(index == 10){

	}
	else{
		cout << "wrong in zeronary\n";
	}
}

void unary_op(Dlist<int> &stack, int index){
	int *a = stack.removeFront();
	if(index == 5){
		*a = *a * (-1);
		stack.insertFront(a);
	}
	else if(index == 6){
		stack.insertFront(a);
		stack.insertFront(new int(*a));
	}
	else if(index == 7){
		cout << *a << endl;
		stack.insertFront(a);
	}
	else{
		cout << "wrong in unary\n";
	}
}

void binary_op(Dlist<int> &stack, int index){
	int *a = stack.removeFront();
	int *b = stack.removeFront();
	if(index == 0){
		stack.insertFront(new int(*b + *a));
	}
	else if(index == 1){
		stack.insertFront(new int(*b - *a));
	}
	else if(index == 2){
		stack.insertFront(new int(*b * *a));
	}
	else if(index == 3){
		if(*a == 0){
			stack.insertFront(b);
			stack.insertFront(a);
			throw(3);
		}
		stack.insertFront(new int(*b / *a));
	}
	else if(index == 4){
		stack.insertFront(a);
		stack.insertFront(b);
	}
	else{
		cout << "wrong in binary\n";
	}
	if(index != 4){
		delete a; 
		delete b;
	}
}






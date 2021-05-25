#include <iostream>
using namespace std;
int foo(int x) {
    if (x < 100) { x = x * x; int y =foo(x);}
    else return x;
}
int main() { cout << foo(15);}

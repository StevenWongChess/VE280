#include <iostream>
#include "dlist.h"
using namespace std;

void test1();
void test2();

int main(int argc, char *argv[])
{
    test1();
    test2();
}

void test1(){
    Dlist<int> l1;
    int *a = new int(1);
    int *b = new int(2);
    int *c = new int(3);
    int *d = new int(4); // 4312
    l1.insertBack(a);
    l1.insertBack(b);
    l1.insertFront(c);
    l1.insertFront(d);
    l1.printDlist();
    l1.removeFront();
    Dlist<int> l3 = l1;
    l1.removeBack();
    l1.printDlist();
    Dlist<int> l2(l1);
    l2.printDlist();
    l3.printDlist();
    delete b; delete d;
}
    int result = 0;

void test2(){
    Dlist<int> ilist;
    int *ip = new int(1);
    ilist.insertFront(ip);
    ip = ilist.removeFront();
    if(*ip != 1)
        cout << "wrong\n";
    delete ip;
    if(!ilist.isEmpty())
        cout << "wrong\n";
}



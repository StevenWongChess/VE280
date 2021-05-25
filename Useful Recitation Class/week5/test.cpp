#include <iostream>
#include <cassert>
#include "cord.h"

using namespace std;

int main(int argc, char **argv) {
    // Test cord representing the empty string
    cord_t c1 = cord_new("");
    assert(c1 == nullptr);
    assert(cord_length(c1) == 0);
    assert(cord_tostring(c1).empty());

    // Test basic leaf node
    cord_t c2 = cord_new("1234");
    assert(cord_length(c2) == 4);
    assert(cord_tostring(c2) == "1234");

    // Test basic concatenation node
    cord_t c3 = cord_join(c2, cord_new("56"));
    assert(cord_length(c3) == 6);
    assert(cord_tostring(c3) == "123456");

    // Test cord_charat
    cord_t c4 = cord_new("012345");
    assert(cord_charat(c4, 0) == '0');
    assert(cord_charat(c4, 1) == '1');
    cord_t c5 = cord_sub(c4, 2, 4);
    assert(cord_length(c5) == 2);
    assert(cord_charat(c5, 0) == '2');
    assert(cord_charat(c5, 1) == '3');

    // Test cord_sub, where substr is the complete string
    cord_t c6 = cord_new("012345");
    cord_t c7 = cord_sub(c6, 0, cord_length(c6));
    cout << cord_tostring(c7) << endl;
    assert(cord_tostring(c7) == cord_tostring(c6));

    // Test cord_sub, where substr is represented by one child node
    cord_t c8 = cord_new("6789");
    cord_t c9 = cord_join(c6, c8);
    cord_t c10 = cord_sub(c9, 6, 10);
    assert(cord_tostring(c8) == cord_tostring(c10));

    // Test the three examples of cord_sub in README.md
    cord_t R = cord_join(cord_join(cord_new("t"), cord_new("otally")), cord_join(cord_new("efficien"), cord_new("t")));
    cord_print(R);
    cout << endl;
    assert(cord_tostring(R) == "totallyefficient");

    cord_t R1 = cord_sub(R, 1, 16);
    cord_print(R1);
    cout << endl;
    assert(cord_tostring(R1) == "otallyefficient");
    assert(cord_tostring(R1->left) == cord_tostring(R->left->right));
    assert(cord_tostring(R1->right) == cord_tostring(R->right));

    cord_t R2 = cord_sub(R, 1, 11);
    cord_print(R2);
    cout << endl;
    assert(cord_tostring(R2) == "otallyeffi");
    assert(cord_tostring(R2->left) == cord_tostring(R->left->right));

    cord_t R3 = cord_sub(R, 2, 11);
    cord_print(R3);
    cout << endl;
    assert(cord_tostring(R3) == "tallyeffi");

    // Test cord validity
    assert(is_cord(c4));
    assert(is_cord(c5));
    assert(is_cord(c6));
    assert(is_cord(c7));
    assert(is_cord(c8));
    assert(is_cord(c9));
    assert(is_cord(c10));
    assert(is_cord(R));
    assert(is_cord(R1));
    assert(is_cord(R2));
    assert(is_cord(R3));

    cord_t c11 = cord_join(c8, c8);
    assert(is_cord(c11));

    cord_t ct1 = cord_new("c1");
    cord_t ct2 = cord_new("c2");
    cord_t ct3 = cord_new("c3");
    ct1->left = ct2;
    ct2->left = ct1;
    ct2->right = ct3;
    ct1->right = ct3;
    ct1->len = 0;
    ct2->len = 0;
    ct3->len = 0;
    assert(!is_cord(ct1));

    cout << "Cord tests passed!" << endl;

    return 0;
}

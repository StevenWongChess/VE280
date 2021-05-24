#ifndef LAB1_H
#define LAB1_H

bool is_magnanimous(int num);
// REQUIRES: 1 <= num <= 10000000
// EFFECTS: return true if num is a magnanimous number, otherwise return false

void test_magnanimous();
// EFFECTS: test the correctness of is_magnanimous()

bool is_jordan_polya(int num);
// REQUIRES: 1 <= num <= 10000000
// EFFECTS: return true if num is a Jordan-Polya number, otherwise return false

void test_jordan_polya();
// EFFECTS: test the correctness of is_jordan_polya()

bool is_alternating(int num, int base);
// REQUIRES: 1 <= num <= 10000000, 2 <= base <= 10
// EFFECTS: return true if num is an alternating number in the given base, otherwise return false

void test_alternating();
// EFFECTS: test the correctness of is_alternating()

bool is_duffinian(int num);
// REQUIRES: 1 <= num <= 10000000
// EFFECTS: return true if num is a Duffinian number, otherwise return false

void test_duffinian();
// EFFECTS: test the correctness of is_duffinian()

#endif

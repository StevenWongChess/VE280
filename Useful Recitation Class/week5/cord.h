#ifndef CORD_H
#define CORD_H

#include <string>

typedef struct cord *cord_t;
struct cord {
    size_t len;
    cord *left;
    cord *right;
    std::string data;
};

bool is_cord(cord *c);
// EFFECTS: returns true if "c" is a valid cord, false otherwise

size_t cord_length(cord_t R);
// EFFECTS: returns the length of the string represented by cord "R"

cord_t cord_new(const std::string &s);
// EFFECTS: returns a new cord representing string "s"

cord_t cord_join(cord_t R, cord_t S);
// EFFECTS: returns a new cord which joins cord "R" and cord "S"

std::string cord_tostring(cord_t R);
// EFFECTS: returns the string represented by cord "R"

char cord_charat(cord_t R, size_t i);
// REQUIRES: 0 <= i && i < cord_length(R)
// EFFECTS: returns the character at index "i" in the string represented by cord "R"

cord_t cord_sub(cord_t R, size_t lo, size_t hi);
// REQUIRES: 0 <= lo && lo <= hi && hi <= cord_length(R)
// EFFECTS: returns a cord representing the segment of the string represented by cord "R"
//          from index "lo" (inclusive) to index "hi" (exclusive), which should maximize
//          sharing between the old cord and the new cord, and only allocates a new node
//          when it is impossible to use the entire string represented by an existing cord

void cord_print(cord_t R);
// EFFECTS: prints the internal structure of cord "R" to standard output, "" for a cord
//          representing the empty string, "somedata" for a leaf node, ( "some" "data" )
//          for a concatenation node

#endif

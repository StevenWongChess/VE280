#include <string>
#include <iostream>
#include "cord.h"

using namespace std;

bool is_cord(cord *c) {
    if (c == nullptr) {
        return true;
    }
    if (c->left == nullptr && c->right == nullptr && c->len && c->len == c->data.length()) {
        return true;
    }
    if (c->left != nullptr && c->right != nullptr) {
        if (c->left->len == 0 || c->right->len == 0 || c->len != c->left->len + c->right->len) {
            return false;
        }
        if (is_cord(c->left) && is_cord(c->right)) {
            return true;
        }
    }
    return false;
}

size_t cord_length(cord_t R) {
    if (R == nullptr) {
        return 0;
    } else {
        return R->len;
    }
}

cord_t cord_new(const std::string &s) {
    if (s.length()) {
        return new cord{s.length(), nullptr, nullptr, s};
    } else {
        return nullptr;
    }
}

cord_t cord_join(cord_t R, cord_t S) {
    if (R == nullptr) {
        return S;
    }
    if (S == nullptr) {
        return R;
    }
    return new cord{cord_length(R) + cord_length(S), R, S, ""};
}

string cord_tostring(cord_t R) {
    // TODO: Your implementation here
    return "";
}

char cord_charat(cord_t R, size_t i) {
    // TODO: Your implementation here
    return '\0';
}

cord_t cord_sub(cord_t R, size_t lo, size_t hi) {
    // TODO: Your implementation here
    return nullptr;
}

void cord_print(cord_t R) {
    // TODO: Your implementation here
}
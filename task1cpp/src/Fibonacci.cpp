#include "Iterated.h"
#include "Fibonacci.h"
#include <ctime>
#include <climits>
#include <stdexcept>


//class F_iterator

F_iterator::F_iterator(int n) : prev(0), cur(1) {
    int tmp;
    for (int i = 0; i < n; ++i) {
        if (prev > INT_MAX - cur) {
            prev = INT_MAX;
            cur = INT_MAX;
            return;
        }
        tmp = cur;
        cur = prev + cur;
        prev = tmp;
    }
}

F_iterator::F_iterator(int pr, int cu) : prev(pr), cur(cu) {}

F_iterator& F_iterator::operator++() {
    if (prev == INT_MAX && cur == INT_MAX) return *this;
    do {
        if (prev > INT_MAX - cur) {
            prev = INT_MAX;
            cur = INT_MAX;
            return *this;
        }
        int tmp = cur;
        cur = prev + cur;
        prev = tmp;
    } while (!check(**this));
    return *this;
}

int F_iterator::operator*() {
    return cur;
}

bool F_iterator::operator==(const F_iterator& other) {
    return cur == other.cur && prev == other.prev;
}

bool F_iterator::operator!=(const F_iterator& other) {
    return cur != other.cur || prev != other.prev;
}


//class Fibonacci

Fibonacci::Fibonacci(int count, int from) :
    n(from < 0 ? 0 : from), m(INT_MAX - count > from ? count + from : INT_MAX) {}

Fibonacci::~Fibonacci() {}

Fibonacci::iterator Fibonacci::begin() {
    return iterator(n);
}

Fibonacci::const_iterator Fibonacci::begin() const {
    return const_iterator(n);
}

Fibonacci::iterator Fibonacci::end() {
    return iterator(m);
}

Fibonacci::const_iterator Fibonacci::end() const {
    return const_iterator(m);
}

Fibonacci::iterator Fibonacci::filter(predic_t func) {
    iterator i = this->begin();
    i.check = func;
    if (!i.check(*i)) {
        ++i;
    }
    return i;
}

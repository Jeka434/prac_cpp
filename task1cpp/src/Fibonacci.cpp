#include "Iterated.h"
#include "Fibonacci.h"
#include <ctime>
#include <climits>
#include <stdexcept>


//class F_filter_iterator

F_filter_iterator::F_filter_iterator(int n, std::function<bool(const value_type&)> pred)
    : prev(0), cur(1), predicate(pred) {
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

F_filter_iterator& F_filter_iterator::operator++() {
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

int F_filter_iterator::operator*() {
    return cur;
}

bool F_filter_iterator::operator==(const F_filter_iterator& other) const {
    return cur == other.cur && prev == other.prev;
}

bool F_filter_iterator::operator!=(const F_filter_iterator& other) const {
    return cur != other.cur || prev != other.prev;
}

bool F_filter_iterator::operator==(const F_iterator& other) const {
    return other == *this;
}

bool F_filter_iterator::operator!=(const F_iterator& other) const {
    return other != *this;
}

bool F_filter_iterator::check(const F_filter_iterator::value_type& k) const {
    return predicate(k);
}

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

F_iterator& F_iterator::operator++() {
    if (prev == INT_MAX && cur == INT_MAX) return *this;
    if (prev > INT_MAX - cur) {
        prev = INT_MAX;
        cur = INT_MAX;
        return *this;
    }
    int tmp = cur;
    cur = prev + cur;
    prev = tmp;
    return *this;
}

int F_iterator::operator*() {
    return cur;
}

bool F_iterator::operator==(const F_iterator& other) const {
    return cur == other.cur && prev == other.prev;
}

bool F_iterator::operator!=(const F_iterator& other) const {
    return cur != other.cur || prev != other.prev;
}

bool F_iterator::operator==(const F_filter_iterator& other) const {
    return cur == other.cur && prev == other.prev;
}

bool F_iterator::operator!=(const F_filter_iterator& other) const {
    return cur != other.cur || prev != other.prev;
}

//class Fibonacci

Fibonacci::Fibonacci(int count, int from) :
    n(from < 0 ? 0 : from), m(INT_MAX - count > from ? count + from : INT_MAX) {}

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

Fibonacci::fiterator Fibonacci::filter(std::function<bool(const value_type&)> pred) {
    fiterator i(n, pred);
    if (!i.check(*i)) {
        ++i;
    }
    return i;
}

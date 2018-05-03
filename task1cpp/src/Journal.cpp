#include <ctime>
#include <functional>
#include <iostream>
#include "Iterated.h"
#include "Journal.h"

//struct J_record

J_record::J_record(time_t t, const std::string& m) : time(t), message(m) {}

bool J_record::operator==(const J_record& rec2) const {
    return message == rec2.message;
}

std::ostream& operator<<(std::ostream& os, const J_record& rec) {
    if (rec.time == 0) return os;
    os << ">>" << ctime(&rec.time) << "Message : " << rec.message << '\n';
    return os;
}

//class J_filter_iterator

J_filter_iterator::J_filter_iterator(const std::list<J_record>::iterator& i,
    std::function<bool(const J_filter_iterator::value_type&)> pred) : it(i), predicate(pred) {}

J_filter_iterator& J_filter_iterator::operator++() {
    auto i = it;
    ++i;
    do {
        ++i;
        ++it;
    } while (i != it && !predicate(**this));
    return *this;
}

J_filter_iterator::value_type& J_filter_iterator::operator*() const {
    return *it;
}

bool J_filter_iterator::operator==(const J_filter_iterator& other) const {
    return it == other.it;
}

bool J_filter_iterator::operator!=(const J_filter_iterator& other) const {
    return it != other.it;
}

bool J_filter_iterator::operator==(const J_iterator& other) const {
    return other == *this;
}

bool J_filter_iterator::operator!=(const J_iterator& other) const {
    return other != *this;
}

bool J_filter_iterator::check(const J_filter_iterator::value_type& rec) const {
    return predicate(rec);
}

//class J_iterator

J_iterator::J_iterator(const std::list<J_record>::iterator& i) : it(i) {}

J_iterator& J_iterator::operator++() {
    ++it;
    return *this;
}

J_record& J_iterator::operator*() const {
    return *it;
}

bool J_iterator::operator==(const J_iterator& other) const {
    return it == other.it;
}

bool J_iterator::operator!=(const J_iterator& other) const {
    return it != other.it;
}

bool J_iterator::operator==(const J_filter_iterator& other) const {
    return it == other.it;
}

bool J_iterator::operator!=(const J_filter_iterator& other) const {
    return it != other.it;
}

//class J_const_iterator

J_const_iterator::J_const_iterator(const std::list<J_record>::const_iterator& i) : it(i) {}

J_const_iterator& J_const_iterator::operator++() {
    ++it;
    return *this;
}

const J_record& J_const_iterator::operator*() const {
    return *it;
}

bool J_const_iterator::operator==(const J_const_iterator& other) const {
    return it == other.it;
}

bool J_const_iterator::operator!=(const J_const_iterator& other) const {
    return it != other.it;
}

//class Journal

Journal::Journal() : list() {}

Journal::iterator Journal::begin() {
    return iterator(list.begin());
}

Journal::const_iterator Journal::begin() const {
    return const_iterator(list.begin());
}

Journal::iterator Journal::end() {
    return iterator(list.end());
}

Journal::const_iterator Journal::end() const {
    return const_iterator(list.end());
}

Journal::fiterator Journal::filter(std::function<bool(const Journal::value_type&)> pred) {
    fiterator i(list.begin(), pred);
    if (!i.check(*i)) {
        ++i;
    }
    return i;
}

void Journal::push_back(time_t time, const std::string& message) {
    list.push_back(J_record(time, message));
}

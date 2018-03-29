#include <ctime>
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

//struct J_list

J_list::J_list(time_t t, const std::string& m) : data(t, m), next(nullptr) {}

J_list::J_list(const J_list& other) : data(other.data), next(nullptr) {}

J_list& J_list::operator=(const J_list& other) {
    data = other.data;
    next = nullptr;
    return *this;
}

//class J_iterator

J_iterator::J_iterator(const J_list *p) : ptr(p) {}

J_iterator& J_iterator::operator++() {
    if (ptr == nullptr) return *this;
    do {
        ptr = ptr->next;
        if (ptr == nullptr) return *this;
    } while (!check(**this));
    return *this;
}

const J_record& J_iterator::operator*() const {
    return ptr->data;
}

bool J_iterator::operator==(const J_iterator &other) {
    return (ptr == other.ptr);
}

bool J_iterator::operator!=(const J_iterator &other) {
    return (ptr != other.ptr);
}

//class Journal

Journal::Journal() : first(nullptr), last(nullptr) {}

Journal::Journal(const Journal &other) : first(nullptr), last(nullptr) {
    if (!other.first) return;
    first = new J_list(*other.first);
    last = first;
    const J_list *tmp = other.first->next;
    while (tmp) {
        last->next = new J_list(*tmp);
        last = last->next;
        tmp = tmp->next;
    }
}

Journal::~Journal() {
    last = nullptr;
    J_list *tmp = first;
    while (first) {
        tmp = first;
        first = first->next;
        delete tmp;
    }
}

Journal & Journal::operator=(const Journal &other) {
    this->~Journal();
    if (!other.first) return *this;
    first = new J_list(*other.first);
    last = first;
    while (last->next) last = last->next;
    return *this;
}

Journal::iterator Journal::begin() {
    return iterator(first);
}

Journal::const_iterator Journal::begin() const {
    return const_iterator(first);
}

Journal::iterator Journal::end() {
    return iterator(nullptr);
}

Journal::const_iterator Journal::end() const {
    return const_iterator(nullptr);
}

Journal::iterator Journal::filter(predic_t func) {
    iterator i = this->begin();
    i.check = func;
    if (!i.check(*i)) {
        ++i;
    }
    return i;
}

void Journal::push_back(time_t time, const std::string& message) {
    J_list *tmp = new J_list(time, message);
    if (last == nullptr) {
        first = last = tmp;
        return;
    }
    last->next = tmp;
    last = last->next;
}

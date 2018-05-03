//Список 1 (итерирование по последовательности записей журнала)
#ifndef JOURNAL_H
#define JOURNAL_H

#include <iostream>
#include <list>
#include <functional>
#include "Iterated.h"

//Структура записи журнала
struct J_record {
    J_record(time_t, const std::string&);
    bool operator==(const J_record&) const;
    time_t time;
    std::string message;
};

std::ostream& operator<<(std::ostream&, const J_record&);

class J_iterator;

//Класс итератора для функции filter последовательности списка 1
class J_filter_iterator : public std::iterator<std::input_iterator_tag, J_record> {
    friend class J_iterator;
public:
    J_filter_iterator(const std::list<J_record>::iterator&, std::function<bool(const value_type&)>);
    J_filter_iterator& operator++();
    reference operator*() const;
    bool operator==(const J_filter_iterator&) const;
    bool operator!=(const J_filter_iterator&) const;
    bool operator==(const J_iterator&) const;
    bool operator!=(const J_iterator&) const;
    bool check(const value_type&) const;
private:
    std::list<J_record>::iterator it;
    std::function<bool(const value_type&)> predicate;
};

//Класс итератора для последовательности списка 1
class J_iterator : public std::iterator<std::input_iterator_tag, J_record> {
public:
    J_iterator(const std::list<J_record>::iterator&);
    J_iterator& operator++();
    reference operator*() const;
    bool operator==(const J_iterator&) const;
    bool operator!=(const J_iterator&) const;
    bool operator==(const J_filter_iterator&) const;
    bool operator!=(const J_filter_iterator&) const;
private:
    std::list<J_record>::iterator it;
};

//Класс константного итератора для последовательности списка 1
class J_const_iterator : public std::iterator<std::input_iterator_tag, J_record> {
public:
    J_const_iterator(const std::list<J_record>::const_iterator&);
    J_const_iterator& operator++();
    const value_type& operator*() const;
    bool operator==(const J_const_iterator&) const;
    bool operator!=(const J_const_iterator&) const;
private:
    std::list<J_record>::const_iterator it;
};

//Класс последовательности списка 1
class Journal : public Iterated<J_iterator, J_filter_iterator, J_const_iterator> {
public:
    Journal();
    Journal(const Journal&);
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    fiterator filter(std::function<bool(const value_type&)>);
    void push_back(time_t time, const std::string& message);
private:
    std::list<J_record> list;
};

#endif

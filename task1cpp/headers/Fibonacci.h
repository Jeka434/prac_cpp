//Список 2 (итерирование по последовательности чисел Фибоначчи)
#ifndef FIBONACCI_H
#define FIBONACCI_H value

#include "Iterated.h"
#include <ctime>
#include <climits>
#include <iterator>

class F_iterator;

//Класс итератора для функции filter последовательности списка 2
class F_filter_iterator : public std::iterator<std::input_iterator_tag, int> {
    friend class F_iterator;
public:
    F_filter_iterator(int n, std::function<bool(const value_type&)>);
    F_filter_iterator& operator++();
    value_type operator*();
    bool operator==(const F_filter_iterator&) const;
    bool operator!=(const F_filter_iterator&) const;
    bool operator==(const F_iterator&) const;
    bool operator!=(const F_iterator&) const;
    bool check(const value_type&) const;
private:
    int prev;
    int cur;
    std::function<bool(const value_type&)> predicate;
};

//Класс итератора для последовательности списка 2
class F_iterator : public std::iterator<std::input_iterator_tag, int> {
public:
    F_iterator(int n);
    F_iterator& operator++();
    value_type operator*();
    bool operator==(const F_iterator&) const;
    bool operator!=(const F_iterator&) const;
    bool operator==(const F_filter_iterator&) const;
    bool operator!=(const F_filter_iterator&) const;
private:
    int prev;
    int cur;
};



//Класс последовательности списка 2
class Fibonacci : public Iterated<F_iterator, F_filter_iterator> {
public:
    Fibonacci(int count = INT_MAX, int from = 0);
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    fiterator filter(std::function<bool(const value_type&)>);
private:
    int n;
    int m;
};

#endif

//Список 2 (итерирование по последовательности чисел Фибоначчи)
#ifndef FIBONACCI_H
#define FIBONACCI_H value

#include "Iterated.h"
#include <ctime>
#include <climits>
#include <iterator>

//Класс итератора для последовательности списка 2
class F_iterator : public std::iterator<std::input_iterator_tag, int> {
public:
    typedef bool (*predic_t)(const int&);

    predic_t check = [](const int&) { return true; };

    F_iterator(int n);
    F_iterator(int pr, int cu);
    F_iterator& operator++();
    int operator*();
    bool operator==(const F_iterator&);
    bool operator!=(const F_iterator&);
private:
    int prev;
    int cur;
};

//Класс последовательности списка 2
class Fibonacci : public Iterated<F_iterator> {
public:
    Fibonacci(int count = INT_MAX, int from = 0);
    ~Fibonacci();
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    iterator filter(predic_t);
private:
    int n;
    int m;
};

#endif

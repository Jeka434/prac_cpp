//Список 1 (итерирование по последовательности записей журнала)
#ifndef JOURNAL_H
#define JOURNAL_H value

#include <iostream>
#include "Iterated.h"

//Структура записи журнала
struct J_record {
    J_record(time_t, const std::string&);
    bool operator==(const J_record&) const;
    time_t time;
    std::string message;
};

std::ostream& operator<<(std::ostream&, const J_record&);

//Структура элемента списка для для хранения записей журнала
struct J_list {
    J_list(time_t, const std::string&);
    J_list(const J_list&);
    J_list& operator=(const J_list&);
    J_record data;
    J_list *next;
};

//Класс итератора для последовательности списка 1
class J_iterator : public std::iterator<std::input_iterator_tag, J_record> {
public:
    typedef bool (*predic_t)(const J_record&);
    predic_t check = [](const J_record&) { return true; };

    J_iterator(const J_list *p);
    J_iterator& operator++();
    const J_record& operator*() const;
    bool operator==(const J_iterator&);
    bool operator!=(const J_iterator&);
private:
    const J_list *ptr;
};

//Класс последовательности списка 1
class Journal : public Iterated<J_iterator> {
public:
    Journal();
    Journal(const Journal&);
    ~Journal();
    Journal& operator=(const Journal&);
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    iterator filter(predic_t);
    void push_back(time_t time, const std::string& message);
private:
    J_list *first;
    J_list *last;
};

#endif

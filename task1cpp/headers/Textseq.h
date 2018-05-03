#ifndef TEXTSEQ_H
#define TEXTSEQ_H value

#include <fstream>
#include <memory>
#include "Iterated.h"

class T_iterator;

//Класс итератора для последовательности списка 3
class T_filter_iterator : public std::iterator<std::input_iterator_tag, char> {
    friend class T_iterator;
public:
    T_filter_iterator(const std::string& filename, std::function<bool(const value_type&)>, std::fstream::openmode mode = std::fstream::in);
    T_filter_iterator(T_filter_iterator&&);
    T_filter_iterator(const T_filter_iterator&);
    T_filter_iterator& operator=(const T_filter_iterator&);
    T_filter_iterator& operator++();
    value_type operator*();
    bool operator==(const T_filter_iterator&) const;
    bool operator!=(const T_filter_iterator&) const;
    bool operator==(const T_iterator&) const;
    bool operator!=(const T_iterator&) const;
    bool check(const value_type&) const;
private:
    std::string filename;
    std::unique_ptr<std::ifstream> file;
    char cur;
    std::ifstream::pos_type pos;
    std::function<bool(const value_type&)> predicate;
};

//Класс итератора для последовательности списка 3
class T_iterator : public std::iterator<std::input_iterator_tag, char> {
public:
    T_iterator(const std::string& filename, std::fstream::openmode mode = std::fstream::in);
    T_iterator(T_iterator&&);
    T_iterator(const T_iterator&);
    T_iterator& operator=(const T_iterator&);
    T_iterator& operator++();
    char operator*();
    bool operator==(const T_iterator&) const;
    bool operator!=(const T_iterator&) const;
    bool operator==(const T_filter_iterator&) const;
    bool operator!=(const T_filter_iterator&) const;
private:
    std::string filename;
    std::unique_ptr<std::ifstream> file;
    char cur;
    std::ifstream::pos_type pos;
};

//Класс последовательности списка 3
class Textseq : public Iterated<T_iterator, T_filter_iterator> {
public:
    Textseq(const std::string& filename);
    Textseq();
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    fiterator filter(std::function<bool(const value_type&)>);
private:
    std::string filename;
};

#endif

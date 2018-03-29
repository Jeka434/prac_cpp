#ifndef TEXTSEQ_H
#define TEXTSEQ_H value

#include <fstream>
#include "Iterated.h"

//Класс итератора для последовательности списка 3
class T_iterator : public std::iterator<std::input_iterator_tag, char> {
public:
    typedef bool (*predic_t)(const char&);

    predic_t check = [](const char&) { return true; };

    T_iterator(const std::string& filename, std::fstream::openmode mode = std::fstream::in);
    T_iterator(T_iterator&&);
    T_iterator(const T_iterator&);
    T_iterator& operator=(const T_iterator&);
    ~T_iterator();
    T_iterator& operator++();
    char operator*();
    bool operator==(const T_iterator&);
    bool operator!=(const T_iterator&);
private:

    std::string filename;
    std::ifstream *file;
    char cur;
    std::ifstream::pos_type pos;
};

//Класс последовательности списка 3
class Textseq : public Iterated<T_iterator> {
public:
    Textseq(const std::string& filename);
    Textseq();
    ~Textseq();
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    iterator filter(predic_t);
private:
    std::string filename;
};

#endif

#include <fstream>
#include "Iterated.h"
#include "Textseq.h"

//class T_iterator

T_iterator::T_iterator(const std::string& name, std::fstream::openmode mode) :
    filename(name),
        file((name == "") ? (new std::ifstream()) : (new std::ifstream(name, mode))),
            cur(file->get()), pos(file->tellg()) {

    if (name != "" && !file->is_open()) throw std::ios_base::failure("Not opened");
}

T_iterator::T_iterator(T_iterator && other) :
    filename(other.filename), file(other.file), cur(other.cur), pos(other.pos) {

    other.file = nullptr;
}

T_iterator::T_iterator(const T_iterator& other) :
    filename(other.filename), file(new std::ifstream(filename)), cur(other.cur), pos(other.pos) {

    file->seekg(pos);
}

T_iterator & T_iterator::operator=(const T_iterator& other) {
    delete file;
    filename = other.filename;
    pos = other.pos;
    cur = other.cur;
    file = new std::ifstream(filename);
    file->seekg(pos);
    return *this;
}

T_iterator::~T_iterator() {
    delete file;
}

T_iterator& T_iterator::operator++() {
    if (file->eof()) return *this;
    do {
        cur = file->get();
        pos = file->tellg();
    } while (!file->eof() && !check(cur));
    return *this;
}

char T_iterator::operator*() {
    return cur;
}

bool T_iterator::operator==(const T_iterator& other) {
    return filename == other.filename && pos == other.pos;
}

bool T_iterator::operator!=(const T_iterator& other) {
    return filename != other.filename || pos != other.pos;
}

//class Textseq

Textseq::Textseq(const std::string& name) : filename(name) {}

Textseq::Textseq() : filename() {}

Textseq::~Textseq() {}

Textseq::iterator Textseq::begin() {
    return iterator(filename);
}

Textseq::const_iterator Textseq::begin() const {
    return const_iterator(filename);
}

Textseq::iterator Textseq::end() {
    return iterator(filename, std::fstream::in | std::fstream::ate);
}

Textseq::const_iterator Textseq::end() const {
    return const_iterator(filename, std::fstream::in | std::fstream::ate);
}

Textseq::iterator Textseq::filter(predic_t func) {
    iterator i = this->begin();
    i.check = func;
    if (!i.check(*i)) {
        ++i;
    }
    return i;
}

#include <fstream>
#include <memory>
#include "Iterated.h"
#include "Textseq.h"

//class T_filter_iterator

T_filter_iterator::T_filter_iterator(const std::string& name, std::function<bool(const value_type&)> pred, std::fstream::openmode mode) :
    filename(name), file((name == "") ? (new std::ifstream()) : (new std::ifstream(name, mode))),
        cur(file->get()), pos(file->tellg()), predicate(pred) {

    if (name != "" && !file->is_open()) throw std::ios_base::failure("Not opened");
}

T_filter_iterator::T_filter_iterator(T_filter_iterator && other) :
    filename(other.filename), file(other.file.release()), cur(other.cur), pos(other.pos), predicate(other.predicate) {
}

T_filter_iterator::T_filter_iterator(const T_filter_iterator& other) :
    filename(other.filename), file(new std::ifstream(filename)), cur(other.cur), pos(other.pos), predicate(other.predicate) {

    file->seekg(pos);
}

T_filter_iterator& T_filter_iterator::operator=(const T_filter_iterator& other) {
    filename = other.filename;
    pos = other.pos;
    cur = other.cur;
    file.reset(new std::ifstream(filename));
    file->seekg(pos);
    predicate = other.predicate;
    return *this;
}

T_filter_iterator& T_filter_iterator::operator++() {
    if (file->eof()) return *this;
    do {
        cur = file->get();
        pos = file->tellg();
    } while (!file->eof() && !check(cur));
    return *this;
}

char T_filter_iterator::operator*() {
    return cur;
}

bool T_filter_iterator::operator==(const T_filter_iterator& other) const {
    return filename == other.filename && pos == other.pos;
}

bool T_filter_iterator::operator!=(const T_filter_iterator& other) const {
    return filename != other.filename || pos != other.pos;
}

bool T_filter_iterator::operator==(const T_iterator& other) const {
    return other == *this;
}

bool T_filter_iterator::operator!=(const T_iterator& other) const {
    return other != *this;
}

bool T_filter_iterator::check(const value_type& c) const {
    return predicate(c);
}

//class T_iterator

T_iterator::T_iterator(const std::string& name, std::fstream::openmode mode) :
    filename(name), file((name == "") ? (new std::ifstream()) : (new std::ifstream(name, mode))),
        cur(file->get()), pos(file->tellg()) {

    if (name != "" && !file->is_open()) throw std::ios_base::failure("Not opened");
}

T_iterator::T_iterator(T_iterator && other) :
    filename(other.filename), file(other.file.release()), cur(other.cur), pos(other.pos) {
}

T_iterator::T_iterator(const T_iterator& other) :
    filename(other.filename), file(new std::ifstream(filename)), cur(other.cur), pos(other.pos) {

    file->seekg(pos);
}

T_iterator& T_iterator::operator=(const T_iterator& other) {
    filename = other.filename;
    pos = other.pos;
    cur = other.cur;
    file.reset(new std::ifstream(filename));
    file->seekg(pos);
    return *this;
}

T_iterator& T_iterator::operator++() {
    if (file->eof()) return *this;
    cur = file->get();
    pos = file->tellg();
    return *this;
}

char T_iterator::operator*() {
    return cur;
}

bool T_iterator::operator==(const T_iterator& other) const {
    return filename == other.filename && pos == other.pos;
}

bool T_iterator::operator!=(const T_iterator& other) const {
    return filename != other.filename || pos != other.pos;
}

bool T_iterator::operator==(const T_filter_iterator& other) const {
    return filename == other.filename && pos == other.pos;
}

bool T_iterator::operator!=(const T_filter_iterator& other) const {
    return filename != other.filename || pos != other.pos;
}

//class Textseq

Textseq::Textseq(const std::string& name) : filename(name) {}

Textseq::Textseq() : filename() {}

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

Textseq::fiterator Textseq::filter(std::function<bool(const value_type&)> pred) {
    fiterator i(filename, pred);
    if (!i.check(*i)) {
        ++i;
    }
    return i;
}

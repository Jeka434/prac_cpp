#include <typeinfo>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "Iterated.h"
#include "Fibonacci.h"
#include "Journal.h"
#include "Textseq.h"

using std::cout;
using std::endl;

template <typename It>
void print_iterated(const Iterated<It>& seq) {
    for (auto i : seq) {
        cout << i << ' ';
    }
}

bool J_f(const J_record& rec);
bool F_f(const int& k);
bool T_f(const char& c);
time_t random_time();

int main() {
//Fibonacci
    cout << "Fibonacci empty:\n";
    Fibonacci F(0, 0);
    for (auto i : F) {
        cout << i << ' ';
    }
    cout << "\nFibonacci not empty:\n";
    F = Fibonacci();
    for (auto i : F) {
        cout << i << ' ';
    }
    cout << "\n\nFibonacci algorithm function:\n";
    cout << *std::adjacent_find(F.begin(), F.end());
    cout << "\n\nFibonacci print function:\n";
    print_iterated(F);
    cout << "\nFibonacci filter function:\n";
    for (auto i = F.filter(F_f); i != F.end(); ++i) {
        cout << *i << endl;
    }
    cout << endl;

//Journal
    cout << "Journal empty:\n";
    Journal J;
    for (auto i : J) {
        cout << i;
    }
    cout << "\nJournal not empty:\n";
    J.push_back(random_time(), "first");
    J.push_back(random_time(), "second");
    J.push_back(random_time(), "hello");
    J.push_back(random_time(), "hello");
    J.push_back(random_time(), "goodbye");
    for (auto i : J) {
        cout << i;
    }
    cout << "\nJournal algorithm function:\n";
    cout << *std::adjacent_find(J.begin(), J.end());
    cout << "\nJournal print function:\n";
    print_iterated(J);
    cout << "\nJournal filter function:\n";
    for (auto i = J.filter(J_f); i != J.end(); ++i) {
        cout << *i << endl;
    }
    cout << endl;

//Textseq
    cout << "Textseq empty:\n";
    Textseq T;
    for (auto i : T) {
        cout << i << ' ';
    }
    cout << "\nTextseq not empty:\n";
    T = Textseq("Text.txt");
    for (auto i : T) {
        cout << i << ' ';
    }
    cout << "\nTextseq algorithm function:\n";
    cout << *std::adjacent_find(T.begin(), T.end());
    cout << "\n\nTextseq print function:\n";
    print_iterated(T);
    cout << "\nTextseq filter function:\n";
    for (auto i = T.filter(T_f); i != T.end(); ++i) {
        cout << *i << ' ';
    }
    cout << endl;

    return 0;
}

time_t random_time() {
    tm t;
    t.tm_sec = rand() % 60;
    t.tm_min = rand() % 60;
    t.tm_hour = rand() % 24;
    t.tm_mday = rand() % 28;
    t.tm_mon = rand() % 12;
    t.tm_year = rand() % 5 + 110;
    t.tm_wday = rand() % 7;
    t.tm_yday = rand() % 366;
    t.tm_isdst = 0;
    return mktime(&t);
}

bool J_f(const J_record& rec) {
    return 5 >= rec.message.length();
}

bool F_f(const int& k) {
    return !(k % 2);
}

bool T_f(const char& c) {
    return c >= 'a' && c <= 'z';
}

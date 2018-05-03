#ifndef ITERATED_H
#define ITERATED_H value

#include <functional>

template <typename It, typename fIt, typename cIt = It>
class Iterated {
public:
    typedef It iterator;
    typedef cIt const_iterator;
    typedef fIt fiterator;
    typedef typename iterator::value_type value_type;
    typedef typename iterator::reference reference;
    virtual ~Iterated() {};
    virtual iterator begin() = 0;
    virtual const_iterator begin() const = 0;
    virtual iterator end() = 0;
    virtual const_iterator end() const = 0;
    virtual fiterator filter(std::function<bool(const value_type&)>) = 0;
};

#endif

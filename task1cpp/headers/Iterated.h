#ifndef ITERATED_H
#define ITERATED_H value

template <typename It>
class Iterated {
public:
    typedef It iterator;
    typedef iterator const_iterator;
    typedef typename iterator::value_type value_type;
    typedef typename iterator::predic_t predic_t;
    virtual ~Iterated() {}
    virtual iterator begin() = 0;
    virtual const_iterator begin() const = 0;
    virtual iterator end() = 0;
    virtual const_iterator end() const = 0;
    virtual iterator filter(predic_t) = 0;
};

#endif

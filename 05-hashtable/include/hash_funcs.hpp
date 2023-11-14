#ifndef _HASH_FUNCS_HPP
#define _HASH_FUNCS_HPP



class HashFunc {
public:
    virtual unsigned long hash(const int& k) const = 0;
    virtual unsigned long hash(const std::string& k) const = 0;
};

class DefaultHashFunc: public HashFunc {
public:
    virtual unsigned long hash(const int& k) const {
        return k;
    }

    virtual unsigned long hash(const std::string& k) const
    {
        unsigned long hash = 0;
        for (const char& c: k) {
            hash += (unsigned long)c;
        }
        return hash;
    }
};

#endif

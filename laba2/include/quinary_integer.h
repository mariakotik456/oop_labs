#ifndef QUINARY_INTEGER_H
#define QUINARY_INTEGER_H

#include <vector>
#include <string>
#include <initializer_list>
#include <stdexcept>

class QuinaryInteger
{
private:
    std::vector<unsigned char> digits_;

public:
    QuinaryInteger();
    QuinaryInteger(const size_t &n, unsigned char value = 0);
    QuinaryInteger(const std::initializer_list<unsigned char> &digits);
    QuinaryInteger(const std::string &str);
    QuinaryInteger(const QuinaryInteger &other);
    QuinaryInteger(QuinaryInteger &&other) noexcept;

    QuinaryInteger &operator=(const QuinaryInteger &other);
    QuinaryInteger &operator=(QuinaryInteger &&other) noexcept;

    virtual ~QuinaryInteger() noexcept;

    size_t size() const;
    std::string toString() const;
    const std::vector<unsigned char> &getDigits() const;

    QuinaryInteger add(const QuinaryInteger &other) const;
    QuinaryInteger subtract(const QuinaryInteger &other) const;
    QuinaryInteger copy() const;

    bool equals(const QuinaryInteger &other) const;
    bool lessThan(const QuinaryInteger &other) const;
    bool greaterThan(const QuinaryInteger &other) const;

    QuinaryInteger addAssign(const QuinaryInteger &other);
    QuinaryInteger subtractAssign(const QuinaryInteger &other);

private:
    void removeLeadingZeros();
    int compare(const QuinaryInteger &other) const;
};

#endif
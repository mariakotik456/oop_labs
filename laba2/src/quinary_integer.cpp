#include "quinary_integer.h"
#include <algorithm>
#include <stdexcept>

QuinaryInteger::QuinaryInteger() : digits_({0}) {}

QuinaryInteger::QuinaryInteger(const size_t &n, unsigned char value)
    : digits_(n, value)
{
    if (value > 4)
    {
        throw std::invalid_argument("Quinary digit must be between 0 and 4");
    }
    if (n == 0)
    {
        digits_ = {0};
    }
    removeLeadingZeros();
}

QuinaryInteger::QuinaryInteger(const std::initializer_list<unsigned char> &digits)
    : digits_(digits)
{
    for (unsigned char digit : digits_)
    {
        if (digit > 4)
        {
            throw std::invalid_argument("Quinary digit must be between 0 and 4");
        }
    }
    std::reverse(digits_.begin(), digits_.end());
    removeLeadingZeros();
}

QuinaryInteger::QuinaryInteger(const std::string &str)
{
    if (str.empty())
    {
        digits_ = {0};
        return;
    }

    for (auto it = str.rbegin(); it != str.rend(); ++it)
    {
        if (*it < '0' || *it > '4')
        {
            throw std::invalid_argument("Invalid quinary digit. Must be 0-4");
        }
        digits_.push_back(*it - '0');
    }
    removeLeadingZeros();
}

QuinaryInteger::QuinaryInteger(const QuinaryInteger &other)
    : digits_(other.digits_) {}

QuinaryInteger::QuinaryInteger(QuinaryInteger &&other) noexcept
    : digits_(std::move(other.digits_))
{
    other.digits_ = {0};
}

QuinaryInteger &QuinaryInteger::operator=(const QuinaryInteger &other)
{
    if (this != &other)
    {
        digits_ = other.digits_;
    }
    return *this;
}

QuinaryInteger &QuinaryInteger::operator=(QuinaryInteger &&other) noexcept
{
    if (this != &other)
    {
        digits_ = std::move(other.digits_);
        other.digits_ = {0};
    }
    return *this;
}

QuinaryInteger::~QuinaryInteger() noexcept {}

void QuinaryInteger::removeLeadingZeros()
{
    while (digits_.size() > 1 && digits_.back() == 0)
    {
        digits_.pop_back();
    }
    if (digits_.empty())
    {
        digits_ = {0};
    }
}

size_t QuinaryInteger::size() const
{
    return digits_.size();
}

std::string QuinaryInteger::toString() const
{
    std::string result;
    for (auto it = digits_.rbegin(); it != digits_.rend(); ++it)
    {
        result += std::to_string(*it);
    }
    return result;
}

const std::vector<unsigned char> &QuinaryInteger::getDigits() const
{
    return digits_;
}

int QuinaryInteger::compare(const QuinaryInteger &other) const
{
    if (digits_.size() != other.digits_.size())
    {
        return digits_.size() < other.digits_.size() ? -1 : 1;
    }

    for (int i = digits_.size() - 1; i >= 0; --i)
    {
        if (digits_[i] != other.digits_[i])
        {
            return digits_[i] < other.digits_[i] ? -1 : 1;
        }
    }
    return 0;
}

QuinaryInteger QuinaryInteger::add(const QuinaryInteger &other) const
{
    QuinaryInteger result;
    result.digits_.clear();

    size_t max_size = std::max(digits_.size(), other.digits_.size());
    unsigned char carry = 0;

    for (size_t i = 0; i < max_size || carry; ++i)
    {
        unsigned char sum = carry;
        if (i < digits_.size())
            sum += digits_[i];
        if (i < other.digits_.size())
            sum += other.digits_[i];

        result.digits_.push_back(sum % 5);
        carry = sum / 5;
    }

    return result;
}

QuinaryInteger QuinaryInteger::subtract(const QuinaryInteger &other) const
{
    if (lessThan(other))
    {
        throw std::invalid_argument("Result would be negative");
    }

    QuinaryInteger result;
    result.digits_.clear();

    unsigned char borrow = 0;
    for (size_t i = 0; i < digits_.size(); ++i)
    {
        unsigned char sub = digits_[i] - borrow;
        if (i < other.digits_.size())
        {
            if (sub < other.digits_[i])
            {
                sub += 5;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }
            sub -= other.digits_[i];
        }
        result.digits_.push_back(sub);
    }

    result.removeLeadingZeros();
    return result;
}

QuinaryInteger QuinaryInteger::copy() const
{
    return QuinaryInteger(*this);
}

bool QuinaryInteger::equals(const QuinaryInteger &other) const
{
    return compare(other) == 0;
}

bool QuinaryInteger::lessThan(const QuinaryInteger &other) const
{
    return compare(other) < 0;
}

bool QuinaryInteger::greaterThan(const QuinaryInteger &other) const
{
    return compare(other) > 0;
}

QuinaryInteger QuinaryInteger::addAssign(const QuinaryInteger &other)
{
    *this = this->add(other);
    return *this;
}

QuinaryInteger QuinaryInteger::subtractAssign(const QuinaryInteger &other)
{
    *this = this->subtract(other);
    return *this;
}
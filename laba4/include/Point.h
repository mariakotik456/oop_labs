#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <type_traits>

// Замена concept на традиционный SFINAE
template <typename T, typename = void>
struct is_scalar : std::false_type
{
};

template <typename T>
struct is_scalar<T, std::enable_if_t<std::is_scalar_v<T>>> : std::true_type
{
};

template <typename T>
constexpr bool is_scalar_v = is_scalar<T>::value;

template <typename T>
class Point
{
private:
    T x_, y_;

    // Проверка типа при компиляции
    static_assert(is_scalar_v<T>, "T must be a scalar type");

public:
    Point(T x = 0, T y = 0) : x_(x), y_(y) {}

    Point(const Point &other) : x_(other.x_), y_(other.y_) {}

    Point &operator=(const Point &other)
    {
        if (this != &other)
        {
            x_ = other.x_;
            y_ = other.y_;
        }
        return *this;
    }

    bool operator==(const Point &other) const
    {
        return x_ == other.x_ && y_ == other.y_;
    }

    bool operator!=(const Point &other) const
    {
        return !(*this == other);
    }

    T x() const { return x_; }
    T y() const { return y_; }

    friend std::ostream &operator<<(std::ostream &os, const Point &p)
    {
        os << "(" << p.x_ << ", " << p.y_ << ")";
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Point &p)
    {
        is >> p.x_ >> p.y_;
        return is;
    }
};

#endif
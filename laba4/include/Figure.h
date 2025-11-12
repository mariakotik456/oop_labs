#ifndef FIGURE_H
#define FIGURE_H

#include "Point.h"
#include <memory>
#include <iostream>

template <typename T>
class Figure
{
    static_assert(is_scalar_v<T>, "T must be a scalar type");

public:
    virtual ~Figure() = default;

    virtual Point<T> geometricCenter() const = 0;
    virtual double area() const = 0;
    virtual void printVertices(std::ostream &os) const = 0;
    virtual void readFromInput(std::istream &is) = 0;

    virtual operator double() const { return area(); }

    virtual std::shared_ptr<Figure<T>> clone() const = 0;

    virtual bool operator==(const Figure<T> &other) const = 0;
    bool operator!=(const Figure<T> &other) const
    {
        return !(*this == other);
    }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Figure<T> &fig)
{
    fig.printVertices(os);
    return os;
}

template <typename T>
std::istream &operator>>(std::istream &is, Figure<T> &fig)
{
    fig.readFromInput(is);
    return is;
}

#endif
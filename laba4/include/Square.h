#ifndef SQUARE_H
#define SQUARE_H

#include "Figure.h"
#include <memory>
#include <vector>
#include <cmath>

template <typename T>
class Square : public Figure<T>
{
    static_assert(is_scalar_v<T>, "T must be a scalar type");

private:
    std::unique_ptr<Point<T>> center_;
    T side_;

public:
    Square()
        : center_(std::make_unique<Point<T>>()), side_(0) {}

    Square(Point<T> center, T side)
        : center_(std::make_unique<Point<T>>(center)), side_(side) {}

    Square(const Square &other)
        : center_(std::make_unique<Point<T>>(*other.center_)), side_(other.side_) {}

    Square &operator=(const Square &other)
    {
        if (this != &other)
        {
            center_ = std::make_unique<Point<T>>(*other.center_);
            side_ = other.side_;
        }
        return *this;
    }

    Point<T> geometricCenter() const override
    {
        return *center_;
    }

    double area() const override
    {
        return side_ * side_;
    }

    void printVertices(std::ostream &os) const override
    {
        auto vertices = getVertices();
        os << "Square vertices: ";
        for (size_t i = 0; i < vertices.size(); ++i)
        {
            os << vertices[i];
            if (i < vertices.size() - 1)
                os << ", ";
        }
    }

    void readFromInput(std::istream &is) override
    {
        Point<T> center;
        T side;
        is >> center >> side;
        *this = Square<T>(center, side);
    }

    std::shared_ptr<Figure<T>> clone() const override
    {
        return std::make_shared<Square<T>>(*this);
    }

    bool operator==(const Figure<T> &other) const override
    {
        const Square *otherSquare = dynamic_cast<const Square *>(&other);
        if (!otherSquare)
            return false;
        return *center_ == *otherSquare->center_ && side_ == otherSquare->side_;
    }

private:
    std::vector<Point<T>> getVertices() const
    {
        T half = side_ / 2;
        T x = center_->x(), y = center_->y();

        return {
            Point<T>(x - half, y - half),
            Point<T>(x + half, y - half),
            Point<T>(x + half, y + half),
            Point<T>(x - half, y + half)};
    }
};

#endif
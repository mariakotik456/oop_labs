#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Figure.h"
#include <memory>
#include <cmath>

template <typename T>
class Triangle : public Figure<T>
{
    static_assert(is_scalar_v<T>, "T must be a scalar type");

private:
    std::unique_ptr<Point<T>> p1_, p2_, p3_;

public:
    Triangle()
        : p1_(std::make_unique<Point<T>>()),
          p2_(std::make_unique<Point<T>>()),
          p3_(std::make_unique<Point<T>>()) {}

    Triangle(Point<T> a, Point<T> b, Point<T> c)
        : p1_(std::make_unique<Point<T>>(a)),
          p2_(std::make_unique<Point<T>>(b)),
          p3_(std::make_unique<Point<T>>(c)) {}

    Triangle(const Triangle &other)
        : p1_(std::make_unique<Point<T>>(*other.p1_)),
          p2_(std::make_unique<Point<T>>(*other.p2_)),
          p3_(std::make_unique<Point<T>>(*other.p3_)) {}

    Triangle &operator=(const Triangle &other)
    {
        if (this != &other)
        {
            p1_ = std::make_unique<Point<T>>(*other.p1_);
            p2_ = std::make_unique<Point<T>>(*other.p2_);
            p3_ = std::make_unique<Point<T>>(*other.p3_);
        }
        return *this;
    }

    Point<T> geometricCenter() const override
    {
        T x = (p1_->x() + p2_->x() + p3_->x()) / 3;
        T y = (p1_->y() + p2_->y() + p3_->y()) / 3;
        return Point<T>(x, y);
    }

    double area() const override
    {
        T x1 = p1_->x(), y1 = p1_->y();
        T x2 = p2_->x(), y2 = p2_->y();
        T x3 = p3_->x(), y3 = p3_->y();

        return std::abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
    }

    void printVertices(std::ostream &os) const override
    {
        os << "Triangle vertices: " << *p1_ << ", " << *p2_ << ", " << *p3_;
    }

    void readFromInput(std::istream &is) override
    {
        Point<T> a, b, c;
        is >> a >> b >> c;
        *this = Triangle<T>(a, b, c);
    }

    std::shared_ptr<Figure<T>> clone() const override
    {
        return std::make_shared<Triangle<T>>(*this);
    }

    bool operator==(const Figure<T> &other) const override
    {
        const Triangle *otherTriangle = dynamic_cast<const Triangle *>(&other);
        if (!otherTriangle)
            return false;
        return *p1_ == *otherTriangle->p1_ &&
               *p2_ == *otherTriangle->p2_ &&
               *p3_ == *otherTriangle->p3_;
    }
};

#endif
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Figure.h"
#include <memory>
#include <vector>
#include <cmath>

template <typename T>
class Rectangle : public Figure<T>
{
    static_assert(is_scalar_v<T>, "T must be a scalar type");

private:
    std::unique_ptr<Point<T>> center_;
    T width_, height_;

public:
    Rectangle()
        : center_(std::make_unique<Point<T>>()), width_(0), height_(0) {}

    Rectangle(Point<T> center, T width, T height)
        : center_(std::make_unique<Point<T>>(center)), width_(width), height_(height) {}

    Rectangle(const Rectangle &other)
        : center_(std::make_unique<Point<T>>(*other.center_)),
          width_(other.width_),
          height_(other.height_) {}

    Rectangle &operator=(const Rectangle &other)
    {
        if (this != &other)
        {
            center_ = std::make_unique<Point<T>>(*other.center_);
            width_ = other.width_;
            height_ = other.height_;
        }
        return *this;
    }

    Point<T> geometricCenter() const override
    {
        return *center_;
    }

    double area() const override
    {
        return width_ * height_;
    }

    void printVertices(std::ostream &os) const override
    {
        auto vertices = getVertices();
        os << "Rectangle vertices: ";
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
        T width, height;
        is >> center >> width >> height;
        *this = Rectangle<T>(center, width, height);
    }

    std::shared_ptr<Figure<T>> clone() const override
    {
        return std::make_shared<Rectangle<T>>(*this);
    }

    bool operator==(const Figure<T> &other) const override
    {
        const Rectangle *otherRect = dynamic_cast<const Rectangle *>(&other);
        if (!otherRect)
            return false;
        return *center_ == *otherRect->center_ &&
               width_ == otherRect->width_ &&
               height_ == otherRect->height_;
    }

private:
    std::vector<Point<T>> getVertices() const
    {
        T half_width = width_ / 2;
        T half_height = height_ / 2;
        T x = center_->x(), y = center_->y();

        return {
            Point<T>(x - half_width, y - half_height),
            Point<T>(x + half_width, y - half_height),
            Point<T>(x + half_width, y + half_height),
            Point<T>(x - half_width, y + half_height)};
    }
};

#endif
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Array.h"
#include "Figure.h"
#include "Triangle.h"
#include "Square.h"
#include "Rectangle.h"
#include <iostream>

template <typename T>
void printAllFiguresInfo(const Array<std::shared_ptr<Figure<T>>> &figures)
{
    for (size_t i = 0; i < figures.size(); ++i)
    {
        std::cout << "Figure " << i + 1 << ":" << std::endl;
        figures[i]->printVertices(std::cout);
        std::cout << std::endl;
        std::cout << "Geometric center: " << figures[i]->geometricCenter() << std::endl;
        std::cout << "Area: " << figures[i]->area() << std::endl;
        std::cout << std::endl;
    }
}

template <typename T>
double calculateTotalArea(const Array<std::shared_ptr<Figure<T>>> &figures)
{
    double total = 0;
    for (size_t i = 0; i < figures.size(); ++i)
    {
        total += static_cast<double>(*figures[i]);
    }
    return total;
}

template <typename T>
std::shared_ptr<Figure<T>> createTriangle()
{
    std::cout << "Enter triangle vertices (x1 y1 x2 y2 x3 y3): ";
    T x1, y1, x2, y2, x3, y3;
    std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    return std::make_shared<Triangle<T>>(
        Point<T>(x1, y1), Point<T>(x2, y2), Point<T>(x3, y3));
}

template <typename T>
std::shared_ptr<Figure<T>> createSquare()
{
    std::cout << "Enter square center and side (center_x center_y side): ";
    T x, y, side;
    std::cin >> x >> y >> side;
    return std::make_shared<Square<T>>(Point<T>(x, y), side);
}

template <typename T>
std::shared_ptr<Figure<T>> createRectangle()
{
    std::cout << "Enter rectangle center, width and height (center_x center_y width height): ";
    T x, y, width, height;
    std::cin >> x >> y >> width >> height;
    return std::make_shared<Rectangle<T>>(Point<T>(x, y), width, height);
}

#endif
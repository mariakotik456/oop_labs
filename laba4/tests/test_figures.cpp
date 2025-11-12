#include <gtest/gtest.h>
#include "../include/Triangle.h"
#include "../include/Square.h"
#include "../include/Rectangle.h"
#include "../include/Array.h"
#include "../include/functions.h"
#include <sstream>
#include <memory>

TEST(PointTest, EqualityOperator)
{
    Point<int> p1(1, 2);
    Point<int> p2(1, 2);
    Point<int> p3(2, 2);

    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(TriangleTest, ConstructorAndArea)
{
    Point<int> a(0, 0), b(4, 0), c(2, 3);
    Triangle<int> triangle(a, b, c);

    EXPECT_NEAR(triangle.area(), 6.0, 1e-9);
    EXPECT_EQ(triangle.geometricCenter().x(), 2);
    EXPECT_EQ(triangle.geometricCenter().y(), 1);
}

TEST(TriangleTest, CopyConstructor)
{
    Point<double> a(0, 0), b(4, 0), c(2, 3);
    Triangle<double> triangle1(a, b, c);
    Triangle<double> triangle2 = triangle1;

    EXPECT_TRUE(triangle1 == triangle2);
}

TEST(SquareTest, ConstructorAndArea)
{
    Point<double> center(2, 2);
    Square<double> square(center, 4);

    EXPECT_NEAR(square.area(), 16.0, 1e-9);
    EXPECT_TRUE(square.geometricCenter() == center);
}

TEST(RectangleTest, ConstructorAndArea)
{
    Point<float> center(3, 3);
    Rectangle<float> rectangle(center, 6, 4);

    EXPECT_NEAR(rectangle.area(), 24.0, 1e-9);
    EXPECT_TRUE(rectangle.geometricCenter() == center);
}

TEST(ArrayTest, AddAndRemove)
{
    Array<std::shared_ptr<Figure<double>>> array;

    auto triangle = std::make_shared<Triangle<double>>(
        Point<double>(0, 0), Point<double>(4, 0), Point<double>(2, 3));
    array.push_back(triangle);

    EXPECT_EQ(array.size(), 1);
    array.remove(0);
    EXPECT_EQ(array.size(), 0);
}

TEST(ArrayTest, TotalArea)
{
    Array<std::shared_ptr<Figure<double>>> array;

    auto square = std::make_shared<Square<double>>(Point<double>(2, 2), 4);
    array.push_back(square);

    auto rectangle = std::make_shared<Rectangle<double>>(Point<double>(3, 3), 6, 4);
    array.push_back(rectangle);

    EXPECT_NEAR(calculateTotalArea(array), 40.0, 1e-9);
}

TEST(ArrayTest, MoveSemantics)
{
    Array<int> array1;
    array1.push_back(1);
    array1.push_back(2);

    Array<int> array2 = std::move(array1); // Move constructor
    EXPECT_EQ(array2.size(), 2);
    EXPECT_EQ(array1.size(), 0);

    Array<int> array3;
    array3 = std::move(array2); // Move assignment
    EXPECT_EQ(array3.size(), 2);
    EXPECT_EQ(array2.size(), 0);
}

TEST(FigureTest, DoubleConversion)
{
    Square<double> square(Point<double>(2, 2), 4);
    double area = static_cast<double>(square);
    EXPECT_NEAR(area, 16.0, 1e-9);
}
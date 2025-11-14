#include <gtest/gtest.h>
#include "block_tracking_memory_resource.h"
#include "dynamic_array.h"
#include <string>

TEST(DynamicArrayTest, IntArray)
{
    BlockTrackingMemoryResource memory_resource;
    DynamicArray<int> array{std::pmr::polymorphic_allocator<int>(&memory_resource)};

    array.push_back(1);
    array.push_back(2);
    array.push_back(3);

    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array[0], 1);
    EXPECT_EQ(array[1], 2);
    EXPECT_EQ(array[2], 3);

    int sum = 0;
    for (auto it = array.begin(); it != array.end(); ++it)
    {
        sum += *it;
    }
    EXPECT_EQ(sum, 6);

    array.pop_back();
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array[1], 2);
}

TEST(DynamicArrayTest, StructArray)
{
    struct Point
    {
        int x, y;
        Point(int x, int y) : x(x), y(y) {}
    };

    BlockTrackingMemoryResource memory_resource;
    DynamicArray<Point> array{std::pmr::polymorphic_allocator<Point>(&memory_resource)};

    array.push_back(Point(1, 2));
    array.push_back(Point(3, 4));

    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array[0].x, 1);
    EXPECT_EQ(array[0].y, 2);
    EXPECT_EQ(array[1].x, 3);
    EXPECT_EQ(array[1].y, 4);
}

TEST(DynamicArrayTest, MemoryReuse)
{
    BlockTrackingMemoryResource memory_resource;
    DynamicArray<int> array{std::pmr::polymorphic_allocator<int>(&memory_resource)};

    for (int i = 0; i < 10; ++i)
    {
        array.push_back(i);
    }
    size_t allocated_after_push = memory_resource.get_allocated_blocks_count();

    for (int i = 0; i < 5; ++i)
    {
        array.pop_back();
    }

    size_t free_blocks_after_pop = memory_resource.get_free_blocks_count();
    EXPECT_GE(free_blocks_after_pop, 5);

    for (int i = 0; i < 5; ++i)
    {
        array.push_back(i + 100);
    }

    EXPECT_LE(memory_resource.get_allocated_blocks_count(), allocated_after_push + 2);
}

TEST(DynamicArrayTest, IteratorFunctionality)
{
    BlockTrackingMemoryResource memory_resource;
    DynamicArray<int> array{std::pmr::polymorphic_allocator<int>(&memory_resource)};

    array.push_back(10);
    array.push_back(20);
    array.push_back(30);

    auto it1 = array.begin();
    EXPECT_EQ(*it1, 10);
    ++it1;
    EXPECT_EQ(*it1, 20);

    auto it2 = array.begin();
    auto it3 = it2++;
    EXPECT_EQ(*it3, 10);
    EXPECT_EQ(*it2, 20);

    EXPECT_NE(array.begin(), array.end());
    EXPECT_NE(++array.begin(), array.end());

    int sum = 0;
    for (const auto &elem : array)
    {
        sum += elem;
    }
    EXPECT_EQ(sum, 60);
}

TEST(DynamicArrayTest, AccessMethods)
{
    BlockTrackingMemoryResource memory_resource;
    DynamicArray<int> array{std::pmr::polymorphic_allocator<int>(&memory_resource)};

    array.push_back(100);
    array.push_back(200);

    EXPECT_EQ(array[0], 100);
    EXPECT_EQ(array[1], 200);

    EXPECT_EQ(array.at(0), 100);
    EXPECT_EQ(array.at(1), 200);

    EXPECT_THROW(array.at(5), std::out_of_range);
}

TEST(DynamicArrayTest, ClearTest)
{
    BlockTrackingMemoryResource memory_resource;
    DynamicArray<std::string> array{std::pmr::polymorphic_allocator<std::string>(&memory_resource)};

    array.push_back("hello");
    array.push_back("world");

    EXPECT_EQ(array.size(), 2);
    EXPECT_FALSE(array.empty());

    array.clear();

    EXPECT_EQ(array.size(), 0);
    EXPECT_TRUE(array.empty());
}

TEST(DynamicArrayTest, CopyMoveTest)
{
    BlockTrackingMemoryResource memory_resource;
    DynamicArray<int> original{std::pmr::polymorphic_allocator<int>(&memory_resource)};

    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    DynamicArray<int> copy = original;
    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy[0], 1);
    EXPECT_EQ(copy[1], 2);
    EXPECT_EQ(copy[2], 3);

    DynamicArray<int> moved = std::move(original);
    EXPECT_EQ(moved.size(), 3);
    EXPECT_EQ(moved[0], 1);
    EXPECT_EQ(original.size(), 0);
}
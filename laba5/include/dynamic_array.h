#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <memory_resource>
#include <stdexcept>
#include "block_tracking_memory_resource.h"

template <typename T>
class DynamicArray
{
public:
    using allocator_type = std::pmr::polymorphic_allocator<T>;
    using value_type = T;

    class Iterator
    {
    private:
        T **data_;
        size_t index_;
        size_t size_;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T *;
        using reference = T &;

        Iterator(T **data, size_t index, size_t size)
            : data_(data), index_(index), size_(size) {}

        Iterator &operator++()
        {
            ++index_;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator temp = *this;
            ++index_;
            return temp;
        }

        reference operator*() const
        {
            return *data_[index_];
        }

        pointer operator->() const
        {
            return data_[index_];
        }

        bool operator==(const Iterator &other) const
        {
            return index_ == other.index_ && data_ == other.data_;
        }

        bool operator!=(const Iterator &other) const
        {
            return !(*this == other);
        }
    };

private:
    T **elements_ = nullptr;
    size_t capacity_ = 0;
    size_t size_ = 0;
    allocator_type allocator_;
    std::pmr::polymorphic_allocator<T *> ptr_allocator_;

    void resize(size_t new_capacity)
    {
        T **new_elements = ptr_allocator_.allocate(new_capacity);

        for (size_t i = 0; i < size_; ++i)
        {
            new_elements[i] = elements_[i];
        }

        for (size_t i = size_; i < new_capacity; ++i)
        {
            new_elements[i] = nullptr;
        }

        if (elements_)
        {
            ptr_allocator_.deallocate(elements_, capacity_);
        }

        elements_ = new_elements;
        capacity_ = new_capacity;
    }

public:
    DynamicArray(const allocator_type &alloc = {})
        : allocator_(alloc), ptr_allocator_(alloc.resource()) {}

    DynamicArray(size_t initial_capacity, const allocator_type &alloc = {})
        : allocator_(alloc), ptr_allocator_(alloc.resource())
    {
        resize(initial_capacity);
    }

    ~DynamicArray()
    {
        clear();
        if (elements_)
        {
            ptr_allocator_.deallocate(elements_, capacity_);
        }
    }

    DynamicArray(const DynamicArray &other)
        : allocator_(other.allocator_), ptr_allocator_(other.ptr_allocator_)
    {
        resize(other.capacity_);
        for (size_t i = 0; i < other.size_; ++i)
        {
            push_back(other[i]);
        }
    }

    DynamicArray &operator=(const DynamicArray &other)
    {
        if (this != &other)
        {
            clear();
            resize(other.capacity_);
            for (size_t i = 0; i < other.size_; ++i)
            {
                push_back(other[i]);
            }
        }
        return *this;
    }

    DynamicArray(DynamicArray &&other) noexcept
        : elements_(other.elements_), capacity_(other.capacity_), size_(other.size_),
          allocator_(std::move(other.allocator_)), ptr_allocator_(std::move(other.ptr_allocator_))
    {
        other.elements_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
    }

    DynamicArray &operator=(DynamicArray &&other) noexcept
    {
        if (this != &other)
        {
            clear();
            if (elements_)
            {
                ptr_allocator_.deallocate(elements_, capacity_);
            }

            elements_ = other.elements_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            allocator_ = std::move(other.allocator_);
            ptr_allocator_ = std::move(other.ptr_allocator_);

            other.elements_ = nullptr;
            other.capacity_ = 0;
            other.size_ = 0;
        }
        return *this;
    }

    void push_back(const T &value)
    {
        if (size_ >= capacity_)
        {
            resize(capacity_ == 0 ? 2 : capacity_ * 2);
        }

        elements_[size_] = allocator_.allocate(1);
        std::allocator_traits<allocator_type>::construct(allocator_, elements_[size_], value);
        ++size_;
    }

    void push_back(T &&value)
    {
        if (size_ >= capacity_)
        {
            resize(capacity_ == 0 ? 2 : capacity_ * 2);
        }

        elements_[size_] = allocator_.allocate(1);
        std::allocator_traits<allocator_type>::construct(allocator_, elements_[size_], std::move(value));
        ++size_;
    }

    void pop_back()
    {
        if (size_ > 0)
        {
            --size_;
            std::allocator_traits<allocator_type>::destroy(allocator_, elements_[size_]);
            allocator_.deallocate(elements_[size_], 1);
            elements_[size_] = nullptr;
        }
    }

    T &operator[](size_t index)
    {
        return *elements_[index];
    }

    const T &operator[](size_t index) const
    {
        return *elements_[index];
    }

    T &at(size_t index)
    {
        if (index >= size_)
            throw std::out_of_range("Index out of range");
        return *elements_[index];
    }

    const T &at(size_t index) const
    {
        if (index >= size_)
            throw std::out_of_range("Index out of range");
        return *elements_[index];
    }

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }

    void clear()
    {
        for (size_t i = 0; i < size_; ++i)
        {
            std::allocator_traits<allocator_type>::destroy(allocator_, elements_[i]);
            allocator_.deallocate(elements_[i], 1);
            elements_[i] = nullptr;
        }
        size_ = 0;
    }

    Iterator begin() { return Iterator(elements_, 0, size_); }
    Iterator end() { return Iterator(elements_, size_, size_); }
};

#endif
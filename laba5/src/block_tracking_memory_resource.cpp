#include "block_tracking_memory_resource.h"
#include <iostream>

BlockTrackingMemoryResource::~BlockTrackingMemoryResource()
{
    for (auto &[ptr, size] : allocated_blocks_)
    {
        ::operator delete(ptr, size);
    }
    allocated_blocks_.clear();
    free_blocks_.clear();
}

size_t BlockTrackingMemoryResource::get_allocated_blocks_count() const
{
    return allocated_blocks_.size();
}

size_t BlockTrackingMemoryResource::get_free_blocks_count() const
{
    return free_blocks_.size();
}

void *BlockTrackingMemoryResource::do_allocate(size_t bytes, size_t alignment)
{
    auto it = free_blocks_.lower_bound(bytes);
    if (it != free_blocks_.end())
    {
        void *ptr = it->second;
        free_blocks_.erase(it);
        std::cout << "[Memory] Reused block: " << ptr << " size: " << bytes << "\n";
        return ptr;
    }

    void *ptr = ::operator new(bytes, std::align_val_t(alignment));
    allocated_blocks_[ptr] = bytes;
    std::cout << "[Memory] Allocated new block: " << ptr << " size: " << bytes << "\n";
    return ptr;
}

void BlockTrackingMemoryResource::do_deallocate(void *ptr, size_t bytes, size_t alignment)
{
    auto it = allocated_blocks_.find(ptr);
    if (it == allocated_blocks_.end())
    {
        return;
    }

    size_t original_size = it->second;
    free_blocks_.insert({original_size, ptr});
    std::cout << "[Memory] Deallocated block: " << ptr << " (moved to free pool)\n";
}

bool BlockTrackingMemoryResource::do_is_equal(const std::pmr::memory_resource &other) const noexcept
{
    return this == &other;
}
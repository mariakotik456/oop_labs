#ifndef BLOCK_TRACKING_MEMORY_RESOURCE_H
#define BLOCK_TRACKING_MEMORY_RESOURCE_H

#include <memory_resource>
#include <map>

class BlockTrackingMemoryResource : public std::pmr::memory_resource
{
private:
    std::map<void *, size_t> allocated_blocks_;
    std::multimap<size_t, void *> free_blocks_;

public:
    BlockTrackingMemoryResource() = default;
    ~BlockTrackingMemoryResource();

    BlockTrackingMemoryResource(const BlockTrackingMemoryResource &) = delete;
    BlockTrackingMemoryResource &operator=(const BlockTrackingMemoryResource &) = delete;

    size_t get_allocated_blocks_count() const;
    size_t get_free_blocks_count() const;

protected:
    void *do_allocate(size_t bytes, size_t alignment) override;
    void do_deallocate(void *ptr, size_t bytes, size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource &other) const noexcept override;
};

#endif
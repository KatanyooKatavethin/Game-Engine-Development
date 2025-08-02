#ifndef MEMORYPOOL_HPP
#define MEMORYPOOL_HPP

#include <cstddef>   
#include <memory>    

struct FreeDeleter 
{
    void operator()(void* p) const 
    {
        std::free(p);
    }
};

class MemoryPool
{
public:
    MemoryPool(std::size_t size);
    ~MemoryPool();

    void* allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t));
    void deallocate(void* ptr);

    std::size_t getUsedMemory() const;
    std::size_t getFreeMemory() const;

private:
    struct Block
    {
        Block* next;
        std::size_t size;
    };
    std::unique_ptr<void, FreeDeleter> m_start;

    std::size_t m_size;
    std::size_t m_used;

    Block* m_freeList;
};
#endif 
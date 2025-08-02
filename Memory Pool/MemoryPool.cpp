#include "MemoryPool.hpp"
#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <new>

MemoryPool::MemoryPool(std::size_t size)
    : m_size(size), m_used(0)
{
    void* raw = std::malloc(size);
    assert(raw != nullptr && "Memory allocation failed");
    m_start = std::unique_ptr<void, FreeDeleter>(raw);

    m_freeList = reinterpret_cast<Block*>(m_start.get());
    m_freeList->next = nullptr;
    m_freeList->size = size;
}

MemoryPool::~MemoryPool() 
{
    m_start = nullptr;
    m_freeList = nullptr;
    m_size = 0;
    m_used = 0;
}

void* MemoryPool::allocate(std::size_t size, std::size_t alignment) 
{
    Block* prev = nullptr;
    Block* current = m_freeList;

    while (current) 
    {
        uintptr_t currentAddr = reinterpret_cast<uintptr_t>(current);

        std::size_t headerSize = sizeof(Block*) + alignment - 1;

        uintptr_t alignedAddr = (currentAddr + sizeof(Block) + headerSize) & ~(alignment - 1);
        uintptr_t userPtr = alignedAddr;
        std::size_t padding = userPtr - currentAddr;

        std::size_t totalSize = size + padding;

        if (current->size >= totalSize) 
        {
            if (current->size <= totalSize + sizeof(Block)) 
            {
                if (prev) prev->next = current->next;
                else m_freeList = current->next;
                m_used += current->size;
            }
            else 
            {
                uintptr_t newBlockAddr = currentAddr + totalSize;

                Block* newBlock = reinterpret_cast<Block*>(newBlockAddr);
                newBlock->size = current->size - totalSize;
                newBlock->next = current->next;

                if (prev) prev->next = newBlock;
                else m_freeList = newBlock;

                current->size = totalSize;
                m_used += totalSize;           
            }
            reinterpret_cast<Block**>(userPtr)[-1] = current;

            return reinterpret_cast<void*>(userPtr);
        }
        prev = current;
        current = current->next;
    }

    return nullptr; 
}

void MemoryPool::deallocate(void* ptr) 
{
    if (!ptr) return;

    Block* block = reinterpret_cast<Block**>(ptr)[-1];

    block->next = m_freeList;
    m_freeList = block;

    m_used -= block->size;
}

std::size_t MemoryPool::getUsedMemory() const 
{
    return m_used;
}

std::size_t MemoryPool::getFreeMemory() const 
{
    return m_size - m_used;
}
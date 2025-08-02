#include "MemoryPool.hpp"
#include <iostream>
#include <vector>
#include <cassert>

int main() 
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    {
        constexpr std::size_t poolSize = 1024;
        MemoryPool pool(poolSize);
        std::cout << "Memory pool created: " << poolSize << " bytes\n";

        std::cout << "----------------------------------------------------------\n";
        std::cout << "Allocation\n";

        std::size_t sizeA = 64;
        std::size_t alignA = 16;
        void* a = pool.allocate(sizeA, alignA);
        assert(a != nullptr);
        std::cout << " Allocated a block of memory: " << sizeA << " bytes\n";

        std::size_t sizeB = 128;
        std::size_t alignB = 32;
        void* b = pool.allocate(sizeB, alignB);
        assert(b != nullptr);
        std::cout << " Allocated another block of memory: " << sizeB << " bytes\n";

        std::cout << " Used: " << pool.getUsedMemory() << " bytes\n"; 
        std::cout << "  (1st request: " << sizeA << " bytes + alignment: " << alignA << " bytes = " << sizeA + alignA << " bytes)\n";
        std::cout << "  (2nd request: " << sizeB << " bytes + alignment: " << alignB << " bytes = " << sizeB + alignB << " bytes)\n";

        std::cout << "  (" << sizeA + alignA << " + " << sizeB + alignB << " = " << sizeA + alignA + sizeB + alignB << " bytes + allocator overhead = " << pool.getUsedMemory() << " bytes)\n";

        std::cout << " Free: " << pool.getFreeMemory() << " bytes\n";

        std::cout << "----------------------------------------------------------\n";
        std::cout << "Deallocation\n";

        pool.deallocate(a);
        std::cout << " Deallocated first block of memory\n";

        pool.deallocate(b);
        std::cout << " Deallocated second block of memory\n";

        std::cout << " Memory in use after deallocation: " << pool.getUsedMemory() << " bytes\n";
        std::cout << " Memory available after deallocation: " << pool.getFreeMemory() << " bytes\n";
        std::cout << "----------------------------------------------------------\n";
    }
    assert(_CrtCheckMemory());
    _CrtDumpMemoryLeaks();
    return 0;
}
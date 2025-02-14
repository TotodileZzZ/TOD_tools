#include "AllocatorBase.h"

Allocator::DefaultLowLevelAllocator::DefaultLowLevelAllocator()
{
    _malloc = malloc;
    _free = free;
}

Allocator::DefaultLowLevelAllocator& Allocator::GetSystemAllocatorsTable() const
{
    static DefaultLowLevelAllocator systemAllocatorsTable;
    return systemAllocatorsTable;
}

Allocator::Allocator()
    : LowLevelAllocators(GetSystemAllocatorsTable())
{
    MESSAGE_CLASS_CREATED(Allocator);

    AllocatedSpacePtr = nullptr;
    AllocatedSpaceSize = NULL;

    Defragmentator = nullptr;
    field_20 = NULL;
    field_21 = NULL;
}

Allocator::~Allocator()
{
    MESSAGE_CLASS_DESTROYED(Allocator);
}

void* Allocator::Allocate(size_t size, const char* const fileName, const unsigned int fileLineNumber)
{
    return Allocate_A(size, fileName, fileLineNumber);
}

void Allocator::CallMethodAtOffset20()
{
    stub9();
}

void Allocator::SetField21(char a1)
{
    field_21 = a1;
}

void Allocator::SetNameAndAllocatedSpaceParams(void* bufferptr, const char* const name, int size)
{
    AllocatedSpacePtr = bufferptr;
    AllocatedSpaceSize = size;
    AllocatorName = name;
}

void* Allocator::GetAllocatedSpacePtr() const
{
    return AllocatedSpacePtr;
}

const int Allocator::GetAllocatedSpaceSize() const
{
    return AllocatedSpaceSize;
}

const int Allocator::GetFreeMemory() const
{
    return NULL;
}

const int Allocator::GetAllocatedElementsTotal() const
{
    return NULL;
}

const char* const Allocator::GetAllocatorName() const
{
    return "Unknown";
}

void Allocator::SetProfilerEnabled(bool enabled)
{
    ProfilerEnabled = enabled;
}

const int Allocator::GetUsedBlocksTotal() const
{
    return -1;
}

const int Allocator::GetFreeBlocksTotal() const
{
    return -1;
}

const int Allocator::GetBiggestUsedMemoryBlock() const
{
    return -1;
}

const int Allocator::GetAvailableMemory() const
{
    return -1;
}

void Allocator::Dump() const
{
    return;
}

int Allocator::PlacementNew(uint32_t* ptr, const uint32_t size, const char* const fileName, const unsigned int fileLineNumber)
{
    return NULL;
}

int Allocator::PlacementNewAligned(uint32_t* ptr, const uint32_t size, const char* const fileName, const unsigned int fileLineNumber, int alignment)
{
    return NULL;
}

int* Allocator::GetMemoryContents() const
{
    return nullptr;
}

const int Allocator::stub27() const
{
    return NULL;
}

uint32_t* Allocator::GetNextDataPtr(int*) const
{
    return NULL;
}

const int Allocator::stub29(int*) const
{
    return NULL;
}

char Allocator::OwnsPointer(int*) const
{
    return NULL;
}

char Allocator::CanExpandData(uint32_t* ptr, const uint32_t size, const uint32_t alignment) const
{
    return NULL;
}

uint32_t* Allocator::GetObjectDataPtr(void* ptr) const
{
    return NULL;
}

uint32_t* Allocator::GetHeaderDataPtr(void* ptr) const
{
    return NULL;
}

char Allocator::TryExpandBy(uint8_t* ptr, uint32_t size)
{
    return NULL;
}

int Allocator::GetMemoryReserved()
{
    return NULL;
}

void Allocator::stub36()
{
    return;
}
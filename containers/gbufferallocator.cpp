#include "gbufferallocator.h"

using namespace gcf;

gBufferAllocator::gBufferAllocator()
{

}
gBufferAllocator::~gBufferAllocator()
{

}
void *gBufferAllocator::allocate() const
{
    return 0;
}
void *gBufferAllocator::allocate(const void *cpy) const
{
    GDUNUSED(cpy);
    return 0;
}
void gBufferAllocator::deallocate(void *ptr)
{
    GDUNUSED(ptr);
}

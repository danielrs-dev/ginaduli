#ifndef GBUFFERALLOCATOR_H
#define GBUFFERALLOCATOR_H
#include "base/gcommon.h"

namespace gcf
{
class SHARED_GCF gBufferAllocator
{
public:
    gBufferAllocator();
    virtual ~gBufferAllocator();

    virtual void *allocate() const;
    virtual void *allocate(const void *cpy) const;
    virtual void deallocate(void *ptr);
};
}
#endif // GBUFFERALLOCATOR_H

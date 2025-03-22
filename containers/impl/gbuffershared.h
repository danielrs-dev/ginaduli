#ifndef GBUFFERSHARED_H
#define GBUFFERSHARED_H
#include "base/gsharedobject.h"
#include "containers/gbufferallocator.h"
#define GBUFFER_DEFINC 15
namespace gcf
{
class gBufferShared: public gSharedObject
{
public:
    gBufferShared();
    ~gBufferShared();

    virtual void copy(const gSharedObject *other);

    guptr dataVal(gu32 index) const;
    void *data(gu32 index) const;
    bool alloc(gu32 nsize);
    bool resize(gu32 nsize);
    void append(void *ptr);
    void setValue(void *ptr, gu32 index, bool removeold);
    void setUsed(gu32 nsize);
    void remove(gu32 index);
    void fastRemove(gu32 index);
    bool contains(const void *ptr, gu32 *idx) const;
    void remove(void *ptr);
    void fastRemove(void *ptr);
    void clear();
    void setAllocator(gBufferAllocator *all);
    gBufferAllocator *allocator() const;
    gu32 size() const;
    gu32 capacity() const;



public:
    guptr *m_data;
    gu32 m_size;
    gu32 m_capacity;
    gBufferAllocator *m_allocator;
    bool m_owndata;
};
}

#endif // GBUFFERSHARED_H

#include "gbuffershared.h"
#include <cstdlib>
using namespace gcf;

gBufferShared::gBufferShared():
    m_data(0),
    m_size(0),
    m_capacity(0),
    m_allocator(0)
{

}
gBufferShared::~gBufferShared()
{
    clear();
}

bool gBufferShared::alloc(gu32 nsize)
{
    gu32 i;
    clear();
    m_data = (guptr *)malloc(nsize * sizeof(guptr));

    for(i = 0; i < nsize; i++)
    {
        m_data[i] = 0;
    }
    m_capacity = nsize;
    return m_data != 0;

}
bool gBufferShared::resize(gu32 nsize)
{
    gu32 i;
    if(!m_data)
    {
        return alloc(nsize);
    }
    if((nsize < m_size) && m_allocator)
    {
        for(i = nsize; i < m_size; i++)
        {
            m_allocator->deallocate(data(i));
        }
    }
    m_capacity = nsize;
    m_data = (guptr *)realloc(m_data, m_capacity * sizeof(guptr));

    if(m_data)
    {
        for(i = m_size; i < m_capacity; i++)
        {
            m_data[i] = 0;
        }
    }

    return (m_data != 0);
}

void gBufferShared::clear()
{
    gu32 i;
    if(!m_data)
    {
        return;
    }
    if(m_allocator)
    {
        for(i = 0; i < m_size; i++)
        {
            m_allocator->deallocate(data(i));
        }
    }
    free(m_data);
    m_capacity = 0;
    m_size = 0;
    m_data = 0;
}
guptr gBufferShared::dataVal(gu32 index) const
{
    if(!m_data)
    {
        return 0;
    }
    return m_data[index];
}
void *gBufferShared::data(gu32 index) const
{
    if(!m_data)
    {
        return 0;
    }
    return (void *)m_data[index];
}
void gBufferShared::append(void *ptr)
{
    if(m_capacity == m_size)
    {
        resize( m_capacity + GBUFFER_DEFINC);
    }
    m_data[m_size] = (guptr)ptr;
    m_size++;
}
void gBufferShared::setValue(void *ptr, gu32 index, bool removeold)
{
    if(!m_data)
    {
        return;
    }
    if(index >= m_size)
    {
        return;
    }
    if(removeold && m_allocator)
    {
        void *ptr = data(index);
        m_allocator->deallocate(ptr);
    }
    m_data[index] = (guptr)ptr;
}
void gBufferShared::setUsed(gu32 nsize)
{
    m_size = nsize;
}

void gBufferShared::remove(gu32 index)
{
    gu32 nsize;
    void *ref;
    gu32 i,j;
    if(m_size == 0)
    {
        return;
    }
    if(index >= m_size)
    {
        return;
    }
    nsize = m_size - 1;
    ref = data(index);

    for(i = index, j = index + 1; i < nsize; j++, i++)
    {
        m_data[i] = m_data[j];
    }
    if(m_allocator && ref != 0)
    {
        m_allocator->deallocate(ref);
    }
    m_size =  nsize;
}
void gBufferShared::fastRemove(gu32 index)
{
    void *ref;
    if(m_size == 0)
    {
        return;
    }
    if(index >= m_size)
    {
        return;
    }
    ref = data(index);
    m_size--;
    if(ref && m_allocator)
    {
        m_allocator->deallocate(ref);
    }
    m_data[index] = m_data[m_size];
}
bool gBufferShared::contains(const void *ptr, gu32 *idx) const
{
    gu32 i;
    const guptr val = (const guptr)ptr;

    for(i = 0; i < m_size; i++)
    {
        if(m_data[i] == val)
        {
            if(idx)
            {
                *idx = i;
            }
            return true;
        }
    }
    return false;
}
void gBufferShared::remove(void *ptr)
{
    gu32 idx;
    if(contains(ptr, &idx))
    {
        remove(idx);
    }
}
void gBufferShared::fastRemove(void *ptr)
{
    gu32 idx;
    if(contains(ptr, &idx))
    {
        fastRemove(idx);
    }
}
void gBufferShared::setAllocator(gBufferAllocator *all)
{
    m_allocator = all;
}
gBufferAllocator *gBufferShared::allocator() const
{
    return m_allocator;
}

void gBufferShared::copy(const gSharedObject *other)
{
    gu32 i;
    const gBufferShared *nother = static_cast<const gBufferShared *>(other);

    alloc(nother->m_capacity);
    m_size = nother->m_size;
    if(m_allocator)
    {
        for(i = 0; i < m_size; i++)
        {
            m_data[i] = (guptr)m_allocator->allocate(nother->data(i));
        }
    }
    else
    {
        for(i = 0; i < m_size; i++)
        {
            m_data[i] = nother->m_data[i];
        }
    }
}
gu32 gBufferShared::size() const
{
    return m_size;
}
gu32 gBufferShared::capacity() const
{
    return m_capacity;
}


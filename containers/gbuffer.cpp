#include "gbuffer.h"

using namespace gcf;

gBuffer::gBuffer()
{

}
gBuffer::gBuffer(const gBuffer &other):
    gSharedObjectModel<gBufferShared>(other)
{

}
gBuffer::~gBuffer()
{

}
bool gBuffer::alloc(gu32 nsize)
{
    if(!d)
    {
        d = new gBufferShared();
    }
    return d->alloc(nsize);
}
void gBuffer::copy(const gBuffer &other)
{
    if(other.isEmpty())
    {
        return;
    }
    if(!d)
    {
        d = new gBufferShared();
    }
    d->copy(other.d);
}
gBuffer &gBuffer::operator =(const gBuffer &other)
{
    assign(other);
    return *this;
}
void gBuffer::append(void *ptr)
{
    if(!d)
    {
        d = new gBufferShared();
    }
    d->append(ptr);
}
void gBuffer::setValue(void *ptr, gu32 index, bool removeold)
{
    if(!d)
    {
        return;
    }
    d->setValue(ptr, index, removeold);
}
void gBuffer::setUsed(gu32 nsize)
{
    if(!d)
    {
        return;
    }
    d->setUsed(nsize);
}

void *gBuffer::value(gu32 index) const
{
    if(!d)
    {
        return 0;
    }
    return d->data(index);
}
gu32 gBuffer::size() const
{
    if(!d)
    {
        return 0;
    }
    return d->size();
}
gu32 gBuffer::capacity() const
{
    if(!d)
    {
        return 0;
    }
    return d->capacity();
}
void *gBuffer::operator [] (gu32 index) const
{
    return d->data(index);
}

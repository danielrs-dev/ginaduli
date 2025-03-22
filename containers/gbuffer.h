#ifndef GBUFFER_H
#define GBUFFER_H
#include "base/gsharedobjectmodel.h"
#include "impl/gbuffershared.h"

namespace gcf
{
class SHARED_GCF gBuffer: public gSharedObjectModel<gBufferShared>
{
public:
    gBuffer();
    gBuffer(const gBuffer &other);
    ~gBuffer();
    bool alloc(gu32 nsize);
    void copy(const gBuffer &other);

    gBuffer &operator = (const gBuffer &other);

    void append(void *ptr);
    void setValue(void *ptr, gu32 index, bool removeold = true);
    void setUsed(gu32 nsize);
    void *value(gu32 index) const;
    gu32 size() const;
    gu32 capacity() const;

    void *operator [] (gu32 index) const;



};
}
#endif // GBUFFER_H

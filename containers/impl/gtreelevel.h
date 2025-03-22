#ifndef GTREELEVEL_H
#define GTREELEVEL_H
/*****************************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File gtreelevel.h
        Description: Implementation of the template class gTreeLevel.
******************************************************************************/
#include <gstring/gstring.h>

namespace gcf
{
class gTreeLevel
{
public:
    gTreeLevel():
        m_ilevel(-1),
        m_ilevelid(-1)
    {

    }
    gTreeLevel(gs32 nlevel):
        m_ilevel(nlevel)
    {

    }

    ~gTreeLevel()
    {

    }
    void setLevel(gs32 nlevel)
    {
        m_ilevel = nlevel;
    }
    void setLevelID(gs32 nlevelID)
    {
        m_ilevelid = nlevelID;
    }
    void setLevelID(const gString &sid){
        m_slevelid = sid;
    }
    gs32 level() const
    {
        return m_ilevel;
    }
    gs32 levelID() const
    {
        return m_ilevelid;
    }
    const gString &stringLevelID() const
    {
        return m_slevelid;
    }

protected:
    gs32 m_ilevel;
    gs32 m_ilevelid;
    gString m_slevelid;
};
}
#endif // GTREELEVEL_H

#ifndef _XZ_ANIGROUP_HEADFILE
#define _XZ_ANIGROUP_HEADFILE

#include "XzAnimation.h"


template<class T1,class T2>
class XzGroup : XzObject
{
    std::map<T1, T2> m_mapTexture;
    std::map<T1, T2>::iterator m_iter;
    std::map<T1, T2>::iterator m_iterEnd;
public:
    XzGroup();
    ~XzGroup();

    VOID Insert(T1 key, T2 date);
    VOID Find(T1 Key);
};

#endif
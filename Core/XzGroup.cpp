#include "XzUnit.h"
//#include <cstdarg>//参数个数不确定

XzGroup::XzGroup()
: m_bArray(FALSE)
, m_cType(TEXTURE)
{
}
XzGroup::~XzGroup()
{
    for (m_iter = m_mapTexture.begin(); m_iter != m_iterEnd; ++m_iter)
    {
        delete m_iter->second;
        m_iter->second = NULL;
    }
}
VOID XzGroup::Draw(LPD3DXSPRITE& sprite)
{
    if (m_cType != GROUP&&m_bArray)
    {
        for (m_iter = m_mapTexture.begin(); m_iter != m_iterEnd; ++m_iter)
        {
            if (m_iter->second)
                m_iter->second->Draw(sprite);
        }
    }
    else
    {
        if (m_iter != m_iterEnd && m_iter->second)
            m_iter->second->Draw(sprite);
    }
}
VOID XzGroup::SetPos(D3DXVECTOR2& point, BOOL setAll)
{
    if (setAll)
    {
        m_iter = m_mapTexture.begin();
        for (; m_iter != m_iterEnd; ++m_iter)
        {
            if (m_iter->second)
                (m_iter->second)->SetPos(point, setAll);
        }
    }
    else
    {
        if (m_iter != m_iterEnd && m_iter->second)
            (m_iter->second)->SetPos(point);
    }
}
VOID XzGroup::SetDepth(FLOAT depth, BOOL setAll)
{
    if (setAll)
    {
        m_iter = m_mapTexture.begin();
        for (; m_iter != m_iterEnd; ++m_iter)
        {
            if (m_iter->second)
                (m_iter->second)->SetDepth(depth, setAll);
        }
    }
    else
    {
        if (m_iter != m_iterEnd && m_iter->second)
            (m_iter->second)->SetDepth(depth);
    }
}
VOID XzGroup::SetAnchorPoint(D3DXVECTOR2& point, BOOL setAll)
{
    if (setAll)
    {
        m_iter = m_mapTexture.begin();
        for (; m_iter != m_iterEnd; ++m_iter)
        {
            if (m_iter->second)
                (m_iter->second)->SetAnchorPoint(point, setAll);
        }
    }
    else
    {
        if (m_iter != m_iterEnd && m_iter->second)
            (m_iter->second)->SetAnchorPoint(point);
    }
}
VOID XzGroup::SetBeginFrame()
{
    if (m_iter != m_iterEnd && m_iter->second)
        (m_iter->second)->SetBeginFrame();
}
VOID XzGroup::SelectPlayAnimation(INT type, INT type2, INT type3)
{
    if (type == -1){ return; }
    if (type == -2)
    {
        m_iter->second->SelectPlayAnimation(type2, type3);
        return;
    }
    switch (m_cType)
    {
    case TEXTURE:
        if (m_bArray){ return; }
        m_iter = m_mapTexture.find(type);
        if (m_iter == m_mapTexture.end()){ return; }
        if (!(m_iter->second)){ return; }
        break;
    case ANIMATION:
        if (m_bArray){ return; }
        m_iter = m_mapTexture.find(type);
        if (m_iter == m_mapTexture.end()){ return; }
        if (!(m_iter->second)){ return; }
        m_iter->second->SetBeginFrame();
        m_iter->second->SetPlay(TRUE);
        break;
    case GROUP:
        m_iter = m_mapTexture.find(type);
        if (m_iter == m_mapTexture.end()){ return; }
        if (!(m_iter->second)){ return; }
        m_iter->second->SelectPlayAnimation(type2, type3);
        break;
    default:
        break;
    }
}
VOID XzGroup::SetPlayFrequency(INT number, XzNode* node, FUNCTION function)
{
    m_iter = m_mapTexture.begin();
    m_iterEnd = m_mapTexture.end();
    for (;m_iter != m_iterEnd; ++m_iter)
    {
        (m_iter->second)->SetPlayFrequency(number, node, function);
    }
}
VOID XzGroup::SetFPS(DWORD FPS, BOOL setAll)
{
    (m_iter->second)->SetFPS(FPS);
}
VOID XzGroup::Insert(INT type, XzUnit* unit)
{
    m_mapTexture.insert(std::make_pair(type, unit));
    m_iter = m_mapTexture.begin();
    m_iterEnd = m_mapTexture.end();
}
VOID XzGroup::SetIsArray(BOOL boolean)
{
    m_bArray = boolean;
}
VOID XzGroup::ArrayTexture(UINT type, INT offsetH, INT offsetV)
{

}
XzGroup* XzGroup::Create(INT type)
{
    XzGroup* m_tmp = new XzGroup;
    m_tmp->m_cType = type;
    switch (type)
    {
    case TEXTURE:
        m_tmp->SetIsArray(TRUE);
        break;
    case GROUP:
    case ANIMATION:
        m_tmp->SetIsArray(FALSE);
        break;
    default:
        break;
    }
    return m_tmp;
}
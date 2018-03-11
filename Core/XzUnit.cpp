#include "XzUnit.h"

XzUnit::XzUnit()
: m_vc3Pos(0, 0, 0)
, m_vc3AnchorPoint(0, 0, 0)
{
}
XzUnit::~XzUnit(){}
VOID XzUnit::Draw(LPD3DXSPRITE & sprite){}
VOID XzUnit::SetPos(D3DXVECTOR2& point, BOOL setAll)
{
    m_vc3Pos.x = point.x;
    m_vc3Pos.y = point.y;
}
VOID XzUnit::SetDepth(FLOAT depth, BOOL setAll)
{
    m_vc3Pos.z = depth;
}
VOID XzUnit::SetAnchorPoint(D3DXVECTOR2& point, BOOL setAll)
{
    m_vc3AnchorPoint.x = point.x;
    m_vc3AnchorPoint.y = point.y;
}
VOID XzUnit::SetBeginFrame(){}
VOID XzUnit::SelectPlayAnimation(INT type, INT type2, INT type3){}
VOID XzUnit::SetPlayFrequency(INT number, XzNode* node, FUNCTION function){}
VOID XzUnit::SetFPS(DWORD FPS, BOOL setAll){}
VOID XzUnit::SetPlay(BOOL boolean){}
VOID XzUnit::SetIsArray(BOOL boolean){}
VOID XzUnit::ArrayTexture(UINT type, INT offsetH, INT offsetV){}
VOID XzUnit::Insert(INT type, XzUnit* unit){}
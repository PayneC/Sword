#include "XzEditSprite.h"

#include "..\core\XzPhysicBody.h"

XzEditSprite::XzEditSprite()
	:m_bIsEdit(FALSE)
	,m_fOffset(0,0)
	,m_nowCursorPos_x(0)
	,m_nowCursorPos_y(0)
	,m_pCursor(NULL)
	,m_pFont(NULL)
{

}

XzEditSprite::~XzEditSprite()
{

}

XzEditSprite* XzEditSprite::Create()
{
	XzEditSprite* m_tmp = new XzEditSprite;
	m_tmp->AutoRelease();
	return m_tmp;
}
VOID XzEditSprite::AddFont(XzFont* font)
{
	m_pFont = font;
	m_pFont->AddUser();
}
VOID XzEditSprite::EraseUser()
{
	XzNode::EraseUser();
	if (m_iUser == 0)
	{
		if (m_pPhysicBody)
			m_pPhysicBody->EraseUser();
		if (m_pCursor)
			m_pCursor->EraseUser();
		if (m_pFont)
			m_pFont->EraseUser();
	}
}
VOID XzEditSprite::Render()
{
	if (m_pSprite)
	{
		m_pFont->Draw(m_pSprite);
	}
}

XzFont* XzEditSprite::GetFont()
{
	return m_pFont;
}
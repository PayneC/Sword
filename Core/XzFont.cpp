#include "XzFont.h"

XzFont::XzFont()
	:m_pFont(NULL)
	,m_text(L"/0")
	,m_vc2EndedPos(0,0)
	,m_color(0)
	,m_LFontWidth(0)
	,m_LFontHeight(0)
{
	m_rtRect.left = 0;
	m_rtRect.right = 0;
	m_rtRect.top = 0;
	m_rtRect.bottom = 0;
}
XzFont::~XzFont()
{
	if(m_pFont)
		m_pFont->Release();
	m_pFont = NULL;
}

VOID XzFont::Draw(LPD3DXSPRITE & sprite)
{
	if (sprite&&m_pFont)
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		m_pFont->DrawText(sprite, m_text.c_str(), -1, &m_rtRect, DT_CALCRECT, m_color);
		//FLOAT _height = (INT)m_rtRect.right/(INT)(m_rtRect.right-m_rtRect.left)*m_rtRect.bottom;
		//FLOAT _width = (INT)m_rtRect.right % ((INT)(m_rtRect.right-m_rtRect.left));
		//m_vc2EndedPos.x = (FLOAT)(m_LFontWidth + m_rtRect.left);
		//m_vc2EndedPos.y = _height + m_rtRect.top;
		m_pFont->DrawText(sprite, m_text.c_str(), -1, &m_rtRect, DT_NOCLIP | DT_WORDBREAK, 0xff00ff00);
		sprite->End();
	}
}

VOID XzFont::InsertText(WCHAR text,INT pos)
{
	std::wstring::iterator m_iterStr;
	m_iterStr = m_text.begin();
	m_iterStr += pos;
	m_text.insert(m_iterStr,text);
}
VOID XzFont::InsertText(WCHAR text)
{
	m_text.push_back(text);
}

VOID XzFont::SetText(std::wstring text)
{
	m_text = text;
}
INT XzFont::GetClickingPos(LONG x, LONG y)
{
	return (INT)(m_vc2EndedPos.x - m_LFontWidth);

}
INT XzFont::GetClickingPos(LPARAM lParam)
{
	return GetClickingPos(LOWORD(lParam),HIWORD(lParam));
}

XzFont* XzFont::Create()
{
	XzFont* m_tmp = new XzFont;
	m_tmp->AutoRelease();
	D3DXCreateFont(XzSystem::SysProfile->m_pd3dDevice,
		0, 0, 0, 0,
		FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, L"свт╡", &m_tmp->m_pFont);

	return m_tmp;
}
XzFont* XzFont::Create(std::wstring text)
{
	XzFont* m_tmp = new XzFont;
	m_tmp->AutoRelease();
	D3DXCreateFont(XzSystem::SysProfile->m_pd3dDevice,
		0, 0, 0, 0,
		FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, L"свт╡", &m_tmp->m_pFont);
	m_tmp->m_text = text;
	return m_tmp;
}
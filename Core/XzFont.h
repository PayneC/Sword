#ifndef _XZ_FONT_HEADFILE
#define _XZ_FONT_HEADFILE

#include "XzObject.h"

class XzFont : public XzObject
{
	LPD3DXFONT		m_pFont;
	std::wstring	m_text;
	RECT			m_rtRect;
	D3DXVECTOR2		m_vc2EndedPos;
	COLORREF		m_color;
	UINT			m_LFontWidth;
	INT				m_LFontHeight;

public:
	XzFont();
	~XzFont();

	virtual VOID Draw(LPD3DXSPRITE & sprite);
	VOID InsertText(WCHAR text,INT pos);
	VOID InsertText(WCHAR text);
	INT GetClickingPos(LONG x, LONG y);
	INT GetClickingPos(LPARAM lParam);
	VOID SetText(std::wstring text);

	static XzFont* Create();
	static XzFont* Create(std::wstring text);
};
#endif
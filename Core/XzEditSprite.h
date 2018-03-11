#ifndef _XZ_EDITSPRITE_HEADFILE
#define _XZ_EDITSPRITE_HEADFILE

#include "XzSprite.h"

class XzEditSprite : public XzSprite
{
private:
    BOOL			m_bIsEdit;				//是否支持输入
	D3DXVECTOR2		m_fOffset;				//内容偏移
    INT				m_nowCursorPos_x;		//当前光标位置X
    INT				m_nowCursorPos_y;		//当前光标位置Y
    XzTexture*		m_pCursor;				//光标图片	
	XzFont*			m_pFont;				//文字指针
	
public:
	XzEditSprite();
	~XzEditSprite();

	virtual VOID EraseUser();
	static XzEditSprite* Create();
	VOID AddFont(XzFont* font);
	VOID Render();
	XzFont* GetFont();
};


#endif
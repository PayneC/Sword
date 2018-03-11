#ifndef _XZ_EDITSPRITE_HEADFILE
#define _XZ_EDITSPRITE_HEADFILE

#include "XzSprite.h"

class XzEditSprite : public XzSprite
{
private:
    BOOL			m_bIsEdit;				//�Ƿ�֧������
	D3DXVECTOR2		m_fOffset;				//����ƫ��
    INT				m_nowCursorPos_x;		//��ǰ���λ��X
    INT				m_nowCursorPos_y;		//��ǰ���λ��Y
    XzTexture*		m_pCursor;				//���ͼƬ	
	XzFont*			m_pFont;				//����ָ��
	
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
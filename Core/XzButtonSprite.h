#ifndef _XZ_BUTTONSPRITE_HEADFILE
#define _XZ_BUTTONSPRITE_HEADFILE

#include "XzSprite.h"

class XzButtonSprite : public XzSprite
{
protected:
	BOOL			m_bIsFixed;			// 是否固定
	XzObject* 		m_pSendToObject;	// 发送消息
	UINT			m_iState;
	WPARAM			m_uiId;
	LPARAM			m_lParam;
	std::map<UINT,XzTexture*> m_mapObject;
	std::map<UINT,XzTexture*>::iterator m_iterObject;
	std::map<UINT,XzTexture*>::iterator m_endObject;
public:
	XzButtonSprite();
	~XzButtonSprite();

	virtual short OnLButtonDown(LPARAM lParam);
	virtual short OnLButtonUp(LPARAM lParam);
	virtual short OnMouseMove(LPARAM lParam);

	VOID SetIsFixed(BOOL boolean);
	VOID SetMessage(LPARAM lParam);
	VOID SetMessageSendObject(XzObject* object);
	VOID SetID(WPARAM id);

	UINT GetButtonState();

	static XzButtonSprite* Create();
	static XzButtonSprite* Create(XzTexture* one,XzTexture* two = NULL,XzTexture* three = NULL);
	static XzButtonSprite* CreateFromXML(std::string file);
	static XzButtonSprite* CreateFromXML(TiXmlElement * ele,XzNode * node);
	
	virtual VOID EraseUser();

	virtual VOID AddTexture(XzTexture* texture, UINT tag);
};
#endif  
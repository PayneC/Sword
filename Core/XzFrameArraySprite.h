#ifndef _XZ_FRAMEARRAYSPRITE_HEADFILE
#define _XZ_FRAMEARRAYSPRITE_HEADFILE

#include "XzSprite.h"

class XzFrameArraySprite : public XzSprite
{
protected:
	BOOL			m_bAllRender;

	std::map<UINT,XzTexture*> m_mapObject;
	std::map<UINT,XzTexture*>::iterator m_iterObject;
	std::map<UINT,XzTexture*>::iterator m_endObject;
public:
	XzFrameArraySprite();
	~XzFrameArraySprite();

	virtual VOID Render();
	virtual VOID AddTexture(XzTexture* texture, UINT tag);
    VOID SetTexture(XzTexture* texture);
	VOID SetAllRender(BOOL boolean);
	VOID SetCurrentTexture(UINT tag);

	static XzFrameArraySprite* Create();
	static XzFrameArraySprite* CreateFromXML(std::string file);
	static XzFrameArraySprite* CreateFromXML(TiXmlElement * ele,XzNode * node);
	
	virtual VOID EraseUser();
};

#endif
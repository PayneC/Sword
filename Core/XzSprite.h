#ifndef _XZ_SPRITE_HEADFILE
#define _XZ_SPRITE_HEADFILE

#include "XzNode.h"
#include "XzAnimation.h"
#include "XzFont.h"
class XzPhysicBody;

class XzSprite : public XzNode
{
protected:
	BOOL        m_bIsAutoDepth;			//是否使用自动深度
	LPD3DXSPRITE	m_pSprite;
	XzTexture*	    m_pTexture;
	XzPhysicBody*	m_pPhysicBody;

public:
	XzSprite();
	~XzSprite();

	VOID AutoCalculateDepth(FLOAT sizeY);
	VOID SetAutoCalculateDepth();

	virtual VOID Update();
	virtual VOID Render();
	virtual VOID AddChild(XzNode* node,UINT tag = 0);
	virtual VOID AddTexture(XzTexture* texture, UINT tag = 0);
	
	VOID AddPhysicBody(XzPhysicBody* body);
	virtual VOID ProcCollision(XzPhysicBody* body,char type);
	
	static XzSprite* Create();
	static XzSprite* CreateFromXML(std::string file);
	static XzSprite* CreateFromXML(TiXmlElement * ele,XzNode * node);

	RECT GetRect();
	BOOL InRect(LONG x , LONG y);
	BOOL InRectX(LONG x , LONG y);
	BOOL InRectY(LONG x , LONG y);
	XzPhysicBody* GetBody();
	virtual VOID EraseUser();
	virtual VOID SetIsVisible(BOOL boolean);

	BOOL InCamera();
	friend XzPhysicBody;
};

#endif
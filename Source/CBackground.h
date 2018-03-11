#ifndef _BACKGROUND_HEADFILE
#define _BACKGROUND_HEADFILE

#include "CXzEngine.h"

class CBackround : public XzLayer
{
public:
	static CBackround* Create();

private:
	XzSprite* m_pClod;
	XzSprite* m_pClod2;
public:
	CBackround();
	~CBackround();

	VOID Update();
};

#endif
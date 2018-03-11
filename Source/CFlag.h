#ifndef _CFLAG_HEADFILE
#define _CFLAG_HEADFILE

#include "CXzEngine.h"

class CFlag : public XzFrameArraySprite
{
	INT m_pBlood;
	INT m_pBloodCurrent;
public:
	CFlag();
	~CFlag();
	static CFlag* Create();
	VOID Update();
	VOID ProcCollision(XzPhysicBody* body,char type);
};
#endif
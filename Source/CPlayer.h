#ifndef _PLAYER_FILEHEAD
#define _PLAYER_FILEHEAD

#include "CRole.h"

class CPlayer : public  CRole
{
private:
	XzSprite* m_pHand;				//手的部分
	XzSprite* m_pSword;				//剑的部分

	BOOL m_bSKill;
	BOOL m_bSkill2;
public:
	CPlayer();
	~CPlayer();

	static CPlayer* Create();
	virtual VOID CollisionProc(XzPhysicBody* body1,XzPhysicBody* body,char type);
    VOID LoadAnimation();
    VOID StatusManage();
	VOID ProcCollision(XzPhysicBody* body,char type);
	virtual VOID Update();

	virtual VOID Revive();
};

#endif
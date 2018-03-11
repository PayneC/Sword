#ifndef _MONSTER_FILEHEAD
#define _MONSTER_FILEHEAD

#include "CXzEngine.h"
#include "CRole.h"
class CPlayer;

class CMonster : public  CRole
{
private:
	static CPlayer* m_pPlayer;
public:
	static VOID SetPlayer(CPlayer* player);

private:
	XzSprite* m_pFire;
	INT m_iSKillTime;
	BOOL m_bFollow;
	FLOAT m_fSkillDIST;
public:
	CMonster();
	~CMonster();

	static CMonster* Create();
	static CMonster* CreateFromXML(TiXmlElement * ele,XzNode * node);

	virtual VOID CollisionProc(XzPhysicBody* body1,XzPhysicBody* body,char type);
	virtual VOID ProcCollision(XzPhysicBody* body,char type);

	VOID LoadAnimation();
	virtual VOID Update();

	VOID OnBorder();
	VOID Walk();
	VOID Skill();
	VOID Injury();
};

#endif
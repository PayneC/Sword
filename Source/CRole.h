#ifndef _ROLE_FILEHEAD
#define _ROLE_FILEHEAD

#include "CXzEngine.h"

class CRole : public  XzFrameArraySprite
{
protected:
	XzPhysicBody* m_pBody;			//身体的body
	FLOAT m_fLeft;					//左边界
	FLOAT m_fRight;					//右边界
	INT m_iBlood;					//总血量
	INT m_iBloodCurrent;			//当前血量

	enum State
	{
		DEATH = 0,	//死亡
		STAND = 1,	//站立
		WALK = 2,	//行走
		SKILL = 3,	//攻击
		BORDER = 4, //处于边界
		INJURY = 5, //受伤

		OCCUPIED = 0xffffffff //占位
	} m_state;
	
	BOOL m_bOnGround;				//是否在地面
	FLOAT m_fSpeed;					//行走速度
	CRole();
public:
	~CRole();

	VOID Init();
	VOID Update();
	virtual VOID Revive();
	VOID SetWalkBorder(FLOAT l , FLOAT r);
	VOID SetSpeed(FLOAT speed);
	FLOAT GetBlood();
};

#endif
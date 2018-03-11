#ifndef _ROLE_FILEHEAD
#define _ROLE_FILEHEAD

#include "CXzEngine.h"

class CRole : public  XzFrameArraySprite
{
protected:
	XzPhysicBody* m_pBody;			//�����body
	FLOAT m_fLeft;					//��߽�
	FLOAT m_fRight;					//�ұ߽�
	INT m_iBlood;					//��Ѫ��
	INT m_iBloodCurrent;			//��ǰѪ��

	enum State
	{
		DEATH = 0,	//����
		STAND = 1,	//վ��
		WALK = 2,	//����
		SKILL = 3,	//����
		BORDER = 4, //���ڱ߽�
		INJURY = 5, //����

		OCCUPIED = 0xffffffff //ռλ
	} m_state;
	
	BOOL m_bOnGround;				//�Ƿ��ڵ���
	FLOAT m_fSpeed;					//�����ٶ�
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
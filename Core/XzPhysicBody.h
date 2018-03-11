#ifndef	_XZ_PHYSICBODY_HEADFILE 
#define _XZ_PHYSICBODY_HEADFILE

#include "XzSprite.h"
class XzPhysicWorld;

class XzPhysicBody : public XzObject
{
private:
	int m_id;
	LONG m_Id;
	LONG m_CollisionId;
	XzPhysicWorld* m_pWorld;	// ��������������
	XzSprite*	m_pUserDate;	// �û�����
	UINT		m_uiType;		// ����
	FLOAT		m_dQuality;		// ���� = 0ʱ �ǹ̶�����
	D3DXVECTOR2	m_vc2Force;		// ����
	D3DXVECTOR2 m_vc2Speed;		// �ٶ�
	BOOL        m_bIsRigidbody;	// �Ƿ�Ϊ����
	BOOL		m_bIsPermitPass;// �Ƿ�����Խ
	BOOL		m_bDoSleep;
	XzObject*	m_pObject;

	std::list<XzPhysicBody*> m_listNewCollisionBody;
	std::list<XzPhysicBody*> m_listNowCollisionBody;
	std::list<XzPhysicBody*> m_listEndCollisionBody;

public:
	XzPhysicBody();
	~XzPhysicBody();
	static XzPhysicBody* Create();
	
	VOID SetIsRigidbody(BOOL boolean);
	VOID SetSleep(BOOL boolean);

	VOID SetQuality(FLOAT quality);
	VOID SetSpeed(D3DXVECTOR2& speed);
	VOID SetSpeedX(FLOAT speedx);
	VOID SetSpeedY(FLOAT speedy);
	VOID SetSpeedAdd(D3DXVECTOR2& speed);
	D3DXVECTOR2 GetSpeed();
	VOID SetForce(D3DXVECTOR2& force);
	VOID SetForceX(FLOAT forceX);
	VOID SetForceY(FLOAT forceY);
	VOID SetForceAdd(D3DXVECTOR2& force);
	D3DXVECTOR2 GetForce();
	VOID SetMomentumAdd(D3DXVECTOR2& moment);
	VOID Update(FLOAT dt);
	VOID AddCollisionBody(XzPhysicBody* body);

	VOID SetParent(XzObject* parent);

	VOID SetID(int id);
	int GetID();
	VOID AddListenID(int id);
	VOID AddListenID(XzPhysicBody* body);

	VOID ProcNewCollision(FLOAT dt);
	VOID ProcNowCollision(FLOAT dt);
	VOID ProcEndCollision(FLOAT dt);

	VOID ProcCollision(FLOAT dt);
	VOID FeedbackParent(FLOAT dt);
	
	VOID ClearBody();

	XzSprite* GetUser();
	virtual VOID EraseUser();
	friend class XzPhysicWorld;
};

#endif


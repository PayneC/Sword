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
	XzPhysicWorld* m_pWorld;	// 所属的物理世界
	XzSprite*	m_pUserDate;	// 用户数据
	UINT		m_uiType;		// 类型
	FLOAT		m_dQuality;		// 质量 = 0时 是固定物体
	D3DXVECTOR2	m_vc2Force;		// 受力
	D3DXVECTOR2 m_vc2Speed;		// 速度
	BOOL        m_bIsRigidbody;	// 是否为刚体
	BOOL		m_bIsPermitPass;// 是否允许穿越
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


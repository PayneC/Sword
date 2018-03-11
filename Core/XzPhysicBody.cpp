#include "XzPhysicBody.h"
#include "XzPhysicWorld.h"


XzPhysicBody::XzPhysicBody()
	:m_pUserDate(NULL)
	,m_uiType(0)
	,m_vc2Force(0,0)
	,m_dQuality(1)
	,m_vc2Speed(0,0)
	,m_bIsRigidbody(FALSE)
	,m_id(0)
	,m_Id(0)
	,m_CollisionId(0)
	,m_bDoSleep(FALSE)
{

}
XzPhysicBody::~XzPhysicBody()
{

}
XzPhysicBody* XzPhysicBody::Create()
{
	XzPhysicBody* m_tmp = new XzPhysicBody();
	m_tmp->m_uiType = 0;
	return m_tmp;
}
VOID XzPhysicBody::SetSleep(BOOL boolean)
{
	m_bDoSleep = boolean;
//	ClearBody();
}
VOID XzPhysicBody::SetIsRigidbody(BOOL boolean)
{
	m_bIsRigidbody = boolean;
}
VOID XzPhysicBody::SetQuality(FLOAT quality)
{
	m_dQuality = quality;
}
VOID XzPhysicBody::SetSpeed(D3DXVECTOR2& speed)
{
	m_vc2Speed = speed;
}
VOID XzPhysicBody::SetSpeedX(FLOAT speedx)
{
	m_vc2Speed.x = speedx;
}
VOID XzPhysicBody::SetSpeedY(FLOAT speedy)
{
	m_vc2Speed.y = speedy;
}
VOID XzPhysicBody::SetSpeedAdd(D3DXVECTOR2& speed)
{
	m_vc2Speed += speed;
}
D3DXVECTOR2 XzPhysicBody::GetSpeed()
{
	return m_vc2Speed;
}
VOID XzPhysicBody::SetForce(D3DXVECTOR2& force)
{
	m_vc2Force = force;
}
VOID XzPhysicBody::SetForceX(FLOAT forceX)
{
	m_vc2Force.x = forceX;
}
VOID XzPhysicBody::SetForceY(FLOAT forceY)
{
	m_vc2Force.y = forceY;
}
VOID XzPhysicBody::SetForceAdd(D3DXVECTOR2& force)
{
	m_vc2Force += force;
}
D3DXVECTOR2 XzPhysicBody::GetForce()
{
	return m_vc2Force;
}
VOID XzPhysicBody::SetMomentumAdd(D3DXVECTOR2& moment)
{
	if (m_dQuality>=0)
	{
		//D3DXVec2Dot(&m_vc2SpeedDir,&moment);
	}
}

VOID XzPhysicBody::ProcNewCollision(FLOAT dt)
{
	std::list<XzPhysicBody*>::iterator m_iterNew;
	for (m_iterNew = m_listNewCollisionBody.begin();m_iterNew != m_listNewCollisionBody.end();++m_iterNew)
	{
		if (m_bIsRigidbody)
		{
			if ((*m_iterNew)->m_bIsRigidbody&&((!m_bIsPermitPass)||(!(*m_iterNew)->m_bIsPermitPass)))
			{
				/* 物理处理 */
				


			}
		}
		if (m_pUserDate)
		{
			m_pUserDate->ProcCollision(*m_iterNew,0);
		}
	}
}
VOID XzPhysicBody::ProcNowCollision(FLOAT dt)
{
	std::list<XzPhysicBody*>::iterator m_iterNow;
	for (m_iterNow = m_listNowCollisionBody.begin();m_iterNow != m_listNowCollisionBody.end();++m_iterNow)
	{
		if (m_bIsRigidbody)
		{
			if ((*m_iterNow)->m_bIsRigidbody&&((!m_bIsPermitPass)||(!(*m_iterNow)->m_bIsPermitPass)))
			{
				/* 物理处理 */



			}
		}
		if (m_pUserDate)
		{
			m_pUserDate->ProcCollision(*m_iterNow,1);
		}
	}
}
VOID XzPhysicBody::ProcEndCollision(FLOAT dt)
{
	std::list<XzPhysicBody*>::iterator m_iterEnd;
	for (m_iterEnd = m_listEndCollisionBody.begin();m_iterEnd != m_listEndCollisionBody.end();++m_iterEnd)
	{
		if (m_bIsRigidbody)
		{
			if ((*m_iterEnd)->m_bIsRigidbody&&((!m_bIsPermitPass)||(!(*m_iterEnd)->m_bIsPermitPass)))
			{
				/* 物理处理 */



			}
		}
		if (m_pUserDate)
		{
			m_pUserDate->ProcCollision(*m_iterEnd,2);
		}
	}
}
VOID XzPhysicBody::ProcCollision(FLOAT dt)
{
	ProcNewCollision(dt);
	ProcNowCollision(dt);
	ProcEndCollision(dt);
}
VOID XzPhysicBody::FeedbackParent(FLOAT dt)
{
	if (m_pUserDate)
	{
		m_pUserDate->SetMoveBy(m_vc2Speed.x * dt,m_vc2Speed.y * dt);
	}
}

VOID XzPhysicBody::Update(FLOAT dt)
{
	if (m_dQuality>0)
	{
		m_vc2Speed += (m_vc2Force / m_dQuality)*dt;
	}
	if (!m_bDoSleep)
	{
		ProcCollision(dt);
		FeedbackParent(dt);
		m_listEndCollisionBody.clear();
		m_listEndCollisionBody.insert(m_listEndCollisionBody.begin(),m_listNowCollisionBody.begin(),m_listNowCollisionBody.end());
		m_listEndCollisionBody.insert(m_listEndCollisionBody.begin(),m_listNewCollisionBody.begin(),m_listNewCollisionBody.end());
		m_listNewCollisionBody.clear();
		m_listNowCollisionBody.clear();
	}
}

VOID XzPhysicBody::AddCollisionBody(XzPhysicBody* body)
{
	std::list<XzPhysicBody*>::iterator m_iterEnd;
	BOOL m_bool = FALSE;
	for (m_iterEnd = m_listEndCollisionBody.begin();m_iterEnd != m_listEndCollisionBody.end();++m_iterEnd)
	{
		if (*m_iterEnd == body)
		{
			m_listEndCollisionBody.erase(m_iterEnd);
			m_listNowCollisionBody.push_back(body);
			m_bool = TRUE;
			break;
		}
	}
	if (!m_bool)
	{
		m_listNewCollisionBody.push_back(body);
	}
}

VOID XzPhysicBody::SetParent(XzObject* parent)
{
	m_pUserDate = (XzSprite*)parent;
}

VOID XzPhysicBody::EraseUser()
{
	XzObject::EraseUser();
	if (m_pUserDate == 0)
	{
		m_pWorld->ReSeiri();
	}
}

VOID XzPhysicBody::SetID(int id)
{
	if (id < 1 || id > 64)
	{
		m_id = 0;
		m_Id = 0;
	}
	else
	{
		m_id = id;
		m_Id = 1 << (id-1);
	}
}
int XzPhysicBody::GetID()
{
	return m_id;
}
VOID XzPhysicBody::AddListenID(int id)
{
	if (id < 1 || id > 64)
	{
		return;
	}
	else
	{
		m_CollisionId = (1 << (id-1))|m_CollisionId;
	}
}
VOID XzPhysicBody::AddListenID(XzPhysicBody* body)
{
	m_CollisionId = m_CollisionId|body->m_Id;
}

XzSprite* XzPhysicBody::GetUser()
{
	return m_pUserDate;
}

VOID XzPhysicBody::ClearBody()
{
	m_listEndCollisionBody.clear();
	m_listNewCollisionBody.clear();
	m_listNowCollisionBody.clear();
}

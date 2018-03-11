#include "XzPhysicWorld.h"

XzPhysicWorld* XzPhysicWorld::m_pSingleton = 0;

XzPhysicWorld* XzPhysicWorld::GetSingleton()
{
	if (!m_pSingleton)
	{
		static XzPhysicWorld m_singleton;
		m_pSingleton = &m_singleton;
	}
	return m_pSingleton;
}

XzPhysicWorld::XzPhysicWorld()
	:m_vc2Gravity(0,0)
	,m_bSEIRI(TRUE)
	,m_bIsUsePhysic(FALSE)
{

}
XzPhysicWorld::~XzPhysicWorld()
{

}
XzPhysicBody* XzPhysicWorld::CreatevAtivityBody(int id)
{
	XzPhysicBody* m_tmp = new XzPhysicBody;
	m_tmp->AutoRelease();
	m_tmp->SetID(id);
	m_listaAtivityBody.push_back(m_tmp);
	m_tmp->m_bIsRigidbody = FALSE;
	m_tmp->m_uiType = 0;
	m_bIsUsePhysic = TRUE;
	return m_tmp;
}
XzPhysicBody* XzPhysicWorld::CreateFixedBody(int id)
{
	XzPhysicBody* m_tmp = new XzPhysicBody;
	m_tmp->AutoRelease();
	m_tmp->SetID(id);
	m_listFixedBody.push_back(m_tmp);
	m_tmp->m_dQuality = 0;
	m_tmp->m_bIsRigidbody = TRUE;
	m_tmp->m_uiType = 0;
	return m_tmp;
}
VOID XzPhysicWorld::_ReSeiri()
{
	std::list<XzPhysicBody*>::iterator m_iterNode = m_listaAtivityBody.begin();

	while (m_iterNode != m_listaAtivityBody.end())
	{
		if ((*m_iterNode)->GetUserNumber() <= 0)
		{
			m_iterNode = m_listaAtivityBody.erase(m_iterNode);
		}
		else
		{
			++m_iterNode;
		}
	}

	m_iterNode = m_listFixedBody.begin();
	while (m_iterNode != m_listFixedBody.end())
	{
		if ((*m_iterNode)->GetUserNumber() <= 0)
		{
			m_iterNode = m_listFixedBody.erase(m_iterNode);
		}
		else
		{
			++m_iterNode;
		}
	}

	m_bSEIRI = false;

	if(m_listaAtivityBody.empty())
	{
		m_bIsUsePhysic = FALSE;
	}
}
VOID XzPhysicWorld::GetAxis(D3DXVECTOR2* OBB,D3DXVECTOR2* axis)
{
	D3DXVECTOR2 m_tmp;
	m_tmp = OBB[0] - OBB[1];
	D3DXVec2Normalize(&m_tmp,&m_tmp);
	axis[0].x = m_tmp.y;
	axis[0].y = -m_tmp.x;

	m_tmp = OBB[1] - OBB[2];
	D3DXVec2Normalize(&m_tmp,&m_tmp);
	axis[1].x = m_tmp.y;
	axis[1].y = -m_tmp.x;

	//m_tmp = OBB[1] - OBB[2];
	//D3DXVec2Normalize(&m_tmp,&m_tmp);
	//axis[2].x = m_tmp.y;
	//axis[2].y = -m_tmp.x;

	//m_tmp = OBB[3] - OBB[0];
	//D3DXVec2Normalize(&m_tmp,&m_tmp);
	//axis[3].x = m_tmp.y;
	//axis[3].y = -m_tmp.x;
}
Projection XzPhysicWorld::GetProjection(D3DXVECTOR2* OBB,D3DXVECTOR2 axis)
{
	Projection m_tmp;
	D3DXVECTOR2 m_vctmp;
	m_vctmp = OBB[0];
	m_tmp.m_fMin = D3DXVec2Dot(&m_vctmp,&axis);
	m_tmp.m_fMax = m_tmp.m_fMin;
	for (int i = 1;i < 4; ++i)
	{
		m_vctmp = OBB[i];
		FLOAT m_fTmp = D3DXVec2Dot(&m_vctmp,&axis);
		if (m_fTmp < m_tmp.m_fMin)
			m_tmp.m_fMin = m_fTmp;
		else if (m_fTmp > m_tmp.m_fMax)
			m_tmp.m_fMax = m_fTmp;
	}
	return m_tmp;
}
bool XzPhysicWorld::_CollisionSTA(D3DXVECTOR2* OBB,D3DXVECTOR2* OBB2)
{
	D3DXVECTOR2 Axis[2];
	Projection m_tmp0,m_tmp1;
	GetAxis(OBB2,Axis);
	m_tmp0 = GetProjection(OBB,Axis[0]);
	m_tmp1 = GetProjection(OBB2,Axis[0]);
	if (m_tmp0.m_fMin > m_tmp1.m_fMax||m_tmp0.m_fMax < m_tmp1.m_fMin)
		return false;

	m_tmp0 = GetProjection(OBB,Axis[1]);
	m_tmp1 = GetProjection(OBB2,Axis[1]);
	if (m_tmp0.m_fMin > m_tmp1.m_fMax||m_tmp0.m_fMax < m_tmp1.m_fMin)
		return false;

	/*m_tmp0 = GetProjection(OBB,Axis[2]);
	m_tmp1 = GetProjection(OBB2,Axis[2]);
	if (m_tmp0.m_fMin > m_tmp1.m_fMax||m_tmp0.m_fMax < m_tmp1.m_fMin)
		return false;

	m_tmp0 = GetProjection(OBB,Axis[3]);
	m_tmp1 = GetProjection(OBB2,Axis[3]);
	if (m_tmp0.m_fMin > m_tmp1.m_fMax||m_tmp0.m_fMax < m_tmp1.m_fMin)
		return false;*/

	GetAxis(OBB,Axis);
	m_tmp0 = GetProjection(OBB,Axis[0]);
	m_tmp1 = GetProjection(OBB2,Axis[0]);
	if (m_tmp0.m_fMin > m_tmp1.m_fMax||m_tmp0.m_fMax < m_tmp1.m_fMin)
		return false;

	m_tmp0 = GetProjection(OBB,Axis[1]);
	m_tmp1 = GetProjection(OBB2,Axis[1]);
	if (m_tmp0.m_fMin > m_tmp1.m_fMax||m_tmp0.m_fMax < m_tmp1.m_fMin)
		return false;

	/*m_tmp0 = GetProjection(OBB,Axis[2]);
	m_tmp1 = GetProjection(OBB2,Axis[2]);
	if (m_tmp0.m_fMin > m_tmp1.m_fMax||m_tmp0.m_fMax < m_tmp1.m_fMin)
		return false;

	m_tmp0 = GetProjection(OBB,Axis[3]);
	m_tmp1 = GetProjection(OBB2,Axis[3]);
	if (m_tmp0.m_fMin > m_tmp1.m_fMax||m_tmp0.m_fMax < m_tmp1.m_fMin)
		return false;*/

	return true;
}
bool XzPhysicWorld::_CollisionOBBAndOBB(XzPhysicBody* body1,XzPhysicBody* body2)
{
	//if (body2->m_bDoSleep)
	//{
	//	return false;
	//}
	if ((body1->m_Id&body2->m_CollisionId)||(body1->m_CollisionId&body2->m_Id))
	{
		D3DXMATRIXA16 m_mtTmp;
		FLOAT m_fTmp;
		RECT m_rtTmp1,m_rtTmp2;
		D3DXMatrixIdentity(&m_mtTmp);
		m_mtTmp = body2->m_pUserDate->GetTransforn();
		D3DXMatrixInverse(&m_mtTmp,&m_fTmp,&m_mtTmp);
		m_mtTmp = body1->m_pUserDate->GetTransforn() * m_mtTmp;
		m_rtTmp1 = body1->m_pUserDate->GetRect();
		m_rtTmp2 = body2->m_pUserDate->GetRect();

		D3DXVECTOR2 m_vc2LT((FLOAT)m_rtTmp1.left, (FLOAT)m_rtTmp1.top);
		D3DXVECTOR2 m_vc2RT((FLOAT)m_rtTmp1.right, (FLOAT)m_rtTmp1.top);
		D3DXVECTOR2 m_vc2LB((FLOAT)m_rtTmp1.left, (FLOAT)m_rtTmp1.bottom);
		D3DXVECTOR2 m_vc2RB((FLOAT)m_rtTmp1.right, (FLOAT)m_rtTmp1.bottom);

		D3DXVec2TransformCoord(&m_vc2LT,&m_vc2LT,&m_mtTmp);
		D3DXVec2TransformCoord(&m_vc2RT,&m_vc2RT,&m_mtTmp);
		D3DXVec2TransformCoord(&m_vc2LB,&m_vc2LB,&m_mtTmp);
		D3DXVec2TransformCoord(&m_vc2RB,&m_vc2RB,&m_mtTmp);

		D3DXVECTOR2 vc1[4] = {m_vc2LT,m_vc2RT,m_vc2RB,m_vc2LB};

		D3DXVECTOR2 vc2[4];
		vc2[0].x = (FLOAT)m_rtTmp2.left;	vc2[0].y = (FLOAT)m_rtTmp2.top;
		vc2[1].x = (FLOAT)m_rtTmp2.right;	vc2[1].y = (FLOAT)m_rtTmp2.top;
		vc2[2].x = (FLOAT)m_rtTmp2.right;	vc2[3].y = (FLOAT)m_rtTmp2.bottom;
		vc2[3].x = (FLOAT)m_rtTmp2.left;	vc2[2].y = (FLOAT)m_rtTmp2.bottom;

		if (_CollisionSTA(vc1,vc2))
		{
			body1->AddCollisionBody(body2);
			body2->AddCollisionBody(body1);
			return true;
		}
	}
	return false;
}
VOID XzPhysicWorld::_Collision(FLOAT dt)
{
	std::list<XzPhysicBody*>::iterator m_iterAtivityBody = m_listaAtivityBody.begin();
	std::list<XzPhysicBody*>::iterator m_endAtivityBody = m_listaAtivityBody.end();
	std::list<XzPhysicBody*>::iterator m_iterAtivityBody2;

	std::list<XzPhysicBody*>::iterator m_iterFixedBody;
	std::list<XzPhysicBody*>::iterator m_endFixedBody;

	while (m_iterAtivityBody != m_endAtivityBody)
	{
		if ((*m_iterAtivityBody)->m_bDoSleep)
		{
			++m_iterAtivityBody;
			continue;
		}
		m_iterAtivityBody2 = m_iterAtivityBody;
		if ((*m_iterAtivityBody)->m_dQuality)
		{
			(*m_iterAtivityBody)->SetSpeedAdd(m_vc2Gravity*dt);
		}
		++m_iterAtivityBody2;
		while (m_iterAtivityBody2 != m_endAtivityBody)
		{
			if (!(*m_iterAtivityBody2)->m_bDoSleep)
			{
				_CollisionOBBAndOBB(*m_iterAtivityBody,*m_iterAtivityBody2);
			}

			++m_iterAtivityBody2;
		}
		m_iterFixedBody = m_listFixedBody.begin();
		m_endFixedBody = m_listFixedBody.end();
		while(m_iterFixedBody != m_endFixedBody)
		{
			if (!(*m_iterFixedBody)->m_bDoSleep)
			{
				_CollisionOBBAndOBB(*m_iterFixedBody,*m_iterAtivityBody);
			}
			++m_iterFixedBody;
		}
		++m_iterAtivityBody;
	}
}
VOID XzPhysicWorld::ReSeiri()
{
	_ReSeiri();
	m_bSEIRI = true;
}
VOID XzPhysicWorld::Update(FLOAT dt)
{
	if(m_bIsUsePhysic)
	{
		if (m_bSEIRI)
		{
			//_ReSeiri();
		}
		_Collision(dt);
		ChildUpdate(dt);
	}
}

VOID XzPhysicWorld::SetGravity(D3DXVECTOR2 gravity)
{
	m_vc2Gravity = gravity;
}
VOID XzPhysicWorld::SetAABB(RECT* rect)
{
	m_rtWorldAABB = *rect;
}

VOID XzPhysicWorld::ChildUpdate(FLOAT dt)
{
	std::list<XzPhysicBody*>::iterator m_iterNode = m_listaAtivityBody.begin();
	std::list<XzPhysicBody*>::iterator m_endNode = m_listaAtivityBody.end();
	while (m_iterNode != m_endNode)
	{
			(*m_iterNode)->Update(dt);
			++m_iterNode;
	}

	m_iterNode = m_listFixedBody.begin();
	m_endNode = m_listFixedBody.end();
	while (m_iterNode != m_endNode)
	{
		(*m_iterNode)->Update(dt);
		++m_iterNode;
	}
}

XzPhysicBody* XzPhysicWorld::CreateFromXML(std::string file)
{
	return NULL;
}
XzPhysicBody* XzPhysicWorld::CreateFromXML(TiXmlElement * ele,XzSprite * node)
{
	if (!ele)
	{
		return NULL;
	}
	INT type = 0;
	INT id = 0;
	INT ativity = 0;
	ele->Attribute("type",&type);
	ele->Attribute("id",&id);
	ele->Attribute("ativity",&ativity);
	XzPhysicBody* m_pBody; 
	if (ativity)
	{
		m_pBody = XzPhysicWorld::GetSingleton()->CreatevAtivityBody(id);
	}
	else
	{
		m_pBody = XzPhysicWorld::GetSingleton()->CreateFixedBody(id);
	}
	if(node)
		node->AddPhysicBody(m_pBody);
	TiXmlElement* child = ele->FirstChildElement("listen");
	while(child)
	{
		child->Attribute("id",&id);
		m_pBody->AddListenID(id);
		child->NextSiblingElement("listen");
	}
	return m_pBody;
}
#include "CRole.h"

CRole::CRole()
	:m_pBody(NULL)
	,m_iBlood(10)
	,m_iBloodCurrent(10)
	,m_state(STAND)
	,m_bOnGround(FALSE)
	,m_fSpeed(1)
{

}

CRole::~CRole()
{
}

VOID CRole::Init()
{
	SetGlobalDepth(0.1f);
}

VOID CRole::Update()
{
	if(m_bOnGround)
	{
		if (m_vc3GlobalPosition.x <= m_fLeft)
		{
			SetGlobalPosX(m_fLeft);
			m_state = BORDER;
		}
		else if(m_vc3GlobalPosition.x >= m_fRight)
		{
			SetGlobalPosX(m_fRight);
			m_state = BORDER;
		}
	}
	
	XzFrameArraySprite::Update();
}

VOID CRole::Revive()
{
	m_state = STAND;
	SetIsVisible(TRUE);
	m_iBloodCurrent = m_iBlood;
}

VOID CRole::SetWalkBorder(FLOAT l , FLOAT r)
{
	m_fLeft = l;
	m_fRight = r;
}

FLOAT CRole::GetBlood()
{
	if (m_iBlood)
	{
		return (FLOAT)m_iBloodCurrent / (FLOAT)m_iBlood;
	}
	return 0.f;
}

VOID CRole::SetSpeed(FLOAT speed)
{
	m_fSpeed = speed;
}
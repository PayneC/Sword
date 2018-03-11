#include "CMonster.h"
#include "..\Core\XzAnimation.h"
#include "CPlayer.h"

CPlayer* CMonster::m_pPlayer = NULL;
VOID CMonster::SetPlayer(CPlayer* player)
{
	m_pPlayer = player;
}

CMonster::CMonster()
	:m_pFire(NULL)
	,m_iSKillTime(0)
	,m_bFollow(FALSE)
	,m_fSkillDIST(50)
{
}
CMonster::~CMonster()
{

}
CMonster* CMonster::Create()
{
	CMonster* m_tmp = new CMonster;
	m_tmp->AutoRelease();
	m_tmp->LoadAnimation();
	return m_tmp;
}

VOID CMonster::LoadAnimation()
{																
	XzAnimation* m_pAni0 = XzAnimation::Create(L"..\\Assets\\gw.png", 1, 4, 1, 2);
    AddTexture(m_pAni0,0);
	m_pAni0->SetAnchorPoint(D3DXVECTOR2(16,64));
	m_pAni0->SetFPS(4);

	m_pAni0 = XzAnimation::Create(L"..\\Assets\\gw.png", 1, 4, 3, 3);
	AddTexture(m_pAni0,1);
	m_pAni0->SetAnchorPoint(D3DXVECTOR2(16,64));
	m_pAni0 = XzAnimation::Create(L"..\\Assets\\gw.png", 1, 4, 4, 4);
	AddTexture(m_pAni0,2);

	m_pAni0->SetAnchorPoint(D3DXVECTOR2(16,64));
	SetCurrentTexture(0);
	SetGlobalDepth(0.1f);

	m_pBody = XzPhysicWorld::GetSingleton()->CreatevAtivityBody(BODY_MONSTER_BODY);
	AddPhysicBody(m_pBody);
	m_pBody->AddListenID(BODY_PLAYER_SWORD);
	m_pBody->AddListenID(BODY_GROUND);

	m_pFire = XzSprite::Create();
	AddChild(m_pFire);

	XzAnimation* m_pAniFire = XzAnimation::Create(L"..\\Assets\\skill_fire.png",1,3,1,3);
	m_pFire->AddTexture(m_pAniFire);
	m_pFire->SetLocalPos(10,-50);
	m_pFire->SetIsVisible(FALSE);

	XzPhysicBody* m_pBodyFire = XzPhysicWorld::GetSingleton()->CreatevAtivityBody(BODY_MONSTER_FIRE);
	m_pFire->AddPhysicBody(m_pBodyFire);
	m_pBodyFire->SetQuality(0.f);
	m_state = WALK;

	SetIsVisible(TRUE);
}

VOID CMonster::Update()
{
	if (m_state == DEATH)
	{
		SetIsVisible(FALSE);
		return;
	}

	if (m_iSKillTime)
	{
		SetCurrentTexture(2);
		--m_iSKillTime;
		CRole::Update();
		return;
	}

	D3DXVECTOR2 m_tmpVc2 = m_pPlayer->GetGlobalPos() - GetGlobalPos();
	m_pFire->SetIsVisible(FALSE);

	if (m_tmpVc2.y < 32.f && m_tmpVc2.y > -5.f)
	{
		if ((m_fSpeed > 0 && m_tmpVc2.x < m_fSkillDIST && m_tmpVc2.x > 0 )|| (m_fSpeed < 0 && m_tmpVc2.x > -m_fSkillDIST && m_tmpVc2.x < 0 ))
		{
			m_state = SKILL;
		}
		else
		{
			m_bFollow = TRUE;
		}
	}
	switch(m_state)
	{
	case STAND:
		break;
	case WALK:
		Walk();
		break;
	case SKILL:
		Skill();
		break;
	case BORDER:
		OnBorder();
		break;
	case INJURY:
		Injury();
		break;
	default:
		break;
	}


	CRole::Update();
}

VOID CMonster::OnBorder()
{
	m_fSpeed = -m_fSpeed;
	SetMoveBy(m_fSpeed,0.f);
	SetScaleBy(-1.f,1.f);
	m_state = WALK;
}
VOID CMonster::Walk()
{
	SetCurrentTexture(0);
	if(m_bOnGround)
		SetMoveBy(m_fSpeed,0.f);
}
VOID CMonster::Skill()
{
	SetCurrentTexture(1);
	if (m_iSKillTime == 0)
	{
		m_pFire->SetIsVisible(TRUE);
		m_pFire->SetLocalScale(2.f,2.f);
	}
		m_state = WALK;
}
VOID CMonster::Injury()
{

	m_iSKillTime = 15;
	--m_iBloodCurrent;
	if (m_iBloodCurrent <= 0)
	{
		m_state = DEATH;
		SendMessage(XzSystem::SysProfile->hWnd,MYMSG_GAME_MONSTER_DEATH,NULL,NULL);
	}
	else
	{
	m_state = WALK;
	}

}
VOID CMonster::CollisionProc(XzPhysicBody* body1,XzPhysicBody* body,char type)
{
	switch(body1->GetID())
	{
	case BODY_MONSTER_BODY:
		//ProcBodyCollision(body,type);
		break;
	}
}

VOID CMonster::ProcCollision(XzPhysicBody* body,char type)
{
	switch(body->GetID())
	{
	case  BODY_FIRE:
		m_state = DEATH;
		SetIsVisible(FALSE);
		break;
	case BODY_GROUND:
		{
			XzSprite* m_tmpSprite= body->GetUser();
			D3DXVECTOR2 m_vc2Speed = m_pBody->GetSpeed();
			D3DXVECTOR2 m_vc2Body = GetGlobalPos();
			switch(type)
			{
			case 0:
				{
					m_vc2Body.y += 1.f;
					D3DXVec2TransformCoord(&m_vc2Body,&m_vc2Body,&XzCamera::GetSingleton()->GetCameraTransform());		//仅变幻到屏幕坐标

					if (m_tmpSprite->InRect((LONG)m_vc2Body.x,(LONG)m_vc2Body.y))
					{
						m_fLeft = m_tmpSprite->GetGlobalPos().x;
						m_fRight = (m_tmpSprite->GetRect().right - m_tmpSprite->GetRect().left) * m_tmpSprite->GetLocalScaleX() + m_fLeft;
						SetWalkBorder(m_fLeft,m_fRight);
					}	
				}
				break;
			case 1:
				{																										
					if (m_vc2Speed.y <= 0)
						return;										
					m_vc2Body.y += 1.f;
					D3DXVec2TransformCoord(&m_vc2Body,&m_vc2Body,&XzCamera::GetSingleton()->GetCameraTransform());		//仅变幻到屏幕坐标

					if (m_tmpSprite->InRect((LONG)m_vc2Body.x,(LONG)m_vc2Body.y))
					{
						SetGlobalPosY(m_tmpSprite->GetGlobalPos().y);
						m_bOnGround = TRUE;
						m_pBody->SetSpeedY(0.f);
						if (m_pBody->GetForce().y > 0)
							m_pBody->SetForceY(0.f);
					}	
				}
				break;
			case 2:
				m_bOnGround = FALSE;
				break;
			default:
				break;
			}
		}
		break;
	case BODY_PLAYER_SWORD:
		switch(type)
		{
			case 0:
				m_state = INJURY;
				break;
		}
		
		break;
	default:
		break;
	}
}

CMonster* CMonster::CreateFromXML(TiXmlElement * ele,XzNode * node)
{
	if (ele)
	{
		DOUBLE x,y,speed;
		CMonster* m_tmp = CMonster::Create();
		node->AddChild(m_tmp);
		ele->Attribute("x",&x);
		ele->Attribute("y",&y);
		ele->Attribute("speed",&speed);
		m_tmp->SetGlobalPos(FLOAT(x),FLOAT(y));
		m_tmp->SetSpeed((FLOAT)speed);
		return m_tmp;
	}
	return NULL;
}
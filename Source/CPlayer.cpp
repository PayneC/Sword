#include "CPlayer.h"
#include "..\Core\XzAnimation.h"
#include "../core/XzDirector.h"


CPlayer::CPlayer()
	:m_pHand(NULL)
	,m_pSword(NULL)
	,m_bSKill(NULL)
	,m_bSkill2(FALSE)
{
}
CPlayer::~CPlayer()
{
	
}
CPlayer* CPlayer::Create()
{
	CPlayer* m_tmp = new CPlayer;
	m_tmp->AutoRelease();
	m_tmp->Init();
	m_tmp->LoadAnimation();
	return m_tmp;
}

VOID CPlayer::LoadAnimation()
{
	XzAnimation* m_tmpBody = XzAnimation::Create(L"..\\Assets\\rw.png", 1, 1, 1, 1);					//创建身体动画
	AddTexture(m_tmpBody,0);																			//加到身体
	m_tmpBody->SetAnchorPoint(D3DXVECTOR2(16.f,64.f));													//设置图片锚点

	m_pBody = XzPhysicWorld::GetSingleton()->CreatevAtivityBody(BODY_PLAYER_BODY);					//创建身体的碰撞体
	AddPhysicBody(m_pBody);																	//加到身体
	m_pBody->AddListenID(BODY_MONSTER_FIRE);															//给身体碰撞体添加监听内容 （怪物的火）
	m_pBody->AddListenID(BODY_GROUND);																//给身体碰撞体添加监听内容 （地面）
	m_pBody->AddListenID(6);

	m_pHand = XzSprite::Create();																		//创建手
	AddChild(m_pHand);																			//加到身体
	m_pHand->SetLocalPos(0,-24.f);																		//设置手的位置

	XzTexture* m_tmpHand = XzTexture::Create(L"..\\Assets\\player_shou.png");							//创建手的图片
	m_pHand->AddTexture(m_tmpHand);																		//加到手
	m_pHand->SetAnchorPoint2D(0,2.f);																	//设置手图片的锚点						

	m_pSword = XzSprite::Create();																		//创建剑
	m_pHand->AddChild(m_pSword);																			//加到手
	m_pSword->SetLocalPos(14.f,0.f);

	XzTexture* m_tmpSword = XzTexture::Create(L"..\\Assets\\jian.png");									//创建剑的图片
	m_pSword->AddTexture(m_tmpSword);																	//加到剑
	m_tmpSword->SetAnchorPoint(D3DXVECTOR2(4.f,38.f));

	XzPhysicBody* m_tmpSwordBody = XzPhysicWorld::GetSingleton()->CreatevAtivityBody(BODY_PLAYER_SWORD);//创建剑的碰撞体
	m_pSword->AddPhysicBody(m_tmpSwordBody);																//加到剑
	m_tmpSwordBody->SetSleep(TRUE);																		//设置碰撞体为休眠状态
	m_tmpSwordBody->SetQuality(0);																		//设置碰撞体质量为0 （不受重力影响）

	m_iBloodCurrent= m_iBlood = 1000;
}

VOID CPlayer::StatusManage()
{

}

VOID CPlayer::Update()
{
	if(!m_bIsVisible)
	{
		return;
	}
	if (m_iBloodCurrent <= 0)
	{
		m_state = DEATH;
		SetIsVisible(FALSE);
		XzDirector::GetSingleton()->SuspendGame();
		SendMessage(XzSystem::SysProfile->hWnd,MYMSG_GAME_PLAY_DEATH,7,NULL);
		SendMessage(XzSystem::SysProfile->hWnd,MYMSG_BUTTONUP,8,NULL);
		return;
	}
	if (m_bOnGround)
	{
		D3DXVECTOR2 m_vc2Speed = m_pBody->GetSpeed();
		if (m_vc2Speed.x < 0)
		{
			m_vc2Speed.x += 10;
			if (m_vc2Speed.x > 0)
			{
				m_vc2Speed.x = 0;
			}
			m_pBody->SetSpeed(m_vc2Speed);
		}
		else if(m_vc2Speed.x > 0)
		{
			m_vc2Speed.x -= 10;
			if (m_vc2Speed.x < 0)
			{
				m_vc2Speed.x = 0;
			}
			m_pBody->SetSpeed(m_vc2Speed);
		}
	}
	if (m_bSkill2)
	{
		m_pSword->SetLocalMoveBy(5,0);
		if (m_pSword->GetLocalPos().x > 200.f)
		{
			FLOAT x = m_pSword->GetGlobalPos().x;
			m_pSword->SetLocalPos(14.f,0.f);
			m_pSword->GetBody()->SetSleep(TRUE);
			m_pSword->SetLocalRatoteZ(0.f);
			SetGlobalPosX(x);
			m_bSkill2 = FALSE;
		}
	}
	else if(m_bSKill)
	{
		m_pHand->SetRatoteZBy(0.1f);
		if (m_pHand->GetLocalRatoteZ() >= 1.5f)
		{
			m_pHand->SetLocalRatoteZ(0.f);
			m_pSword->SetLocalScale(1.f,1.f);
			m_pSword->GetBody()->SetSleep(TRUE);
			m_bSKill = FALSE;
		}
	}
	else
	{
		if (XzSystem::SysInput->KeyDown('K'))
		{
			m_pSword->SetLocalRatoteZ(1.57f);
			m_pSword->GetBody()->SetSleep(FALSE);
			m_bSkill2 = TRUE;
		}
		else if (XzSystem::SysInput->KeyDown('J'))
		{ 
			m_pHand->SetLocalRatoteZ(-1.6f);
			m_pSword->SetLocalScale(2.f,2.f);
			m_pSword->GetBody()->SetSleep(FALSE);
			m_bSKill = TRUE;
		}
		if (XzSystem::SysInput->KeyDown('W'))
		{ 
			if (m_bOnGround)
			{
				SetMoveBy(0.f,-5.f);
				m_pBody->SetSpeedAdd(D3DXVECTOR2(0,-320));
				m_bOnGround = FALSE;
			}
		}
		else if (XzSystem::SysInput->KeyDown('S')) 
		{ 
			if (m_bOnGround)
			{
				SetMoveBy(0.f,50.f);
				m_bOnGround = FALSE;
			}
		}
		if (XzSystem::SysInput->KeyDown('A'))
		{ 
			SetLocalScale(-1.f,1.f);
			m_pBody->SetSpeedX(-150.f);
		}
		else if (XzSystem::SysInput->KeyDown('D'))
		{ 
			SetLocalScale(1.f,1.f);
			m_pBody->SetSpeedX(150.f);
		}
	}
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
	XzFrameArraySprite::Update();
}

VOID CPlayer::CollisionProc(XzPhysicBody* body1,XzPhysicBody* body,char type)
{
	switch(body1->GetID())
	{
	case BODY_PLAYER_BODY:
		ProcCollision(body,type);
		break;
	}
}

VOID CPlayer::ProcCollision(XzPhysicBody* body,char type)
{

	switch (body->GetID())
	{
	case  BODY_FIRE:
		m_state = DEATH;
		XzDirector::GetSingleton()->SuspendGame();
		SendMessage(XzSystem::SysProfile->hWnd,MYMSG_GAME_PLAY_DEATH,NULL,NULL);
		SendMessage(XzSystem::SysProfile->hWnd,MYMSG_BUTTONUP,BUTTON_PAUSE,NULL);
		SetIsVisible(FALSE);
		break;
	case BODY_GROUND:
			switch(type)
			{
			case 0:
			case 1:
				{
					XzSprite* m_tmpSprite= body->GetUser();																//传入的body的父节点
					D3DXVECTOR2 m_vc2Speed = m_pBody->GetSpeed();
					if (m_vc2Speed.y <= 0)
					{
						return;
					}
					D3DXVECTOR2 m_vc2Body = GetGlobalPos();														//得到身体位置											
					m_vc2Body.y += 1.f;
					D3DXVec2TransformCoord(&m_vc2Body,&m_vc2Body,&XzCamera::GetSingleton()->GetCameraTransform());		//仅变幻到屏幕坐标
					if (m_tmpSprite->InRect((LONG)m_vc2Body.x,(LONG)m_vc2Body.y))
					{
						m_bOnGround = TRUE;
						SetGlobalPosY(m_tmpSprite->GetGlobalPos().y);

						m_pBody->SetSpeedY(0.f);
						if (m_pBody->GetForce().y > 0)
						{
							m_pBody->SetForceY(0.f);
						}
					}	
				}
				break;
			case 2:
				m_bOnGround = FALSE;
				break;
			default:
				break;
			}
			break;
	case BODY_MONSTER_FIRE:
		--m_iBloodCurrent;
		break;
	default:
		break;
	}
}

VOID CPlayer::Revive()
{
	CRole::Revive();
	m_pBody->ClearBody();
	m_pSword->GetBody()->ClearBody();
}
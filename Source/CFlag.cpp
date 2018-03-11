#include "CFlag.h"

CFlag::CFlag()
	:m_pBlood(29)
	,m_pBloodCurrent(29)
{

}
CFlag::~CFlag()
{

}
VOID CFlag::Update()
{
	if (m_pBloodCurrent > 0)
	{
		SetCurrentTexture(m_pBloodCurrent/5);
	}
	XzFrameArraySprite::Update();
}

CFlag* CFlag::Create()
{
	CFlag* m_tmp = new CFlag;
	m_tmp->AutoRelease();
	m_tmp->SetGlobalDepth(0.1f);
	XzPhysicBody* m_pBody = XzPhysicWorld::GetSingleton()->CreateFixedBody(BODY_Flag);
	m_tmp->AddPhysicBody(m_pBody);
	m_pBody->AddListenID(BODY_PLAYER_SWORD);

	XzTexture* m_t1 = XzTexture::Create(L"..\\Assets\\start0.png");
	m_tmp->AddTexture(m_t1,5);
	m_t1 = XzTexture::Create(L"..\\Assets\\start1.png");
	m_tmp->AddTexture(m_t1,4);
	m_t1 = XzTexture::Create(L"..\\Assets\\start2.png");
	m_tmp->AddTexture(m_t1,3);
	m_t1 = XzTexture::Create(L"..\\Assets\\start3.png");
	m_tmp->AddTexture(m_t1,2);
	m_t1 = XzTexture::Create(L"..\\Assets\\start4.png");
	m_tmp->AddTexture(m_t1,1);
	m_t1 = XzTexture::Create(L"..\\Assets\\start5.png");
	m_tmp->AddTexture(m_t1,0);

	return m_tmp;
}

VOID CFlag::ProcCollision(XzPhysicBody* body,char type)
{
	switch(type)
	{
	case 0:
		--m_pBloodCurrent;
		if (m_pBloodCurrent<=0)
		{
			SendMessage(XzSystem::SysProfile->hWnd,MYMSG_GAME_PLAY_VICTORY,NULL,NULL);
			SendMessage(XzSystem::SysProfile->hWnd,MYMSG_BUTTONUP,8,NULL);
			SetIsVisible(FALSE);
			body->GetUser()->GetParent()->GetParent()->SetIsVisible(FALSE);
		}

		break;
	default:
		break;
	}
}
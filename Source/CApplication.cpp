#include "CApplication.h"
#include "..\Core\XzDirector.h"
//#include "CPlayer.h"
#include "CMonster.h"
#include "CWindow.h"
#include "CBackground.h"
#include "CGameInfoUI.h"
#include "CFlag.h"
CApplication* CApplication::m_pSingleton = 0;

CApplication* CApplication::GetSingleton()
{
	if (!m_pSingleton)
	{
		static CApplication m_singleton;
		m_pSingleton = &m_singleton;
	}
	return m_pSingleton;
}
CApplication::CApplication()
{

}
CApplication::~CApplication()
{

}
VOID CApplication::InitApplication()
{
	XzProfile::GetSingleton()->SetClearColor(0xfff0f0ff);
	FLOAT m_tmpH = (FLOAT)XzSystem::SysProfile->m_iHeight;
	FLOAT m_tmpW = (FLOAT)XzSystem::SysProfile->m_iWidth;
	XzCamera::GetSingleton()->SetAnchorPoint2D(m_tmpW/2.f ,m_tmpH/2.f);
	
	XzScene* m_pSceneLoad = CResourceManage::GetSingleton()->LoadFromXML("scene0.xml");
	XzDirector::GetSingleton()->PushScene(m_pSceneLoad);

	InitGlobalObject();
	
	XzPhysicWorld::GetSingleton()->SetGravity(D3DXVECTOR2(0,900));
	XzCamera::GetSingleton()->SetBorder(m_pSceneLoad->GetGlobalPos()-m_pSceneLoad->GetAnchorPoint2D(),m_pSceneLoad->GetSceneSize()-m_pSceneLoad->GetAnchorPoint2D());
	XzDirector::GetSingleton()->RunGame();
}

VOID CApplication::KillApplication()
{
   
}

VOID CApplication::InitGlobalObject()
{
	/*m_pPlayer = CPlayer::Create();
	m_pPlayer->SetIsVisible(FALSE);
	CMonster::SetPlayer(m_pPlayer);
	XzDirector::GetSingleton()->AddGlobalObject(m_pPlayer);*/

}

VOID CApplication::ChangeScene(LPARAM lParam)
{
	CHAR buff[32] = "";
	sprintf_s(buff,32,"scene%d.xml",lParam);

	XzScene* s2 = CResourceManage::GetSingleton()->LoadFromXML(buff);
	XzDirector::GetSingleton()->PushScene(s2);

	//m_pPlayer->SetIsVisible(TRUE);
	CFlag* m_pFlag = CFlag::Create();
	s2->AddChild(m_pFlag);

	CPlayer* m_pPlayer = CPlayer::Create();
	s2->AddChild(m_pPlayer);
	CMonster::SetPlayer(m_pPlayer);

	TiXmlDocument m_doc(buff);
	if (m_doc.LoadFile())
	{
		TiXmlElement * m_player = m_doc.FirstChildElement("player");
		DOUBLE x,y;
		DOUBLE flagx,flagy;
		m_player->Attribute("x",&x);
		m_player->Attribute("y",&y);
		m_pPlayer->SetGlobalPos((FLOAT)x,(FLOAT)y);

		m_player->Attribute("flagx",&flagx);
		m_player->Attribute("flagy",&flagy);
		m_pFlag->SetGlobalPos((FLOAT)flagx,(FLOAT)flagy);
	}
	m_pPlayer->SetWalkBorder(0.f,s2->GetSceneSize().x);

	CGameInfoUI* m_Gui = CGameInfoUI::Create();
	s2->AddChild(m_Gui);
	m_Gui->SetPlayer(m_pPlayer);

	CBackround * m_pTmpClod = CBackround::Create();
	s2->AddChild(m_pTmpClod);

	//CRole::SetBorder(s2->GetGlobalPos()-s2->GetAnchorPoint2D(),s2->GetSceneSize()-s2->GetAnchorPoint2D());
	XzCamera::GetSingleton()->SetFollowObject(m_pPlayer);
	XzCamera::GetSingleton()->SetBorder(s2->GetGlobalPos()-s2->GetAnchorPoint2D(),s2->GetSceneSize()-s2->GetAnchorPoint2D());

	XzDirector::GetSingleton()->RunGame();
}

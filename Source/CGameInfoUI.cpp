#include "CGameInfoUI.h"

CGameInfoUI::CGameInfoUI()
	:m_pBlood(NULL)
	,m_pName(NULL)
	,m_pMark(NULL)
	,m_iMark(0)
	,m_pPlayer(NULL)
{

}
CGameInfoUI::~CGameInfoUI()
{

}
VOID CGameInfoUI::SetPlayer(CPlayer* player)
{
	m_pPlayer = player;
}
VOID CGameInfoUI::Update()
{
	m_pBlood->SetGlobalScale(m_pPlayer->GetBlood(),1.f);
	XzLayer::Update();
}
CGameInfoUI* CGameInfoUI::Create()
{
	CGameInfoUI* m_tmp = new CGameInfoUI;
	m_tmp->AutoRelease();
	m_tmp->SetGlobalDepth(0.03f);
	m_tmp->SetIsUseCamera(FALSE);

	XzSprite* m_pBlood0 = XzSprite::Create();
	m_tmp->AddChild(m_pBlood0);
	m_pBlood0->SetGlobalPos(64.f,32.f);

	XzTexture* m_pTextureBlood = XzTexture::Create(L"..\\Assets\\blood_0.png");
	m_pBlood0->AddTexture(m_pTextureBlood);

	m_tmp->m_pBlood = XzSprite::Create();
	m_tmp->AddChild(m_tmp->m_pBlood);
	m_tmp->m_pBlood->SetLocalPos(67.f,35.f);

	XzTexture* m_pTextureBlood1 = XzTexture::Create(L"..\\Assets\\blood_1.png");
	m_tmp->m_pBlood->AddTexture(m_pTextureBlood1);
	
	m_tmp->m_pName = XzEditSprite::Create();
	m_tmp->AddChild(m_tmp->m_pName);
	XzFont* m_tmpFont = XzFont::Create(L"payne");
	m_tmp->m_pName->AddFont(m_tmpFont);
	m_tmp->m_pName->SetLocalPos(64.f,16.f);

	m_tmp->m_pMark = XzEditSprite::Create();
	m_tmp->AddChild(m_tmp->m_pMark);
	m_tmpFont = XzFont::Create(L"0");
	m_tmp->m_pMark->AddFont(m_tmpFont);
	m_tmp->m_pMark->SetLocalPos(128.f,16.f);

	XzMessage::GetSingleton()->RegisterMessage(MYMSG_GAME_MONSTER_DEATH,m_tmp,type_conversion(CGameInfoUI::MonsterDeath));

	return m_tmp;
}

short CGameInfoUI::MonsterDeath(WPARAM wParam, LPARAM lParam)
{
	++m_iMark;
	WCHAR buff[32]= L"";
	_swprintf_p(buff,32,L"É±¹ÖÊý£º%d",m_iMark);
	m_pMark->GetFont()->SetText(buff);
	return 0;
}
#include "CBackground.h"

CBackround* CBackround::Create()
{
	CBackround* m_tmp = new CBackround;
	m_tmp->AutoRelease();
	m_tmp->SetGlobalDepth(0.95f);
	m_tmp->SetIsUseCamera(FALSE);

	m_tmp->m_pClod = XzSprite::Create();
	m_tmp->AddChild(m_tmp->m_pClod);
	XzTexture* m_tmpTexture = XzTexture::Create(L"../assets/clod.png");
	m_tmp->m_pClod->AddTexture(m_tmpTexture);

	m_tmp->m_pClod2 = XzSprite::Create();
	m_tmp->AddChild(m_tmp->m_pClod2);
	m_tmpTexture = XzTexture::Create(L"../assets/clod1.png");
	m_tmp->m_pClod2->AddTexture(m_tmpTexture);

	return m_tmp;
}

CBackround::CBackround()
{
	
}
CBackround::~CBackround()
{

}

VOID CBackround::Update()
{
	m_pClod->SetMoveBy(1.f,0.f);
	if (m_pClod->GetGlobalPos().x > 960.f)
	{
		m_pClod->SetGlobalPosX(-512.f);
	}
	m_pClod2->SetMoveBy(2,0);
	if (m_pClod2->GetGlobalPos().x > 960.f)
	{
		m_pClod2->SetGlobalPosX(-512.f);
	}
	XzNode::Update();
}
#include "CWindow.h"


CWindow::CWindow()
	:m_pClose(NULL)
	,m_pBackground(NULL)
	,m_HotKey(0)
{

}
CWindow::~CWindow()
{

}

CWindow* CWindow::Create(std::wstring bg ,std::wstring close)
{
	CWindow* m_tmp = new CWindow;
	m_tmp->AutoRelease();
	m_tmp->SetIsUseCamera(FALSE);
	m_tmp->SetGlobalDepth(0.02f);					
	XzMessage::GetSingleton()->ListenMouse(m_tmp);

	XzTexture* m_tmpBG = NULL;
	if(bg!=L"/0")
		m_tmpBG = XzTexture::Create(bg);
	else
		m_tmpBG = XzTexture::Create(L"../assets/load_about.png");
	m_tmp->m_pBackground = XzButtonSprite::Create(m_tmpBG);
	m_tmp->AddChild(m_tmp->m_pBackground);
	m_tmp->m_pBackground->SetIsFixed(FALSE);

	if(close!=L"/0")
	{
		XzTexture* m_tmpClose = XzTexture::Create(close);
		m_tmp->m_pClose = XzButtonSprite::Create(m_tmpClose);
		m_tmp->m_pBackground->AddChild(m_tmp->m_pClose);
		m_tmp->m_pClose->SetMessageSendObject(m_tmp);
	}
	if (m_tmp->m_pClose)
	{
		FLOAT x =(FLOAT)( m_tmp->m_pBackground->GetRect().right - m_tmp->m_pClose->GetRect().right);
		m_tmp->m_pClose->SetLocalPos(x,0);
	}


	m_tmp->SetIsVisible(FALSE);
	return m_tmp;
}

CWindow* CWindow::CreateFromXML(std::string file)
{
	return NULL;
}
CWindow* CWindow::CreateFromXML(TiXmlElement * ele,XzNode * node)
{
	if (!ele)
	{
		return NULL;
	}
	DOUBLE x;
	DOUBLE y;
	INT msg;
	INT id;
	CWindow* m_pWindow = CWindow::Create(XzSystem::CU_A2U(ele->Attribute("bg")),XzSystem::CU_A2U(ele->Attribute("close")));
	if (node)
		node->AddChild(m_pWindow);

	ele->Attribute("x",&x);
	ele->Attribute("y",&y);
	ele->Attribute("msg",&msg);
	ele->Attribute("id",&id);
	m_pWindow->m_pBackground->SetGlobalPos((FLOAT)x,(FLOAT)y);
	m_pWindow->RegisterHotKey(msg,id);

	TiXmlElement* child = ele->FirstChildElement("texture");
	child = ele->FirstChildElement("texture");
	while(child)
	{
		XzTexture::CreateFromXML(child,m_pWindow->m_pBackground);
		child = child->NextSiblingElement("texture");
	}

	child = ele->FirstChildElement("animation");
	while(child)
	{
		XzAnimation::CreateFromXML(child,m_pWindow->m_pBackground);
		child = child->NextSiblingElement("animation");
	}

	child = ele->FirstChildElement("sprite");
	while(child)
	{
		XzSprite::CreateFromXML(child,m_pWindow->m_pBackground);
		child = child->NextSiblingElement("sprite");
	}

	child = ele->FirstChildElement("buttonSprite");
	while(child)
	{
		XzButtonSprite::CreateFromXML(child,m_pWindow->m_pBackground);
		child = child->NextSiblingElement("buttonSprite");
	}

	child = ele->FirstChildElement("arrSprite");
	while(child)
	{
		XzFrameArraySprite::CreateFromXML(child,m_pWindow->m_pBackground);
		child = child->NextSiblingElement("arrSprite");
	}


	return m_pWindow;
}

short CWindow::SetVisible(WPARAM wParam, LPARAM lParam)
{
	if (wParam == m_HotKey)
	{
		m_bIsVisible = !m_bIsVisible;
		return 1;
	}
	return 0;
}

VOID CWindow::RegisterHotKey(UINT msg,WPARAM key)
{
	XzMessage::GetSingleton()->RegisterMessage(msg,this,type_conversion(CWindow::SetVisible));
	m_HotKey = key;
}

short CWindow::OnButtonUp(WPARAM wParam,LPARAM lParam)
{
	SetIsVisible(FALSE);
	return 1;
}

VOID CWindow::AddGUIObject(XzNode * node,UINT tag)
{
	m_pBackground->AddChild(node,tag);
}

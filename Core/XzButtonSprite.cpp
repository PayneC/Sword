#include "XzButtonSprite.h"
#include "XzMessage.h"
#include "XzCamera.h"

#include "XzPhysicWorld.h"
#include "XzButtonSprite.h"
#include "XzFrameArraySprite.h"

XzButtonSprite::XzButtonSprite()
	:m_bIsFixed(TRUE)
	,m_pSendToObject(NULL)
	,m_iState(MYMSG_NONE)
	,m_uiId(NULL)
	,m_lParam(NULL)
{
}

XzButtonSprite::~XzButtonSprite()
{
}

short XzButtonSprite::OnLButtonDown(LPARAM lParam)
{
	short v = 0;
	v = XzNode::OnLButtonDown(lParam);
	if (v)
		return v;

	if (InRect(LOWORD(lParam),HIWORD(lParam)))
	{
		if (m_pTexture != m_mapObject[2])
		{
			m_pTexture = m_mapObject[2];
			m_pTexture->SetBeginFrame();
		}
		m_iState = MYMSG_BUTTONDOWN;
		if (m_pSendToObject)
		{
			m_pSendToObject->OnButtonDown(m_uiId,m_lParam);
		}
		else
		{
			PostMessage(XzSystem::SysProfile->hWnd,m_iState,m_uiId,m_lParam);
		}
		return 1;
	}
	return 0;
}

short XzButtonSprite::OnLButtonUp(LPARAM lParam)
{
	short v = 0;
	v = XzNode::OnLButtonUp(lParam);
	if (v)
		return v;

	if (m_iState == MYMSG_BUTTONDOWN)
	{
		if (InRect(LOWORD(lParam),HIWORD(lParam)))
		{
			if (m_pTexture != m_mapObject[1])
			{
				m_pTexture = m_mapObject[1];
				m_pTexture->SetBeginFrame();
			}
			m_iState = MYMSG_BUTTONUP;
			if (m_pSendToObject)
			{
				m_pSendToObject->OnButtonUp(m_uiId,m_lParam);
			}
			else
			{
				PostMessage(XzSystem::SysProfile->hWnd,m_iState,m_uiId,m_lParam);
			}
		}
		else
		{
			if (m_pTexture != m_mapObject[0])
			{
				m_pTexture = m_mapObject[0];
				m_pTexture->SetBeginFrame();
			}
			m_iState = MYMSG_BUTTONLEAVE;
			if (m_pSendToObject)
			{
				m_pSendToObject->OnButtonLeave(m_uiId,m_lParam);
			}
			else
			{
				PostMessage(XzSystem::SysProfile->hWnd,m_iState,m_uiId,m_lParam);
			}
		}
		m_iState = MYMSG_NONE;
		return 1;
	}
	return 0;
}
short XzButtonSprite::OnMouseMove(LPARAM lParam)
{
	short v = 0;
	v = XzNode::OnMouseMove(lParam);
	if (v)
		return v;

	if(m_iState == MYMSG_BUTTONDOWN)
	{
		if (!m_bIsFixed)
		{
			SetMoveBy(XzSystem::SysInput->m_vc2MouseMove.x,XzSystem::SysInput->m_vc2MouseMove.y);
		}
		if(m_pTexture != m_mapObject[2])
		{
			m_pTexture = m_mapObject[2];
			m_pTexture->SetBeginFrame();
		}		
		return 1;
	}
	else if (InRect(LOWORD(lParam),HIWORD(lParam)))
	{
		if (m_pTexture != m_mapObject[1])
		{	
			m_pTexture = m_mapObject[1];
			m_pTexture->SetBeginFrame();
		}
		return 1;
	}
	else
	{
		if (m_pTexture != m_mapObject[0])
		{
			m_pTexture = m_mapObject[0];
			m_pTexture->SetBeginFrame();
		}
	}
	return 0;
}
VOID XzButtonSprite::SetIsFixed(BOOL boolean)
{
	m_bIsFixed = boolean;
}
VOID XzButtonSprite::SetMessage(LPARAM lParam)
{
	m_lParam = lParam;
}
VOID XzButtonSprite::SetMessageSendObject(XzObject* object)
{
	m_pSendToObject = object;
}
VOID XzButtonSprite::SetID(WPARAM id)
{
	m_uiId = id;
}
UINT XzButtonSprite::GetButtonState()
{
	return m_iState;
}
XzButtonSprite* XzButtonSprite::Create()
{
	XzButtonSprite* m_tmp = new XzButtonSprite;
	m_tmp->AutoRelease();
	return m_tmp;
}
XzButtonSprite* XzButtonSprite::CreateFromXML(std::string file)
{
	return NULL;
}
XzButtonSprite* XzButtonSprite::CreateFromXML(TiXmlElement * ele,XzNode * node)
{
	TiXmlElement * child;
	INT tag = 0;
	INT id = 0;
	INT msg = 0;
	INT Fixed=1;
	double x = 0;
	double y = 0;
	double ratote = 0;
	double scaleX = 1;
	double scaleY = 1;
	if(ele)
	{
		ele->Attribute("x",&x);										//读取位置x
		ele->Attribute("y",&y);										//读取位置y
		ele->Attribute("scaleX",&scaleX);							//读取缩放x
		ele->Attribute("scaleY",&scaleY);							//读取缩放y
		ele->Attribute("ratote",&ratote);							//读取选择
		ele->Attribute("tag",&tag);									//读取标签
		ele->Attribute("id",&id);									//读取按钮ID
		ele->Attribute("msg",&msg);									//读取消息内容
		ele->Attribute("Fixed",&Fixed);								//是否是固定
		XzButtonSprite* m_pButtonSprite = XzButtonSprite::Create();	//创建精灵
		if(node)
			node->AddChild(m_pButtonSprite,(UINT)tag);							
		m_pButtonSprite->SetLocalPos((FLOAT)x,(FLOAT)y);
		m_pButtonSprite->SetLocalRatoteZ((FLOAT)ratote);					
		m_pButtonSprite->SetLocalScale((FLOAT)scaleX,(FLOAT)scaleY);	
		m_pButtonSprite->SetID(id);
		m_pButtonSprite->SetMessage(msg);
		m_pButtonSprite->SetIsFixed(Fixed);

		child = ele->FirstChildElement("texture");
		while(child)
		{
			XzTexture::CreateFromXML(child,m_pButtonSprite);
			child = child->NextSiblingElement("texture");
		}
		child = ele->FirstChildElement("animation");
		while(child)
		{
			XzAnimation::CreateFromXML(child,m_pButtonSprite);
			child = child->NextSiblingElement("animation");
		}

		child = ele->FirstChildElement("body");
		if(child)
			XzPhysicWorld::CreateFromXML(child,m_pButtonSprite);

		child = ele->FirstChildElement("sprite");
		while(child)
		{
			XzSprite::CreateFromXML(child,m_pButtonSprite);
			child = child->NextSiblingElement("sprite");
		}

		child = ele->FirstChildElement("buttonSprite");
		while(child)
		{
			XzButtonSprite::CreateFromXML(child,m_pButtonSprite);
			child = child->NextSiblingElement("buttonSprite");
		}

		child = ele->FirstChildElement("arrSprite");
		while(child)
		{
			XzFrameArraySprite::CreateFromXML(child,m_pButtonSprite);
			child = child->NextSiblingElement("arrSprite");
		}

		return m_pButtonSprite;
	}
	return NULL;
}
XzButtonSprite* XzButtonSprite::Create(XzTexture* one,XzTexture* two,XzTexture* three)
{
	XzButtonSprite* m_tmp = new XzButtonSprite;
	
	if (one)
	{
		one->AddUser();
		m_tmp->AutoRelease();
		m_tmp->m_mapObject.insert(std::make_pair(0, one));
	}
	else
	{
		delete m_tmp;
		return NULL;
	}
	if (two)
	{
		two->AddUser();
		m_tmp->m_mapObject.insert(std::make_pair(1, two));
	}
	else
	{
		m_tmp->m_mapObject.insert(std::make_pair(1, one));
	}
	if (three)
	{
		three->AddUser();
		m_tmp->m_mapObject.insert(std::make_pair(2, three));
	}
	else
	{
		m_tmp->m_mapObject.insert(std::make_pair(2, m_tmp->m_mapObject[1]));
	}
	if (!m_tmp->m_mapObject.empty())
	{
		m_tmp->m_pTexture = m_tmp->m_mapObject.begin()->second;
	}
	return m_tmp;
}
VOID XzButtonSprite::EraseUser()
{
	XzNode::EraseUser();
	if (m_pPhysicBody)
		m_pPhysicBody->EraseUser();
	if (m_iUser == 0)
	{
		m_endObject = m_mapObject.end();
		for (m_iterObject = m_mapObject.begin(); m_iterObject != m_endObject; ++m_iterObject)
		{
			if (m_iterObject->second)
			{
				m_iterObject->second->EraseUser();
			}
		}
	}
}

VOID XzButtonSprite::AddTexture(XzTexture* texture, UINT tag)
{
	m_iterObject = m_mapObject.find(tag);
	if (m_iterObject != m_mapObject.end())
	{
		m_iterObject->second->EraseUser();
		m_mapObject.erase(m_iterObject);
	}
	m_mapObject.insert(std::make_pair(tag, texture));
	m_pTexture = m_mapObject[0];
	texture->AddUser();
}

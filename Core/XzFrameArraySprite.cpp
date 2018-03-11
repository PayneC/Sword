#include "XzFrameArraySprite.h"


#include "XzPhysicWorld.h"
#include "XzButtonSprite.h"
#include "XzFrameArraySprite.h"

XzFrameArraySprite::XzFrameArraySprite()
	:m_bAllRender(FALSE)
{
}

XzFrameArraySprite::~XzFrameArraySprite()
{


}
VOID XzFrameArraySprite::Render()
{
	if (!m_bIsVisible){ return; }
	if (!m_pSprite){ return; }
	if (m_bAllRender)
	{
		m_endObject = m_mapObject.end();
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		for(m_iterObject = m_mapObject.begin();m_iterObject != m_endObject;++m_iterObject)
		{
			m_iterObject->second->Draw(m_pSprite,m_vc3AnchorPoint);
		}
		m_pSprite->End();
	}
	else if (m_pTexture)
    {
        m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
         m_pTexture->Draw(m_pSprite,m_vc3AnchorPoint);
        m_pSprite->End();
    }
	XzNode::Render();
}
VOID XzFrameArraySprite::SetCurrentTexture(UINT tag)
{
	m_pTexture = m_mapObject.find(tag)->second;
}
VOID XzFrameArraySprite::AddTexture(XzTexture* texture, UINT tag)
{
	m_iterObject = m_mapObject.find(tag);
	if (m_iterObject != m_mapObject.end())
	{
		m_iterObject->second->EraseUser();
	}
	m_mapObject.insert(std::make_pair(tag, texture));
	m_pTexture = m_mapObject.begin()->second;
	texture->AddUser();
}

VOID XzFrameArraySprite::SetTexture(XzTexture* texture)
{
    m_pTexture = texture;
}
VOID XzFrameArraySprite::SetAllRender(BOOL boolean)
{
	m_bAllRender = boolean;
}
XzFrameArraySprite* XzFrameArraySprite::Create()
{
	XzFrameArraySprite* m_tmp = new XzFrameArraySprite;
	m_tmp->AutoRelease();
	return m_tmp;
}
XzFrameArraySprite* XzFrameArraySprite::CreateFromXML(std::string file)
{
	return NULL;
}
XzFrameArraySprite* XzFrameArraySprite::CreateFromXML(TiXmlElement * ele,XzNode * node)
{
	TiXmlElement * child;
	XzFrameArraySprite* m_pSprite = NULL;
	double x = 0;
	double y = 0;
	double ratote = 0;
	double scaleX = 1;
	double scaleY = 1;
	INT tag = 0;
	if(ele)
	{
		ele->Attribute("x",&x);										//��ȡλ��x
		ele->Attribute("y",&y);										//��ȡλ��y
		ele->Attribute("scaleX",&scaleX);							//��ȡ����x
		ele->Attribute("scaleY",&scaleY);							//��ȡ����y
		ele->Attribute("ratote",&ratote);							//��ȡѡ��
		ele->Attribute("tag",&tag);									//��ȡ��ǩ
		XzFrameArraySprite* m_pFrameArraySprite = XzFrameArraySprite::Create();		
		if(node)
			node->AddChild(m_pSprite,(UINT)tag);							
		m_pFrameArraySprite->SetLocalPos((FLOAT)x,(FLOAT)y);
		m_pFrameArraySprite->SetLocalRatoteZ((FLOAT)ratote);					
		m_pFrameArraySprite->SetLocalScale((FLOAT)scaleX,(FLOAT)scaleY);


		child = ele->FirstChildElement("texture");
		while(child)
		{
			XzTexture::CreateFromXML(child,m_pFrameArraySprite);
			child = child->NextSiblingElement("texture");
		}
		child = ele->FirstChildElement("animation");
		while(child)
		{
			XzAnimation::CreateFromXML(child,m_pFrameArraySprite);
			child = child->NextSiblingElement("animation");
		}

		child = ele->FirstChildElement("body");
		if(child)
			XzPhysicWorld::CreateFromXML(child,m_pFrameArraySprite);

		child = ele->FirstChildElement("sprite");
		while(child)
		{
			XzSprite::CreateFromXML(child,m_pFrameArraySprite);
			child = child->NextSiblingElement("sprite");
		}

		child = ele->FirstChildElement("buttonSprite");
		while(child)
		{
			XzButtonSprite::CreateFromXML(child,m_pFrameArraySprite);
			child = child->NextSiblingElement("buttonSprite");
		}

		child = ele->FirstChildElement("arrSprite");
		while(child)
		{
			XzFrameArraySprite::CreateFromXML(child,m_pFrameArraySprite);
			child = child->NextSiblingElement("arrSprite");
		}
		return m_pFrameArraySprite;
	}
	return NULL;
}
VOID XzFrameArraySprite::EraseUser()
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
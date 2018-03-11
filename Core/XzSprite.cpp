#include "XzSprite.h"
#include "XzCamera.h"

#include "XzPhysicWorld.h"
#include "XzButtonSprite.h"
#include "XzFrameArraySprite.h"

XzSprite::XzSprite()
	:m_pSprite(NULL)
	,m_pTexture(NULL)
	,m_pPhysicBody(NULL)
	,m_bIsAutoDepth(FALSE)
{
	D3DXCreateSprite(XzSystem::SysProfile->m_pd3dDevice, &m_pSprite);
}
XzSprite::~XzSprite()
{
	if (m_pSprite)
	{
		m_pSprite->Release();
		m_pSprite = NULL;
	}
}
VOID XzSprite::AutoCalculateDepth(FLOAT sizeY)
{
	if (sizeY)
	{
		m_vc3GlobalPosition.z =0.1f + 0.8f/sizeY * m_vc3GlobalPosition.y;
		m_bIsTransform = TRUE;
	}
}
VOID XzSprite::SetAutoCalculateDepth()
{
	m_bIsAutoDepth = TRUE;
}
VOID XzSprite::Update()
{
	if(m_bIsAutoDepth)
	{
		AutoCalculateDepth(m_fSizeY);
		m_bIsAutoDepth = FALSE;
	}
	if (m_bIsTransform||(m_bIsUseCamera&&XzCamera::GetSingleton()->GetIsTransform()))
	{
		D3DXMatrixRotationZ(&m_mtRatote,m_vc3Ratote.z);
		D3DXMatrixScaling(&m_mtScale,m_vc3Scale.x,m_vc3Scale.y,1.0f);
		D3DXMatrixTranslation(&m_mtPos,m_vc3GlobalPosition.x,m_vc3GlobalPosition.y,m_vc3GlobalPosition.z);
		m_mtTransform =m_mtRatote *m_mtScale *   m_mtPos ;
		m_mtTransform = m_mtTransform * XzSystem::SysProfile->m_mtTransform;
		if (m_bIsUseCamera)
		{
			m_mtTransform = m_mtTransform * XzCamera::GetSingleton()->GetCameraTransform();
			
			//D3DXVECTOR2 m_tmpVc2(m_vc3GlobalPosition.x,m_vc3GlobalPosition.y);
			//D3DXVec2TransformCoord(&m_tmpVc2,&m_tmpVc2,&m_mtTransform);
			//if (m_tmpVc2.x < 0 || m_tmpVc2.x > XzCamera::GetSingleton()->GetCameraWidth())
			//{
			//	m_bIsRender = FALSE;
			//}
			//else if (m_tmpVc2.y < 0 || m_tmpVc2.y > XzCamera::GetSingleton()->GetCameraHeigth())
			//{
			//	m_bIsRender = FALSE;
			//}
			//else
			//{
			//	m_bIsRender = TRUE;
			//}
		}
		m_pSprite->SetTransform(&m_mtTransform);
		//m_bIsRender = TRUE;
		m_bIsTransform = FALSE; 
	}
	XzNode::Update();
}
VOID XzSprite::Render()
{
	if (!m_bIsVisible){ return; }
	if (!m_pSprite){ return; }
	if (m_pTexture&&m_bIsRender)
    {
        m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
        m_pTexture->Draw(m_pSprite,m_vc3AnchorPoint);
        m_pSprite->End();
    }
	XzNode::Render();
}
VOID XzSprite::AddChild(XzNode * node,UINT tag)
{
	XzNode::AddChild(node,tag);
	node->SetGlobalDepth(m_vc3GlobalPosition.z);
}
VOID XzSprite::AddTexture(XzTexture* texture, UINT tag)
{
	if (m_pTexture)
	{
		m_pTexture->EraseUser();
	}
	//SetAnchorPoint2D(m_pTexture->m_vc3AnchorPoint.x, m_pTexture->m_vc3AnchorPoint.y);
	m_pTexture = texture;
	texture->AddUser();
}
VOID XzSprite::AddPhysicBody(XzPhysicBody* body)
{
	if (m_pPhysicBody)
	{
		m_pPhysicBody->EraseUser();
	}
	m_pPhysicBody = body;
	body->SetParent(this);
	body->AddUser();
}
XzSprite* XzSprite::Create()
{
	XzSprite* m_tmp = new XzSprite;
	m_tmp->AutoRelease();
	return m_tmp;
}
XzSprite* XzSprite::CreateFromXML(std::string file)
{
	return NULL;
}
XzSprite* XzSprite::CreateFromXML(TiXmlElement * ele,XzNode * node)
{
	TiXmlElement * child;
	INT tag = 0;
	double x = 0;
	double y = 0;
	double scaleX = 1;
	double scaleY = 1;
	double ratote = 0;
	if(ele)
	{
		ele->Attribute("tag",&tag);									//读取标签
		ele->Attribute("x",&x);										//读取位置x
		ele->Attribute("y",&y);										//读取位置y
		ele->Attribute("ratote",&ratote);							//读取选择
		ele->Attribute("scaleX",&scaleX);							//读取缩放x
		ele->Attribute("scaleY",&scaleY);							//读取缩放y
		XzSprite* m_pSprite = XzSprite::Create();					//创建精灵
		if (node)
			node->AddChild(m_pSprite,(UINT)tag);						
		m_pSprite->SetGlobalPos((FLOAT)x,(FLOAT)y);
		m_pSprite->SetGlobalRatoteZ((FLOAT)ratote);					
		m_pSprite->SetGlobalScale((FLOAT)scaleX,(FLOAT)scaleY);		

		child = ele->FirstChildElement("texture");
		if(child)
			XzTexture::CreateFromXML(child,m_pSprite);

		child = ele->FirstChildElement("animation");
		if(child)
			XzAnimation::CreateFromXML(child,m_pSprite);
		
		child = ele->FirstChildElement("body");
		if(child)
			XzPhysicWorld::CreateFromXML(child,m_pSprite);

		child = ele->FirstChildElement("sprite");
		while(child)
		{
			XzSprite::CreateFromXML(child,m_pSprite);
			child->NextSiblingElement("sprite");
		}

		child = ele->FirstChildElement("buttonSprite");
		while(child)
		{
			XzButtonSprite::CreateFromXML(child,m_pSprite);
			child->NextSiblingElement("buttonSprite");
		}

		child = ele->FirstChildElement("arrSprite");
		while(child)
		{
			XzFrameArraySprite::CreateFromXML(child,m_pSprite);
			child->NextSiblingElement("arrSprite");
		}

		return m_pSprite;
	}
	return NULL;
}
VOID XzSprite::EraseUser()
{
	XzNode::EraseUser();
	if (m_iUser == 0)
	{
		if (m_pTexture)
			m_pTexture->EraseUser();
		if (m_pPhysicBody)
			m_pPhysicBody->EraseUser();
	}
}
RECT XzSprite::GetRect()
{
	RECT m_rtTmp;
	m_rtTmp.top = m_pTexture->m_rtRect.top - (LONG)m_pTexture->m_vc3AnchorPoint.y;
	m_rtTmp.left = m_pTexture->m_rtRect.left - (LONG)m_pTexture->m_vc3AnchorPoint.x;
	m_rtTmp.right = m_pTexture->m_rtRect.right - (LONG)m_pTexture->m_vc3AnchorPoint.x;
	m_rtTmp.bottom = m_pTexture->m_rtRect.bottom - (LONG)m_pTexture->m_vc3AnchorPoint.y;
	return m_rtTmp;
}

VOID XzSprite::ProcCollision(XzPhysicBody* body,char type)
{
	/*switch(type)
	{
	case 0:
	XzProfile::GetSingleton()->m_color = 0xfffff0ff;
	break;
	case 1:
	XzProfile::GetSingleton()->m_color = 0xfffffff0;
	break;
	case 2:
	XzProfile::GetSingleton()->m_color = 0xffffffff;
	break;
	}*/
	if (m_pParent)
	{
		m_pParent->CollisionProc(m_pPhysicBody,body,type);
	}
}

BOOL XzSprite::InRect(LONG x , LONG y)
{
	D3DXVECTOR2 m_vc2tmp((FLOAT)x,(FLOAT)y);
	D3DXMATRIXA16 m_mtInverse;
	D3DXMatrixInverse(&m_mtInverse,NULL,&m_mtTransform);
	D3DXVec2TransformCoord(&m_vc2tmp,&m_vc2tmp,&m_mtInverse);

	return m_pTexture->InRect(m_vc2tmp);
}

BOOL XzSprite::InRectX(LONG x , LONG y)
{
	D3DXVECTOR2 m_vc2tmp((FLOAT)x,(FLOAT)y);
	D3DXMATRIXA16 m_mtInverse;
	D3DXMatrixInverse(&m_mtInverse,NULL,&m_mtTransform);
	D3DXVec2TransformCoord(&m_vc2tmp,&m_vc2tmp,&m_mtInverse);

	return m_pTexture->InRectX(m_vc2tmp);
}
BOOL XzSprite::InRectY(LONG x , LONG y)
{
	D3DXVECTOR2 m_vc2tmp((FLOAT)x,(FLOAT)y);
	D3DXMATRIXA16 m_mtInverse;
	D3DXMatrixInverse(&m_mtInverse,NULL,&m_mtTransform);
	D3DXVec2TransformCoord(&m_vc2tmp,&m_vc2tmp,&m_mtInverse);

	return m_pTexture->InRectY(m_vc2tmp);
}
XzPhysicBody* XzSprite::GetBody()
{
	return m_pPhysicBody;
}
VOID XzSprite::SetIsVisible(BOOL boolean)
{
	XzNode::SetIsVisible(boolean);

	if (m_pPhysicBody)
	{
		m_pPhysicBody->SetSleep(!boolean);
	}
}

#include "XzAnimation.h"
#include "XzSystem.h"
#include "XzSprite.h"

XzAnimation::XzAnimation()
: m_fTime(0)
, m_fFramesPerSecond(100 / 3)
, m_dRate(1)
, m_bPlay(TRUE)
, m_bPause(FALSE)
, m_callback(NULL)
, m_iFrequency(-1)
, m_iCurrentFrequency(0)
{
   
}
XzAnimation::~XzAnimation()
{
	m_pTexture = NULL;
	m_iterEnd = m_vtTexture.end();
	for (m_iter = m_vtTexture.begin(); m_iter != m_iterEnd; ++m_iter)
	{
		if (*m_iter)
		{
			(*m_iter)->EraseUser();
		}
	}   
    if (m_callback)
    {
        delete m_callback;
        m_callback = NULL;
    }
}
VOID XzAnimation::Update()
{
	m_fTime += XzSystem::SysTime->m_dFrameDT;//test
    m_iterEnd = m_vtTexture.end();
	if (m_fTime >= m_fFramesPerSecond)
	{
		m_fTime = 0;
		++m_iter;
		if (m_iter == m_iterEnd)
		{
			m_iter = m_vtTexture.begin();
			if (0 < m_iFrequency)
			{
				++m_iCurrentFrequency;
				if (m_iFrequency <= m_iCurrentFrequency)
				{ 
					m_iCurrentFrequency = 0;
					m_bPlay = FALSE;
					XzCallback::Callback(m_callback,NULL,NULL); 
				}
			}
		}
        m_pTexture = (*m_iter)->m_pTexture;
        m_color = (*m_iter)->m_color;
        m_rtRect = (*m_iter)->m_rtRect;
        m_vc3AnchorPoint = (*m_iter)->m_vc3AnchorPoint;
	}
}
VOID XzAnimation::AddFrame(XzTexture* texture)
{
    
}
VOID XzAnimation::Draw(LPD3DXSPRITE& sprite,D3DXVECTOR3 pos)
{
    if (!m_bPlay)
        return;
    sprite->Draw(m_pTexture, &m_rtRect, &m_vc3AnchorPoint, &pos, m_color);
    Update();
}
VOID XzAnimation::SetPos(D3DXVECTOR2& point)
{
    m_vc3AnchorPoint.x = point.x;
    m_vc3AnchorPoint.y = point.y;
    m_iterEnd = m_vtTexture.end();
    for (m_iter = m_vtTexture.begin(); m_iter != m_iterEnd;++m_iter)
    {
        (*m_iter)->SetPos(point);
    }
}
VOID XzAnimation::SetDepth(FLOAT depth)
{
    m_vc3AnchorPoint.z = depth;
    m_iterEnd = m_vtTexture.end();
    for (m_iter = m_vtTexture.begin(); m_iter != m_iterEnd; ++m_iter)
    {
        (*m_iter)->SetDepth(depth);
    }
}
VOID XzAnimation::SetAnchorPoint(D3DXVECTOR2& point)
{
    m_vc3AnchorPoint.x = point.x;
    m_vc3AnchorPoint.y = point.y;
    m_iterEnd = m_vtTexture.end();
    for (m_iter = m_vtTexture.begin(); m_iter != m_iterEnd; ++m_iter)
    {
        (*m_iter)->SetAnchorPoint(point);
    }
	m_iter = m_vtTexture.begin();
}
VOID XzAnimation::SetBeginFrame()
{
    m_iter = m_vtTexture.begin();
	m_pTexture = (*m_iter)->m_pTexture;
	m_color = (*m_iter)->m_color;
	m_rtRect = (*m_iter)->m_rtRect;
	m_vc3AnchorPoint = (*m_iter)->m_vc3AnchorPoint;
}
VOID XzAnimation::SetPlayFrequency(INT number, XzObject* object, XzFunction function)
{
    m_iFrequency = number;
    m_callback->m_pObject = object;
    m_callback->m_pFunction = function;
}
VOID XzAnimation::SetFPS(DWORD FPS)
{
    if (FPS > 0)
    {
        m_fFramesPerSecond = 1000 / FPS;
    }
}
VOID XzAnimation::SetPlay(BOOL boolean)
{
    m_bPlay = boolean;
}
XzAnimation * XzAnimation::Create(std::wstring filePath,UINT row,UINT col,UINT frist,UINT frame)
{
	XzAnimation* m_tmp = new XzAnimation;
	m_tmp->AutoRelease();
    XzTexture* m_base = XzTexture::Create(filePath);
    XzTexture* m_pTexture;

	RECT m_rtTmp = { 0, 0, 0, 0 };
	LONG m_lWidth = m_base->GetWidth() / col;
	LONG m_lHeight = m_base->GetHeight() / row;

    UINT r1 = (frist-1) / col;
    UINT cl = (frist-1) % col;

    for (UINT r = r1; r < row; ++r)
	{
        for (UINT c = cl; c < col; ++c)
		{
            if (frist>frame)
            {
				/* delete m_base;
				m_base = NULL;*/
                m_tmp->SetBeginFrame();
                return m_tmp;
            }
			m_rtTmp.left = m_lWidth * c;
			m_rtTmp.right = m_rtTmp.left + m_lWidth;
			m_rtTmp.top = m_lHeight * r;
			m_rtTmp.bottom = m_rtTmp.top + m_lHeight;

            m_pTexture = XzTexture::Create(m_base, &m_rtTmp);
			m_pTexture->AddUser();
			m_tmp->m_vtTexture.push_back(m_pTexture);
            ++frist;
		}
	}

    m_tmp->SetBeginFrame();


	return m_tmp;
}
XzAnimation* XzAnimation::CreateFromXML(std::string file)
{
	return NULL;
}
XzAnimation* XzAnimation::CreateFromXML(TiXmlElement * ele,XzSprite * node)
{
	INT tag = 0;
	INT row = 0;
	INT col = 0;
	INT begin = 0;
	INT end = 0;
	INT frame;
	ele->Attribute("row",&row);			
	ele->Attribute("col",&col);			
	ele->Attribute("begin",&begin);
	ele->Attribute("end",&end);
	ele->Attribute("frame",&frame);
	ele->Attribute("tag",&tag);
	XzAnimation* m_pAnimation;
	if(ele)
	{
		if (row)
		{
			m_pAnimation = XzAnimation::Create(XzSystem::CU_A2U(ele->Attribute("file")),(UINT)row,(UINT)col,(UINT)begin,(UINT)end);
			if (tag < 0)
				tag = -tag;
			if(node)
				node->AddTexture(m_pAnimation,tag);
			m_pAnimation->SetFPS(frame);
		}
		TiXmlElement* child = ele->FirstChildElement("texture");
		while(child)
		{
			XzTexture* m_pTexture = XzTexture::Create(XzSystem::CU_A2U(ele->Attribute("file")));
			m_pAnimation->AddFrame(m_pTexture);
			child = child->NextSiblingElement("texture");
		}
	}
	return m_pAnimation;
}
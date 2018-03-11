#include "XzProfile.h"

XzProfile* XzProfile::m_pSingleton = NULL;
XzProfile* XzProfile::GetSingleton()
{
	if (!m_pSingleton)
	{
		static XzProfile m_singleton;
		m_pSingleton = &m_singleton;
	}
	return m_pSingleton;
}

XzProfile::XzProfile()
	:hInst(NULL)
	,hWnd(NULL)
	,m_pD3D(NULL)
	,m_pd3dDevice(NULL)
	,m_iWidth(0)
	,m_iHeight(0)
	,m_dTime(0)
	,m_dFPS(100/3)
	,m_color(0)
	,m_vc3AnchorPoint(0.f,0.f,0.f)
{
	D3DXMatrixIdentity(&m_mtTransform);
}
XzProfile::~XzProfile()
{

}
VOID XzProfile::SetClearColor(COLORREF color)
{
	m_color = color;
}
BOOL XzProfile::LoadProfile(std::string file)
{
	TiXmlDocument m_doc(file.c_str());
	TiXmlElement * m_info;
	if (m_doc.LoadFile())
	{
		if(!(m_info = m_doc.FirstChildElement("width")))
			return FALSE;
		m_info->Attribute("width",&m_iWidth);
		if(!(m_info = m_doc.FirstChildElement("height")))
			return FALSE;
		m_info->Attribute("height",&m_iHeight);

		if(m_info = m_doc.FirstChildElement("FPS"))
		{
			INT m_iFps;
			m_info->Attribute("FPS",&m_iFps);
			if (m_iFps)
			{
				m_dFPS = 1000/m_iFps;
			}
		}

		if(m_info = m_doc.FirstChildElement("anchorPoint"))
		{
			DOUBLE x=0,y=0,z=0;
			m_info->Attribute("x",&x);
			m_info->Attribute("y",&y);
			m_info->Attribute("z",&z);
			m_vc3AnchorPoint.x = (FLOAT)x;
			m_vc3AnchorPoint.y = (FLOAT)y;
			m_vc3AnchorPoint.z = (FLOAT)z;
			D3DXMatrixTranslation(&m_mtTransform,m_vc3AnchorPoint.x,m_vc3AnchorPoint.y,m_vc3AnchorPoint.z);
		}

		return TRUE;
	}
	return FALSE;
}
BOOL XzProfile::SaveProfile(std::string file)
{
	return TRUE;
}
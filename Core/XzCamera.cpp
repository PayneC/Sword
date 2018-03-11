#include "XzCamera.h"

XzCamera* XzCamera::m_pSingleton = NULL;
XzCamera* XzCamera::GetSingleton()
{
	if (!m_pSingleton)
	{
		static XzCamera m_singleton;
		m_pSingleton = &m_singleton;
	}
	return m_pSingleton;
}

XzCamera::XzCamera()
	:m_vc2Size((FLOAT)XzSystem::SysProfile->m_iWidth,(FLOAT)XzSystem::SysProfile->m_iHeight)
	,m_vc2AnchorPoint(0.f,0.f)
	,m_vc2Pos(0.f,0.f)
	,m_vc2Border_LT(0.f,0.f)
	,m_vc2Border_RB(0.f,0.f)
	,m_bIsUseBorder(FALSE)
	,m_bIsFollow(TRUE)
	,m_pFollowObject(NULL)
{
	D3DXMatrixIdentity(&m_mtCameraTrans);
	SetBorder(D3DXVECTOR2(0.f,0.f),D3DXVECTOR2((FLOAT)XzSystem::SysProfile->m_iWidth,(FLOAT)XzSystem::SysProfile->m_iHeight));
}

XzCamera::~XzCamera()
{

}
BOOL XzCamera::GetIsTransform()
{
	return m_bIstransform;
}
VOID XzCamera::SetSize(FLOAT width, FLOAT height)
{
	m_vc2Size.x = width;
	m_vc2Size.y = height;
}
VOID XzCamera::SetAnchorPoint2D(FLOAT x, FLOAT y)
{
	m_vc2AnchorPoint.x = x;
	m_vc2AnchorPoint.y = y;
}
VOID XzCamera::SetPos(D3DXVECTOR2 point)
{
	//D3DXVECTOR2 vc2tmp = point - m_vc2AnchorPoint - m_vc2Pos;
	//m_vc2Pos += (vc2tmp - m_vc2Pos)*XzSystem::SysTime->m_fDeltaTime;
	m_vc2Pos = point - m_vc2AnchorPoint;//
	if (m_bIsUseBorder)	//相机运动边界判断
	{
		if(m_vc2Pos.x < m_vc2Border_LT.x)
		{
			m_vc2Pos.x = m_vc2Border_LT.x;
		}
		else if(m_vc2Pos.x > m_vc2Border_RB.x)
		{
			m_vc2Pos.x = m_vc2Border_RB.x;
		}

		if(m_vc2Pos.y < m_vc2Border_LT.y)
		{
			m_vc2Pos.y = m_vc2Border_LT.y;
		}
		else if(m_vc2Pos.y > m_vc2Border_RB.y)
		{
			m_vc2Pos.y = m_vc2Border_RB.y;
		}
	}
}

VOID XzCamera::SetFollowObject(XzNode * node)
{
	m_pFollowObject = node;
}

VOID XzCamera::SetBorder(D3DXVECTOR2 LT,D3DXVECTOR2 RB)
{
	if (LT.x > RB.x || LT.y > RB.y)
	{
		MessageBox(NULL,L"边界设置错误",NULL,NULL);
		return;
	}
	m_vc2Border_LT = LT;
	m_vc2Border_RB = RB;
	if (RB.x - LT.x < m_vc2Size.x)
	{
		m_vc2Border_LT.x = LT.x;
		m_vc2Border_RB.x = m_vc2Size.x + LT.x;
	}
	if (RB.y - LT.y < m_vc2Size.y)
	{
		m_vc2Border_LT.y = LT.y;
		m_vc2Border_RB.y = m_vc2Size.y + LT.y;
	}
	//m_vc2Border_LT += m_vc2AnchorPoint;
	//m_vc2Border_RB -= (m_vc2Size - m_vc2AnchorPoint);
	m_vc2Border_RB -= m_vc2Size;
	m_bIsUseBorder = TRUE;
}

VOID XzCamera::UseFollow(BOOL & boolean)
{
	m_bIsUseBorder = boolean;
}

VOID XzCamera::UseBorder(BOOL & boolean)
{
	m_bIsFollow = boolean;
}

D3DXVECTOR2 XzCamera::SceneToWorld(D3DXVECTOR2& point)
{
	return point + m_vc2Pos;
}

D3DXVECTOR2 XzCamera::WorldToScene(D3DXVECTOR2& point)
{
	return point - m_vc2Pos;
}

VOID XzCamera::Update()
{
	if (!m_bIsFollow)
	{
		return;
	}
	if (m_pFollowObject)
	{
		SetPos(m_pFollowObject->GetGlobalPos());
		m_bIstransform = TRUE;
	}
	else
	{
		m_bIstransform = FALSE;
	}
}

VOID XzCamera::GetCameraTransform(D3DXMATRIXA16 * pOut, const D3DXVECTOR2 & point,const FLOAT & depth)
{
    D3DXMatrixTranslation(pOut, point.x - m_vc2Pos.x, point.y - m_vc2Pos.y, depth);
}
D3DXMATRIXA16 XzCamera::GetCameraTransform()
{
	 D3DXMatrixTranslation(&m_mtCameraTrans,-m_vc2Pos.x, -m_vc2Pos.y,0);
	 return m_mtCameraTrans;
}
FLOAT XzCamera::GetCameraWidth()
{
	return m_vc2Size.x;
}
FLOAT XzCamera::GetCameraHeigth()
{
	return m_vc2Size.y;
}
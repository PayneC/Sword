#include "XzNode.h" 

FLOAT XzNode::m_fSizeY = 0.f;

VOID XzNode::SetSizeY(FLOAT sizeY)
{
	m_fSizeY = sizeY;
}

XzNode::XzNode()
    :m_pParent(NULL)
	,m_bIsUseCamera(TRUE)
	,m_bIsTransform(TRUE)
    ,m_vc3AnchorPoint(0.f,0.f,0.f)
	,m_vc3LocalPosition(0.f,0.f,0.f)
	,m_vc3Scale(1.f,1.f,1.f)
	,m_vc3Ratote(0.f,0.f,0.f)
	,m_bIsRender(TRUE)
{
	D3DXMatrixIdentity(&m_mtPos);
	D3DXMatrixIdentity(&m_mtScale);
	D3DXMatrixIdentity(&m_mtRatote);
	D3DXMatrixIdentity(&m_mtTransform);
}
XzNode::~XzNode()
{

}
VOID XzNode::SetTransformForParent(D3DXMATRIXA16* transform)
{
	D3DXVECTOR2 m_vc2tmp;
	m_vc2tmp.x = m_vc3LocalPosition.x;
	m_vc2tmp.y = m_vc3LocalPosition.y;
	D3DXVec2TransformCoord(&m_vc2tmp,&m_vc2tmp,transform);
	SetGlobalPos(m_vc2tmp.x, m_vc2tmp.y);
	m_bIsTransform = true;
}
VOID XzNode::SetAlignForParent(XzNode* parent)
{
	SetLocalPos(m_vc3GlobalPosition.x - parent->m_vc3GlobalPosition.x,m_vc3GlobalPosition.y - parent->m_vc3GlobalPosition.y);
	//SetGlobalDepth(parent->m_vc3GlobalPosition.z);
	SetIsUseCamera(parent->m_bIsUseCamera);
}


VOID XzNode::SetMoveBy(FLOAT x, FLOAT y)
{
	SetGlobalPos(m_vc3GlobalPosition.x + x,m_vc3GlobalPosition.y +y);
}

VOID XzNode::SetLocalMoveBy(FLOAT x, FLOAT y)
{
	SetLocalPos(m_vc3LocalPosition.x + x,m_vc3LocalPosition.y +y);
}
VOID XzNode::SetRatoteZBy(FLOAT z)
{
	SetGlobalRatoteZ(m_vc3Ratote.z + z);
}
VOID XzNode::SetLocalRatoteZBy(FLOAT z)
{
	SetLocalRatoteZ(m_pParent->GetGlobalDepth() - m_vc3Ratote.z + z);
}
VOID XzNode::SetScaleBy(FLOAT x,FLOAT y)
{
	SetGlobalScale(x*m_vc3Scale.x,y*m_vc3Scale.y);
}
VOID XzNode::SetLocalPosForParent(FLOAT x, FLOAT y)
{
	SetLocalPos(m_vc3LocalPosition.x - x, m_vc3LocalPosition.y - y);
}
/*================================
函数：SetParent
作用：设置父节点
注释：null
=================================*/
VOID XzNode::SetParent(XzNode * parent)
{
	m_pParent = parent;
}
/*================================
函数：SetAnchorPoint2D
作用：设置锚点
注释：null
=================================*/
VOID XzNode::SetAnchorPoint2D(FLOAT x, FLOAT y)
{
	if(m_vc3AnchorPoint.x == x && m_vc3AnchorPoint.y == y)
	{
		return;
	}
	m_endNode = m_mmpNode.end();
	for (m_iterNode = m_mmpNode.begin();m_iterNode != m_endNode;++m_iterNode)
	{
		m_iterNode->second->SetLocalPosForParent(x - m_vc3AnchorPoint.x, y-m_vc3AnchorPoint.y);
	}
	m_vc3AnchorPoint.x = x;
	m_vc3AnchorPoint.y = y;
}
/*================================
函数：SetAnchorPoint3D
作用：设置锚点
注释：null
=================================*/
VOID XzNode::SetAnchorPoint3D(FLOAT x, FLOAT y, FLOAT z)
{
	m_vc3AnchorPoint.x = x;
	m_vc3AnchorPoint.y = y;
	m_vc3AnchorPoint.z = z;
}
/*================================
函数：SetLocalPos
作用：设置相对位置
注释：世界坐标 = 相对坐标 + 父节点世界坐标
=================================*/
VOID XzNode::SetLocalPos(FLOAT x, FLOAT y)
{
	m_vc3LocalPosition.x = x;
	m_vc3LocalPosition.y = y;
	if (m_pParent)
	{
		D3DXMatrixRotationZ(&m_pParent->m_mtRatote,m_pParent->m_vc3Ratote.z);
		D3DXMatrixScaling(&m_pParent->m_mtScale,m_pParent->m_vc3Scale.x,m_pParent->m_vc3Scale.y,m_pParent->m_vc3Scale.z);
		D3DXMatrixTranslation(&m_pParent->m_mtPos,m_pParent->m_vc3GlobalPosition.x,m_pParent->m_vc3GlobalPosition.y,m_pParent->m_vc3GlobalPosition.z);
		m_pParent->m_mtTransform = m_pParent->m_mtRatote *m_pParent->m_mtScale * m_pParent->m_mtPos;
		D3DXVECTOR2 m_vc2tmp;
		m_vc2tmp.x = m_vc3LocalPosition.x;
		m_vc2tmp.y = m_vc3LocalPosition.y;
		D3DXVec2TransformCoord(&m_vc2tmp,&m_vc2tmp,&m_pParent->m_mtTransform);
		SetGlobalPos(m_vc2tmp.x, m_vc2tmp.y);
	}
	else
	{ 
		SetGlobalPos(m_vc3LocalPosition.x,m_vc3GlobalPosition.y);
	}
}
/*================================
函数：SetGlobalPos
作用：设置世界位置
注释：null
=================================*/
VOID XzNode::SetGlobalPos(FLOAT x, FLOAT y)
{
	if (m_vc3GlobalPosition.x != x
		||m_vc3GlobalPosition.y != y)
	{	
		FLOAT m_fx = x - m_vc3GlobalPosition.x;
		FLOAT m_fy = y - m_vc3GlobalPosition.y;
		m_vc3GlobalPosition.x = x;
		m_vc3GlobalPosition.y = y; 
		m_bIsTransform = TRUE;

		D3DXMatrixRotationZ(&m_mtRatote,m_vc3Ratote.z);
		D3DXMatrixScaling(&m_mtScale,m_vc3Scale.x,m_vc3Scale.y,m_vc3Scale.z);
		D3DXMatrixTranslation(&m_mtPos,m_vc3GlobalPosition.x,m_vc3GlobalPosition.y,m_vc3GlobalPosition.z);
		m_mtTransform = m_mtRatote *m_mtScale *   m_mtPos;

		m_endNode = m_mmpNode.end();
		for (m_iterNode = m_mmpNode.begin();m_iterNode != m_endNode;++m_iterNode)
		{
			m_iterNode->second->SetMoveBy(m_fx, m_fy);
			m_iterNode->second->SetTransformForParent(&m_mtTransform);
		}
	}	
}
VOID XzNode::SetLocalPosX(FLOAT x)
{
	SetLocalPos(x,m_vc3LocalPosition.y);
}
VOID XzNode::SetLocalPosY(FLOAT y)
{
	SetLocalPos(m_vc3LocalPosition.x,y);
}
VOID XzNode::SetGlobalPosX(FLOAT x)
{
	SetGlobalPos(x,m_vc3GlobalPosition.y);
}
VOID XzNode::SetGlobalPosY(FLOAT y)
{
	SetGlobalPos(m_vc3GlobalPosition.x,y);
}
/*================================
函数：SetLocalDepth
作用：设置相对深度
注释：null
=================================*/
VOID XzNode::SetLocalDepth(FLOAT depth)
{ 
	/*if (m_pParent)
	{
		if (m_vc3GlobalPosition.z != m_pParent->m_vc3GlobalPosition.z + depth)
		{
			m_vc3GlobalPosition.z = m_pParent->m_vc3GlobalPosition.z + depth;
			if (m_vc3GlobalPosition.z < 0.f)
			{
				m_vc3GlobalPosition.z = 0.f;
			}
			else if (m_vc3GlobalPosition.z > 1.f)
			{
				m_vc3GlobalPosition.z = 1.f;
			}
			m_bIsTransform = TRUE;
		}
	}
	else
	{
		if (m_vc3GlobalPosition.z != depth)
		{
			m_vc3GlobalPosition.z = depth;
			if (m_vc3GlobalPosition.z < 0.f)
			{
				m_vc3GlobalPosition.z = 0.f;
			}
			else if (m_vc3GlobalPosition.z > 1.f)
			{
				m_vc3GlobalPosition.z = 1.f;
			}
			m_bIsTransform = TRUE;
		}
	}*/
	m_vc3GlobalPosition.z = depth;
	m_bIsTransform = TRUE;
}
/*================================
函数：SetGlobalDepth
作用：设置世界深度
注释：null
=================================*/
VOID XzNode::SetGlobalDepth(FLOAT depth)
{
	//if (m_vc3GlobalPosition.z != depth)
	//{
	//	m_vc3GlobalPosition.z = depth;
	//	if (m_vc3GlobalPosition.z < 0.f)
	//	{
	//		m_vc3GlobalPosition.z = 0.f;
	//	}
	//	else if (m_vc3GlobalPosition.z > 1.f)
	//	{
	//		m_vc3GlobalPosition.z = 1.f;
	//	}
	//	m_bIsTransform = TRUE;
	//}
	m_vc3GlobalPosition.z = depth;
	m_bIsTransform = TRUE;
}
/*================================
函数：SetLocalScale
作用：设置相对缩放
注释：世界缩放 = 相对缩放 x 父节点世界缩放
=================================*/
VOID XzNode::SetLocalScale(FLOAT x,FLOAT y)
{
	if (m_pParent)
	{
		SetGlobalScale(x*m_pParent->m_vc3Scale.x,y*m_pParent->m_vc3Scale.y);
	}
	else
	{
		SetGlobalScale(x,y);
	}
}
/*================================
函数：SetGlobalScale
作用：设置相对缩放
注释：世界缩放 = 相对缩放 x 父节点世界缩放
=================================*/
VOID XzNode::SetGlobalScale(FLOAT x,FLOAT y)
{
	if (m_vc3Scale.x != x
		||m_vc3Scale.y != y)
	{	
		FLOAT m_fTmpX,m_fTmpY;
		if (m_vc3Scale.x)
		{
			m_fTmpX = x/m_vc3Scale.x;
			m_fTmpY = y/m_vc3Scale.y;
		}
		else
		{
			m_fTmpX = 0.f;
		}
		if (m_vc3Scale.y)
		{
			m_fTmpY = y/m_vc3Scale.y;
		}
		else
		{
			m_fTmpY = 0.f;
		}
		m_vc3Scale.x = x;
		m_vc3Scale.y = y;
		m_bIsTransform = TRUE;
		D3DXMatrixRotationZ(&m_mtRatote,m_vc3Ratote.z);
		D3DXMatrixScaling(&m_mtScale,m_vc3Scale.x,m_vc3Scale.y,m_vc3Scale.z);
		D3DXMatrixTranslation(&m_mtPos,m_vc3GlobalPosition.x,m_vc3GlobalPosition.y,m_vc3GlobalPosition.z);
		m_mtTransform = m_mtRatote *m_mtScale *  m_mtPos ;
		m_endNode = m_mmpNode.end();
		for (m_iterNode = m_mmpNode.begin();m_iterNode != m_endNode;++m_iterNode)
		{
			m_iterNode->second->SetTransformForParent(&m_mtTransform);
			m_iterNode->second->SetScaleBy(m_fTmpX,m_fTmpY);
		}
	}
}
/*================================
函数：SetLocalRatoteZ
作用：设置相对选转
注释：世界旋转 = 相对旋转 + 父节点世界旋转
=================================*/
VOID XzNode::SetLocalRatoteZ(FLOAT z)
{
	if (m_pParent)
	{
		SetGlobalRatoteZ(m_pParent->m_vc3Ratote.z + z);
	}
	else
	{
		SetGlobalRatoteZ(z);
	}
}
/*================================
函数：SetGlobalScaleZ
作用：设置世界旋转
注释：世界旋转 = 相对旋转 + 父节点世界旋转
=================================*/
VOID XzNode::SetGlobalRatoteZ(FLOAT z)
{
	if (m_vc3Ratote.z != z)
	{
		FLOAT m_fTmpRz = z - m_vc3Ratote.z;
		m_vc3Ratote.z = z;
		m_bIsTransform = TRUE;
		D3DXMatrixRotationZ(&m_mtRatote,m_vc3Ratote.z);
		D3DXMatrixScaling(&m_mtScale,m_vc3Scale.x,m_vc3Scale.y,m_vc3Scale.z);
		D3DXMatrixTranslation(&m_mtPos,m_vc3GlobalPosition.x,m_vc3GlobalPosition.y,m_vc3GlobalPosition.z);
		m_mtTransform = m_mtRatote *m_mtScale *   m_mtPos;
		m_endNode = m_mmpNode.end();
		for (m_iterNode = m_mmpNode.begin();m_iterNode != m_endNode;++m_iterNode)
		{
			m_iterNode->second->SetRatoteZBy(m_fTmpRz);
			m_iterNode->second->SetTransformForParent(&m_mtTransform);

		}
	}
}
/*================================
函数：SetIsVisible
作用：设置可见
注释：null
=================================*/
VOID XzNode::SetIsVisible(BOOL boolean)
{
	m_bIsVisible = boolean;
}
/*================================
函数：SetIsUseCamera
作用：设置是否使用相机
注释：null
=================================*/
VOID XzNode::SetIsUseCamera(BOOL boolean)
{
	m_bIsUseCamera = boolean;
}
/*================================
函数：SetIsTransform
作用：设置是否更改
注释：null
=================================*/
VOID XzNode::SetIsTransform(BOOL boolean)
{
	m_bIsTransform = boolean;
}
/*===========================================
=============================================
===========================================*/
XzNode* XzNode::GetParent()
{
	return m_pParent;
}
D3DXVECTOR2 XzNode::GetAnchorPoint2D()
{
	return D3DXVECTOR2(m_vc3AnchorPoint.x,m_vc3AnchorPoint.y);
}
D3DXVECTOR3 XzNode::GetAnchorPoint3D()
{
	return m_vc3AnchorPoint;
}
D3DXVECTOR2 XzNode::GetLocalPos()
{
	//if (m_pParent)
	//{
	//	return D3DXVECTOR2(m_vc3GlobalPosition.x - m_pParent->m_vc3GlobalPosition.x, m_vc3GlobalPosition.y - m_vc3GlobalPosition.y);
	//}
	//else
	//{
	//	return D3DXVECTOR2(m_vc3GlobalPosition.x,m_vc3GlobalPosition.y);
	//}
	return D3DXVECTOR2(m_vc3LocalPosition.x,m_vc3LocalPosition.y);
}
D3DXVECTOR2 XzNode::GetGlobalPos()
{
	return D3DXVECTOR2(m_vc3GlobalPosition.x,m_vc3GlobalPosition.y);
}
FLOAT XzNode::GetLocalDepth()
{
	if (m_pParent)
	{
		return m_vc3GlobalPosition.z - m_pParent->m_vc3GlobalPosition.z;
	}
	else
	{
		return m_vc3GlobalPosition.z;
	}
}
FLOAT XzNode::GetGlobalDepth()
{
	return m_vc3GlobalPosition.z;
}
FLOAT XzNode::GetLocalScaleX()
{
	if (m_pParent)
	{
		if (m_pParent->m_vc3Scale.x == 0)
		{
			return 0;
		}
		return m_vc3Scale.x / m_pParent->m_vc3Scale.x;
	}
	else
	{
		return m_vc3Scale.x;
	}
}
FLOAT XzNode::GetGlobalScaleX()
{
	return m_vc3Scale.x;
}
FLOAT XzNode::GetLocalRatoteZ()
{	
	if (m_pParent)
	{
		return m_vc3Ratote.z - m_pParent->m_vc3Ratote.z;
	}
	else
	{
		return m_vc3Ratote.z;
	}
}
FLOAT XzNode::GetGlobalRatoteZ()
{
	return m_vc3Ratote.z;
}
BOOL XzNode::GetIsVisible()
{
	return m_bIsVisible;
}
BOOL XzNode::GetIsUseCamera()
{
	return m_bIsUseCamera;
}
BOOL XzNode::GetIsTransform()
{
	return m_bIsTransform;
}
D3DXMATRIXA16& XzNode::GetTransforn()
{
	return m_mtTransform;
}
VOID XzNode::AddChild(XzNode * node,UINT tag)
{
	if(node->GetParent())
	{
		node->GetParent()->EraseChild(node);
	}
	node->SetParent(this);
	node->SetAlignForParent(this);
	node->AddUser();
	m_mmpNode.insert(std::make_pair(tag, node));
}
VOID XzNode::EraseChild(XzNode* node)
{
	m_endNode = m_mmpNode.end();
	for (m_iterNode = m_mmpNode.begin();m_iterNode != m_endNode;++m_iterNode)
	{
		if(m_iterNode->second == node)
		{
			node->EraseUser();
			m_mmpNode.erase(m_iterNode);
			return;
		}
	}
}
VOID XzNode::Update()
{

	m_endNode = m_mmpNode.end();
	for (m_iterNode = m_mmpNode.begin();m_iterNode != m_endNode;++m_iterNode)
	{
		m_iterNode->second->Update();
	}
}
VOID XzNode::Render()
{
	if (!m_bIsVisible){return;}
	std::multimap<UINT,XzNode*>::reverse_iterator m_riterNode;
	std::multimap<UINT,XzNode*>::reverse_iterator m_rendNode;
	m_rendNode = m_mmpNode.rend();
	for (m_riterNode = m_mmpNode.rbegin();m_riterNode != m_rendNode;++m_riterNode)
	{
		m_riterNode->second->Render();
	}
}

VOID XzNode::EraseUser()
{
	XzObject::EraseUser();
	if (m_iUser == 0)
	{
		m_endNode = m_mmpNode.end();
		for (m_iterNode = m_mmpNode.begin();m_iterNode != m_endNode;++m_iterNode)
		{
			m_iterNode->second->EraseUser();
		}
	}
}

short XzNode::OnLButtonDown(LPARAM lParam)
{
	if(!m_pParent->m_bIsVisible)
	{
		return 0;
	}
	if (!m_bIsVisible)
	{
		return 0;
	}
	short v = 0;
	m_endNode = m_mmpNode.end();
	for (m_iterNode = m_mmpNode.begin();m_iterNode != m_endNode;++m_iterNode)
	{
		v = m_iterNode->second->OnLButtonDown(lParam);
		if (v)
		{
			return v;
		}
	}
	return 0;
}
short XzNode::OnLButtonUp(LPARAM lParam)
{
	if(!m_pParent->m_bIsVisible)
	{
		return 0;
	}
	if (!m_bIsVisible)
	{
		return 0;
	}
	short v = 0;
	m_endNode = m_mmpNode.end();
	for (m_iterNode = m_mmpNode.begin();m_iterNode != m_endNode;++m_iterNode)
	{
		v = m_iterNode->second->OnLButtonUp(lParam);
		if (v)
		{
			return v;
		}
	}
	return 0;
}
short XzNode::OnRButtonDown(LPARAM lParam)
{
	if(!m_pParent->m_bIsVisible)
	{
		return 0;
	}
	if (!m_bIsVisible)
	{
		return 0;
	}
	short v = 0;
	m_endNode = m_mmpNode.end();
	for (m_iterNode = m_mmpNode.begin();m_iterNode != m_endNode;++m_iterNode)
	{
		v = m_iterNode->second->OnRButtonDown(lParam);
		if (v)
		{
			return v;
		}
	}
	return 0;
}
short XzNode::OnRButtonUp(LPARAM lParam)
{
	if(!m_pParent->m_bIsVisible)
	{
		return 0;
	}
	if (!m_bIsVisible)
	{
		return 0;
	}
	short v = 0;
	m_endNode = m_mmpNode.end();
	for (m_iterNode = m_mmpNode.begin();m_iterNode != m_endNode;++m_iterNode)
	{
		v = m_iterNode->second->OnRButtonUp(lParam);
		if (v)
		{
			return v;
		}
	}
	return 0;
}
short XzNode::OnMouseMove(LPARAM lParam)
{
	if(!m_pParent->m_bIsVisible)
	{
		return 0;
	}
	if (!m_bIsVisible)
	{
		return 0;
	}
	short v = 0;
	m_endNode = m_mmpNode.end();
	for (m_iterNode = m_mmpNode.begin();m_iterNode != m_endNode;++m_iterNode)
	{
		v = m_iterNode->second->OnMouseMove(lParam);
		if (v)
		{
			return v;
		}
	}
	return 0;
}
VOID XzNode::CollisionProc(XzPhysicBody* body1,XzPhysicBody* body,char type)
{
	if (m_pParent)
	{
		m_pParent->CollisionProc(body1,body,type);
	}
}
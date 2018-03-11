#include "XzTexture.h"
#include "XzSprite.h"

XzTexture::XzTexture()
	:m_pTexture(NULL)
	,m_color(0xffffffff)
	,m_vc3AnchorPoint(0,0,0)
{
	 ZeroMemory(&m_rtRect, sizeof(m_rtRect));
}
XzTexture::~XzTexture()
{
	if (m_pTexture)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
XzTexture * XzTexture::Create(std::wstring filePath)
{
    XzTexture* m_tmp = new XzTexture;
	D3DXIMAGE_INFO m_info;
	ZeroMemory(&m_info, sizeof(m_info));
	D3DXCreateTextureFromFileEx(
		XzSystem::SysProfile->m_pd3dDevice,
		filePath.c_str(),
		D3DX_FROM_FILE,	//纹理宽度
		D3DX_FROM_FILE,	//纹理高度	
		D3DX_FROM_FILE, //纹理级别
		0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		NULL,
		&m_info,
		NULL,
		&m_tmp->m_pTexture);
	m_tmp->m_rtRect.top = 0;
	m_tmp->m_rtRect.left = 0;
	m_tmp->m_rtRect.bottom = m_info.Height;
	m_tmp->m_rtRect.right = m_info.Width;
	if (!m_tmp->m_pTexture)
	{
		delete m_tmp;
		return NULL;
	}
	m_tmp->AutoRelease();
	return m_tmp;
}
XzTexture * XzTexture::Create(std::wstring filePath, RECT *_rect)
{
	XzTexture* m_base = XzTexture::Create(filePath);
	if(!m_base)
	{
		return NULL;
	}
	XzTexture* m_tmp = Create(m_base, _rect);
    return m_tmp;
}
XzTexture * XzTexture::Create(const XzTexture* texture, RECT * rect)
{
    XzTexture* m_tmp = new XzTexture;
	D3DLOCKED_RECT pLockedRectA,pLockedRectB;

	m_tmp->m_rtRect.left = m_tmp->m_rtRect.top = 0;
	m_tmp->m_rtRect.right = rect->right - rect->left;
	m_tmp->m_rtRect.bottom = rect->bottom - rect->top;

	D3DXCreateTexture(XzSystem::SysProfile->m_pd3dDevice, m_tmp->m_rtRect.right, m_tmp->m_rtRect.bottom, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_tmp->m_pTexture);

	texture->m_pTexture->LockRect(0, &pLockedRectA, NULL, D3DLOCK_DISCARD);
	m_tmp->m_pTexture->LockRect(0, &pLockedRectB, &m_tmp->m_rtRect, D3DLOCK_DISCARD);
	int A = pLockedRectA.Pitch/4;
	int B = pLockedRectB.Pitch/4;
	int AYX = 0, BYX = 0;

	for (int iy = 0; iy < m_tmp->m_rtRect.bottom; ++iy)
	{
		BYX = iy * B;
		AYX = (iy + rect->top) * A;
		for (int ix = 0; ix < m_tmp->m_rtRect.right; ++ix)
		{
			((DWORD*)pLockedRectB.pBits)[BYX + ix] = ((DWORD*)pLockedRectA.pBits)[AYX + rect->left + ix];
		}  
	}
	m_tmp->m_pTexture->UnlockRect(0);
	texture->m_pTexture->UnlockRect(0);
	m_tmp->AutoRelease();
	return m_tmp;
}
XzTexture* XzTexture::CreateFromXML(std::string file)
{
	return NULL;
}
XzTexture* XzTexture::CreateFromXML(TiXmlElement * ele,XzSprite * node)
{
	INT tag;
	if(ele)
	{
		XzTexture* m_pTexture = XzTexture::Create(XzSystem::CU_A2U(ele->Attribute("file")));
		ele->Attribute("tag",&tag);
		if (tag < 0)
			tag = -tag;
		if(node)
			node->AddTexture(m_pTexture,(UINT)tag);
		return m_pTexture;
	}
	return NULL;
}
VOID XzTexture::Draw(LPD3DXSPRITE & _sprite,D3DXVECTOR3 pos)
{
	_sprite->Draw(m_pTexture, &m_rtRect, &m_vc3AnchorPoint, &pos, m_color);
}
VOID XzTexture::SetPos(D3DXVECTOR2& point){}
VOID XzTexture::SetDepth(FLOAT depth){}
VOID XzTexture::SetAnchorPoint(D3DXVECTOR2& point)
{
	m_vc3AnchorPoint.x = point.x;
	m_vc3AnchorPoint.y = point.y;
}
VOID XzTexture::SetBeginFrame(){}
VOID XzTexture::SetPlayFrequency(INT number, XzObject* node, XzFunction function){}
VOID XzTexture::SetFPS(DWORD FPS){}
VOID XzTexture::SetPlay(BOOL boolean){}
VOID XzTexture::Insert(INT type, XzTexture* unit){}
BOOL XzTexture::InRect(D3DXVECTOR2 & piont)
{
	if(piont.x >= (FLOAT)m_rtRect.left - m_vc3AnchorPoint.x
		&&piont.x <= (FLOAT)m_rtRect.right - m_vc3AnchorPoint.x
		&&piont.y >= (FLOAT)m_rtRect.top - m_vc3AnchorPoint.y
		&&piont.y <= (FLOAT)m_rtRect.bottom - m_vc3AnchorPoint.y)
	{
		return TRUE;
	}
	return FALSE;
}
BOOL XzTexture::InRectX(D3DXVECTOR2 & piont)
{
	if(piont.x >= m_rtRect.left - m_vc3AnchorPoint.x
		&&piont.x <= m_rtRect.right - m_vc3AnchorPoint.x)
	{
		return TRUE;
	}
	return FALSE;
}
BOOL XzTexture::InRectY(D3DXVECTOR2 & piont)
{
	if(piont.y >= m_rtRect.top - m_vc3AnchorPoint.y
		&&piont.y <= m_rtRect.bottom - m_vc3AnchorPoint.y)
	{
		return TRUE;
	}
	return FALSE;
}
LONG XzTexture::GetWidth()
{
	return m_rtRect.right - m_rtRect.left;
}
LONG XzTexture::GetHeight()
{
	return m_rtRect.bottom - m_rtRect.top;
}

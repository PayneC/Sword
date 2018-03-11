#include "RigidBody.h"

BOOL XzCollision::CollisionPixel(XzSprite * _rectangle, XzSprite * _rectangle2, RECT *_rect)
{
	RECT m_rtTmp1 = _rectangle->GetSizefromTransform();
	RECT m_rtTmp2 = _rectangle2->GetSizefromTransform();

	HITSTRUCT hsH[4] = {m_rtTmp1.left,1,
		m_rtTmp1.right,1,
		m_rtTmp2.left,2,
		m_rtTmp2.right,2};

	Sort4(hsH);
	if(hsH[0].flag == hsH[1].flag)
		return false;

	HITSTRUCT hsV[4] = {m_rtTmp1.top,1,
		m_rtTmp1.bottom,1,
		m_rtTmp2.top,2,
		m_rtTmp2.bottom,2};
	Sort4(hsV);
	if(hsV[0].flag == hsV[1].flag)
		return false;

	if (_rect)
	{
		_rect->left		= hsH[1].Value;
		_rect->right	= hsH[2].Value;
		_rect->top		= hsV[1].Value;
		_rect->bottom	= hsV[2].Value;
	}
	return TRUE;
}

void Sort4(HITSTRUCT* List)
{
	HITSTRUCT	t;
	if(List[0].Value > List[2].Value) SWAP(0, 2);
	if(List[1].Value > List[3].Value) SWAP(1, 3);
	if(List[0].Value > List[1].Value) SWAP(0, 1);
	if(List[2].Value > List[3].Value) SWAP(2, 3);
	if(List[1].Value > List[2].Value) SWAP(1, 2);
}

BOOL XzCollision::IsCollision(XzSprite * _rectangle, XzSprite * _rectangle2, RECT *_rect)
{
	FLOAT m_fDeterminant1,m_fDeterminant2;
	D3DXMATRIXA16 m_mtInverse1,m_mtInverse2;
	D3DXMatrixInverse(&m_mtInverse1,&m_fDeterminant1,&(_rectangle->m_mtWorld));
	D3DXMatrixInverse(&m_mtInverse2,&m_fDeterminant2,&(_rectangle2->m_mtWorld));

	D3DLOCKED_RECT pLockedRect1,pLockedRect2;
	_rectangle->m_pTexture->LockRect(0,&pLockedRect1,NULL,D3DLOCK_DISCARD);
	_rectangle2->m_pTexture->LockRect(0,&pLockedRect2,NULL,D3DLOCK_DISCARD);

	int a = pLockedRect1.Pitch/4;
	int b = pLockedRect2.Pitch/4;

	D3DXVECTOR2 m_vc2,m_vc21,m_vc22;

	for (m_vc2.y = _rect->top; m_vc2.y < _rect->bottom; m_vc2.y+=1.0f)
	{
		for (m_vc2.x = _rect->left; m_vc2.x < _rect->right; m_vc2.x+=1.0f)
		{
			D3DXVec2TransformCoord(&m_vc21,&m_vc2,&m_mtInverse1);
			D3DXVec2TransformCoord(&m_vc22,&m_vc2,&m_mtInverse2);

			if (((D3DCOLOR*)pLockedRect1.pBits)[a*(int)m_vc21.y + (int)m_vc21.x] >> 24
				== ((D3DCOLOR*)pLockedRect2.pBits)[b*(int)m_vc22.y + (int)m_vc22.x] >> 24
				== 0xff)
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}
#ifndef _XZ_PROFILE_HEADFILE
#define _XZ_PROFILE_HEADFILE

#include <d3dx9.h>
#include <string>
#include "tinyxml.h"
class XzProfile
{
private:
	static XzProfile* m_pSingleton;
public:
	static XzProfile* GetSingleton();
public:
	XzProfile();
	~XzProfile();
	
	VOID SetClearColor(COLORREF color);
	BOOL LoadProfile(std::string file);
	BOOL SaveProfile(std::string file);
public:
	HINSTANCE			hInst;									// ��ǰʵ��
	HWND				hWnd;									// ���ھ��
	WNDCLASSEX			wcex;									// ���ڽṹ��
	LPDIRECT3D9			m_pD3D;									// D3Dָ��
	LPDIRECT3DDEVICE9	m_pd3dDevice;							// �豸ָ��
	INT					m_iWidth;								// ��	
	INT					m_iHeight;								// ��
	DWORD				m_dTime;								// ��ʱ
	DWORD				m_dFPS;									// ֡��
	COLORREF			m_color;
	D3DXVECTOR3			m_vc3AnchorPoint;						// ê��λ��
	D3DXMATRIXA16		m_mtTransform;

};
#endif
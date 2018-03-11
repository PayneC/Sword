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
	HINSTANCE			hInst;									// 当前实例
	HWND				hWnd;									// 窗口句柄
	WNDCLASSEX			wcex;									// 窗口结构体
	LPDIRECT3D9			m_pD3D;									// D3D指针
	LPDIRECT3DDEVICE9	m_pd3dDevice;							// 设备指针
	INT					m_iWidth;								// 宽	
	INT					m_iHeight;								// 高
	DWORD				m_dTime;								// 计时
	DWORD				m_dFPS;									// 帧率
	COLORREF			m_color;
	D3DXVECTOR3			m_vc3AnchorPoint;						// 锚点位置
	D3DXMATRIXA16		m_mtTransform;

};
#endif
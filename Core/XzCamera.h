#ifndef _XZ_CAMERA_HEADFILE
#define _XZ_CAMERA_HEADFILE 

#include "XzNode.h"

class XzCamera : public XzObject
{
	static XzCamera* m_pSingleton;	
public:
	static XzCamera* GetSingleton();
private:	
	D3DXVECTOR2		m_vc2Size;				//相机尺寸
	D3DXVECTOR2		m_vc2Pos;				//相机位置
	D3DXVECTOR2		m_vc2AnchorPoint;		//锚点位置
	D3DXVECTOR2		m_vc2Border_LT;			//边界
	D3DXVECTOR2		m_vc2Border_RB;			//边界
	BOOL			m_bIsUseBorder;			//是否使用边界
	BOOL			m_bIsFollow;			//是否跟随
	BOOL			m_bUseScript;			//设置Lua
	XzNode *		m_pFollowObject;		//相机跟随组件
	D3DXMATRIXA16	m_mtCameraTrans;
	BOOL			m_bIstransform;
public:
	XzCamera();
	~XzCamera();
	
	BOOL GetIsTransform();
	VOID SetSize(FLOAT width, FLOAT height);
	VOID SetAnchorPoint2D(FLOAT x, FLOAT y);	
	VOID SetPos(D3DXVECTOR2 point);
	VOID SetFollowObject(XzNode * node);
	VOID SetBorder(D3DXVECTOR2 LT,D3DXVECTOR2 RB);
	VOID UseFollow(BOOL & boolean);
	VOID UseBorder(BOOL & boolean);
	VOID SetLuaScript();
	D3DXVECTOR2 SceneToWorld(D3DXVECTOR2& point);
	D3DXVECTOR2 WorldToScene(D3DXVECTOR2& point);
	
	D3DXMATRIXA16 GetCameraTransform();
    VOID GetCameraTransform(D3DXMATRIXA16 * pOut, const D3DXVECTOR2 & point, const FLOAT & depth);
	VOID Update();	

	FLOAT GetCameraWidth();
	FLOAT GetCameraHeigth();
};

#endif
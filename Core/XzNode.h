#ifndef _XZ_NODE_FILEHEAD
#define _XZ_NODE_FILEHEAD 

#include "XzObject.h"

class XzNode : public XzObject
{
public:
	static VOID SetSizeY(FLOAT sizeY);
protected:
	static FLOAT m_fSizeY;

	friend class XzPhysicBody;
protected:
	std::multimap<UINT,XzNode*> m_mmpNode;
	std::multimap<UINT,XzNode*>::iterator m_iterNode;
	std::multimap<UINT,XzNode*>::iterator m_endNode;

	XzNode*		m_pParent;				//父节点
    BOOL        m_bIsUseCamera;         //使用相机
	BOOL		m_bIsTransform;			//是否变化
	BOOL        m_bIsRender;

	D3DXVECTOR3 m_vc3AnchorPoint;		//锚点
	D3DXVECTOR3	m_vc3LocalPosition;		//位置
	D3DXVECTOR3	m_vc3Scale;				//缩放
	D3DXVECTOR3	m_vc3Ratote;			//旋转

	D3DXMATRIXA16   m_mtPos;
	D3DXMATRIXA16   m_mtScale;
	D3DXMATRIXA16   m_mtRatote;
	D3DXMATRIXA16	m_mtTransform;


	VOID SetTransformForParent(D3DXMATRIXA16* transform);
	VOID SetAlignForParent(XzNode* node);
	VOID XzNode::SetLocalPosForParent(FLOAT x, FLOAT y);
public:
    XzNode();
    ~XzNode();

	VOID SetMoveBy(FLOAT x, FLOAT y);
	VOID SetLocalMoveBy(FLOAT x, FLOAT y);
	VOID SetRatoteZBy(FLOAT z);
	VOID SetLocalRatoteZBy(FLOAT z);
	VOID SetScaleBy(FLOAT x,FLOAT y);

	VOID SetParent(XzNode * parent);
	VOID SetAnchorPoint2D(FLOAT x, FLOAT y);	
	VOID SetAnchorPoint3D(FLOAT x, FLOAT y, FLOAT z);	

	VOID SetLocalPos(FLOAT x, FLOAT y);
	VOID SetGlobalPos(FLOAT x, FLOAT y);	
	VOID SetLocalPosX(FLOAT x);
	VOID SetLocalPosY(FLOAT y);
	VOID SetGlobalPosX(FLOAT x);
	VOID SetGlobalPosY(FLOAT y);

	VOID SetLocalDepth(FLOAT depth);	
	VOID SetGlobalDepth(FLOAT depth);
	VOID SetLocalScale(FLOAT x,FLOAT y);
	VOID SetGlobalScale(FLOAT x,FLOAT y);
	VOID SetLocalRatoteZ(FLOAT z);
	VOID SetGlobalRatoteZ(FLOAT z);
	virtual VOID SetIsVisible(BOOL boolean);
	VOID SetIsUseCamera(BOOL boolean);
	VOID SetIsTransform(BOOL boolean);

	XzNode* GetParent();
	D3DXVECTOR2 GetAnchorPoint2D();
	D3DXVECTOR3 GetAnchorPoint3D();
	D3DXVECTOR2 GetLocalPos();
	D3DXVECTOR2 GetGlobalPos();
	FLOAT GetLocalDepth();
	FLOAT GetGlobalDepth();
	FLOAT GetLocalScaleX();
	FLOAT GetGlobalScaleX();
	FLOAT GetLocalRatoteZ();
	FLOAT GetGlobalRatoteZ();
	BOOL GetIsVisible();
	BOOL GetIsUseCamera();
	BOOL GetIsTransform();

	
	D3DXMATRIXA16& GetTransforn();

	virtual VOID AddChild(XzNode * node,UINT tag = 0);
	virtual VOID EraseUser();
	virtual VOID Update();
	virtual VOID Render();

	virtual VOID EraseChild(XzNode* node);

	virtual short OnLButtonDown(LPARAM lParam);
	virtual short OnLButtonUp(LPARAM lParam);
	virtual short OnRButtonDown(LPARAM lParam);
	virtual short OnRButtonUp(LPARAM lParam);
	virtual short OnMouseMove(LPARAM lParam);

	virtual VOID CollisionProc(XzPhysicBody* body1,XzPhysicBody* body,char type);
protected:
	
};

#endif




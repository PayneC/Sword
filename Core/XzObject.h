#ifndef _XZ_OBJECT_FILEHEAD
#define _XZ_OBJECT_FILEHEAD

#include "XzSystem.h"

class XzObject;
typedef  short(XzObject::*XzFunction)(WPARAM wParam, LPARAM lParam);
#define type_conversion(FUN) (XzFunction)(&FUN)

class XzCallback
{
public:
    XzFunction m_pFunction;
    XzObject* m_pObject;
public:
    XzCallback();
    ~XzCallback();
	static short Callback(XzCallback * callback, WPARAM wParam,LPARAM lParam);
};

class XzObject
{
	static std::list<XzObject*> m_listObject;

	static BOOL m_bIsRelease;
public:
	static VOID Release();
	//static VOID AllRelease();
protected:
	int	m_iUser;						//用户数量
	BOOL        m_bIsVisible;           //可见性
	D3DXVECTOR3	m_vc3GlobalPosition;	//位置
	friend class XzDirector;
public:
	
    XzObject();
    virtual ~XzObject();
public:
    XzFunction m_pFunction;               //函数指针
	virtual short OnLButtonDown(LPARAM lParam);
	virtual short OnLButtonUp(LPARAM lParam);
	virtual short OnRButtonDown(LPARAM lParam);
	virtual short OnRButtonUp(LPARAM lParam);
	virtual short OnMouseMove(LPARAM lParam);
	virtual short OnKeyDown(WPARAM wParam);
	virtual short OnKeyUp(WPARAM wParam);

	virtual short OnButtonUp(WPARAM wParam,LPARAM lParam);
	virtual short OnButtonDown(WPARAM wParam,LPARAM lParam);
	virtual short OnButtonLeave(WPARAM wParam,LPARAM lParam);

	virtual VOID Update();
	virtual VOID Render();

	int GetUserNumber();
	float GetDepth();
	virtual VOID SetParent(XzObject* parent);
	VOID AddUser();
	virtual VOID EraseUser();
	VOID AutoRelease();
};

#endif
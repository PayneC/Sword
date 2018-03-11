#include "XzObject.h"

#include "XzMessage.h"
#include "XzPhysicWorld.h"

XzCallback::XzCallback()
: m_pFunction(NULL)
, m_pObject(NULL)
{
}
XzCallback::~XzCallback()
{

}
short XzCallback::Callback(XzCallback * callback, WPARAM wParam, LPARAM lParam)
{
   return ((callback->m_pObject)->*(callback->m_pFunction))(wParam, lParam);
}

//=========================================================================================//
std::list<XzObject*> XzObject::m_listObject;
BOOL XzObject::m_bIsRelease = FALSE;

VOID XzObject::Release()
{
	if (!m_bIsRelease)
	{
		return;
	}
	XzMessage::GetSingleton()->RemoveLose();
	XzPhysicWorld::GetSingleton()->ReSeiri();
	std::list<XzObject*>::iterator m_iterObject;
	std::list<XzObject*>::iterator m_endObject;
	m_iterObject = m_listObject.begin();
	while(m_iterObject != m_listObject.end())
	{
		if ((*m_iterObject)->m_iUser <= 0)
		{
			delete *m_iterObject;
			m_iterObject = m_listObject.erase(m_iterObject);
		}
		else
		{
			++m_iterObject;
		}	
	}
	m_bIsRelease = FALSE;
}

XzObject::XzObject()
	:m_pFunction(NULL)
	,m_iUser(0)
	, m_vc3GlobalPosition(0.f,0.f,0.f)
	,m_bIsVisible(TRUE)
{
}

XzObject::~XzObject()
{
}

short XzObject::OnLButtonDown(LPARAM lParam){return 0;}
short XzObject::OnLButtonUp(LPARAM lParam){return 0;}
short XzObject::OnRButtonDown(LPARAM lParam){return 0;}
short XzObject::OnRButtonUp(LPARAM lParam){return 0;}
short XzObject::OnMouseMove(LPARAM lParam){return 0;}

short XzObject::OnKeyDown(WPARAM wParam){return 0;}
short XzObject::OnKeyUp(WPARAM wParam){return 0;}
short XzObject::OnButtonUp(WPARAM wParam,LPARAM lParam){return 0;}
short XzObject::OnButtonDown(WPARAM wParam,LPARAM lParam){return 0;}
short XzObject::OnButtonLeave(WPARAM wParam,LPARAM lParam){return 0;}
VOID XzObject::Update(){}
VOID XzObject::Render(){}

int XzObject::GetUserNumber()
{
	return m_iUser;
}
VOID XzObject::AddUser()
{
	++m_iUser;
}
VOID XzObject::EraseUser()
{
	--m_iUser;
	if (m_iUser==0)
	{
		m_bIsRelease = TRUE;
	}
}
VOID XzObject::AutoRelease()
{
	m_listObject.push_back(this);
}
VOID XzObject::SetParent(XzObject* parent)
{

}
float XzObject::GetDepth()
{
	return m_vc3GlobalPosition.z;
}
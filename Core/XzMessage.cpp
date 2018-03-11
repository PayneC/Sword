#include "XzMessage.h"
#include "XzDirector.h"

#include <algorithm>

XzMessage* XzMessage::m_pSingleton = NULL;
XzMessage* XzMessage::GetSingleton()
{
	if (!m_pSingleton)
	{
		static XzMessage m_singleton;
		m_pSingleton = &m_singleton;
	}
	return m_pSingleton;
}

XzMessage::XzMessage()
{
}

XzMessage::~XzMessage()
{
	std::map<UINT, std::list<XzCallback*>*>::iterator m_iterMsg = m_mapMessage.begin();
	std::map<UINT, std::list<XzCallback*>*>::iterator m_endMsg = m_mapMessage.end();
	std::list<XzCallback*>::iterator m_iterProc;
	std::list<XzCallback*>::iterator m_endProc;
	for(;m_iterMsg != m_endMsg;++m_iterMsg)
	{
		m_iterProc = (m_iterMsg->second)->begin();
		m_endProc = (m_iterMsg->second)->end();
		for (; m_iterProc != m_endProc; ++m_iterProc)
		{
			delete (*m_iterProc);
			(*m_iterProc) = NULL;
		}

		delete m_iterMsg->second;
		m_iterMsg->second = NULL;
	}
}

VOID XzMessage::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		OnMouseMsg(msg,lParam);
		break;
	case WM_KEYDOWN:
		OnKeyDown(wParam);
		break;
	case WM_KEYUP:
		OnKeyUp(wParam);
		break;
	default:
		{
			short v = 0;
			std::list<XzCallback*>::iterator m_iterProc;
			std::list<XzCallback*>::iterator m_endProc;
			std::map<UINT, std::list<XzCallback*>*>::iterator m_iterMsg;
			m_iterMsg = m_mapMessage.find(msg);
			if (m_iterMsg != m_mapMessage.end())
			{
				m_iterProc = (m_iterMsg->second)->begin();
				m_endProc = (m_iterMsg->second)->end();
				for (; m_iterProc != m_endProc; ++m_iterProc)
				{
					v = XzCallback::Callback(*m_iterProc,wParam,lParam);
					if (v == MSG_END)
					{
						return;
					}
				}
			}
		}
		break;
	}
}

short XzMessage::OnMouseMsg(UINT msg,LPARAM lParam)
{
	std::list<XzObject*>::iterator m_iterNode;
	std::list<XzObject*>::iterator m_endNode;
	short v = 0;
	switch(msg)
	{
	case WM_LBUTTONDOWN:
		for (m_iterNode = m_listMouseMsg.begin();m_iterNode != m_listMouseMsg.end();++m_iterNode)
		{
			if (*m_iterNode)
			{
				v = (*m_iterNode)->OnLButtonDown(lParam);
				if (v)
				{
					return v;
				}
			}
		}
		break;
	case WM_RBUTTONDOWN:
		for (m_iterNode = m_listMouseMsg.begin();m_iterNode != m_listMouseMsg.end();++m_iterNode)
		{
			if (*m_iterNode)
			{
				v = (*m_iterNode)->OnRButtonDown(lParam);
				if (v)
				{
					return v;
				}
			}
		}
		break;
	case WM_LBUTTONUP:
		for (m_iterNode = m_listMouseMsg.begin();m_iterNode != m_listMouseMsg.end();++m_iterNode)
		{
			if (*m_iterNode)
			{
				v = (*m_iterNode)->OnLButtonUp(lParam);
				if (v)
				{
					return v;
				}
			}
		}
		break;
	case WM_RBUTTONUP:
		for (m_iterNode = m_listMouseMsg.begin();m_iterNode != m_listMouseMsg.end();++m_iterNode)
		{
			if (*m_iterNode)
			{
				v = (*m_iterNode)->OnRButtonUp(lParam);
				if (v)
				{
					return v;
				}
			}
		}
		break;
	case WM_MOUSEMOVE:
		for (m_iterNode = m_listMouseMsg.begin();m_iterNode != m_listMouseMsg.end();++m_iterNode)
		{
			if (*m_iterNode)
			{
				v = (*m_iterNode)->OnMouseMove(lParam);
				if (v)
				{
					return v;
				}
			}
		}
		break;
	}

	return 0;
}

short XzMessage::OnKeyDown(WPARAM wParam)
{
	std::list<XzObject*>::iterator m_iterNode;
	std::list<XzObject*>::iterator m_endNode;
	for (m_iterNode = m_vtKeyDown.begin();m_iterNode != m_vtKeyDown.end();++m_iterNode)
	{
		(*m_iterNode)->OnKeyDown(wParam);
	}
	return 0;
}
short XzMessage::OnKeyUp(WPARAM wParam)
{
	std::list<XzObject*>::iterator m_iterNode;
	std::list<XzObject*>::iterator m_endNode;
	for (m_iterNode = m_vtKeyUp.begin();m_iterNode != m_vtKeyUp.end();++m_iterNode)
	{
		(*m_iterNode)->OnKeyUp(wParam);
	}
	return 0;
}

VOID XzMessage::RegisterMessage(UINT msg,XzObject* object, XzFunction f)
{
    XzCallback* m_tmp = new XzCallback;
    m_tmp->m_pFunction = f;
    m_tmp->m_pObject = object;
	std::map<UINT, std::list<XzCallback*>*>::iterator m_iterMsg = m_mapMessage.begin();
    m_iterMsg = m_mapMessage.find(msg);
    if (m_iterMsg == m_mapMessage.end())
    {
        std::list<XzCallback*>* m_vtTmp = new std::list<XzCallback*>;
        m_vtTmp->push_back(m_tmp);
        m_mapMessage.insert(std::make_pair(msg, m_vtTmp));
    }
    else
    {
        (m_iterMsg->second)->push_back(m_tmp);
    }
}

VOID XzMessage::ListenMouse(XzObject* object)
{
	m_listMouseMsg.push_back(object);
	std::list<XzObject*>::iterator m_iterMouseMsg = m_listMouseMsg.begin();
	std::list<XzObject*>::iterator m_endMouseMsg = m_listMouseMsg.end();
	cp m_cp;
	m_listMouseMsg.sort(m_cp);
}

VOID XzMessage::ListenKey(UINT msg,XzObject* object)
{
	switch(msg)
	{
	case WM_KEYDOWN:
		m_vtKeyDown.push_back(object);
		break;
	case WM_KEYUP:
		m_vtKeyUp.push_back(object);
		break;
	default:
		break;
	}
}

VOID XzMessage::RemoveLoseMouse()
{
	std::list<XzObject*>::iterator m_iterNode;

	m_iterNode = m_listMouseMsg.begin();
	while (m_iterNode != m_listMouseMsg.end())
	{
		if ((*m_iterNode)->GetUserNumber() <= 0)
		{
			m_iterNode = m_listMouseMsg.erase(m_iterNode);
		}
		else
		{
			++m_iterNode;
		}
	}
}

VOID XzMessage::RemoveLoseKey()
{
	std::list<XzObject*>::iterator m_iterNode = m_vtKeyDown.begin();

	while (m_iterNode != m_vtKeyDown.end())
	{
		if ((*m_iterNode)->GetUserNumber() <= 0)
		{
			m_iterNode = m_vtKeyDown.erase(m_iterNode);
		}
		else
		{
			++m_iterNode;
		}
	}

	m_iterNode = m_vtKeyUp.begin();
	while (m_iterNode != m_vtKeyUp.end())
	{
		if ((*m_iterNode)->GetUserNumber() <= 0)
		{
			m_iterNode = m_vtKeyUp.erase(m_iterNode);
		}
		else
		{
			++m_iterNode;
		}
	}
}
VOID XzMessage::RemoveLoseMsg()
{
	std::list<XzCallback*>::iterator m_iterProc;
	std::map<UINT, std::list<XzCallback*>*>::iterator m_iterMsg;
	std::map<UINT, std::list<XzCallback*>*>::iterator m_endMsg;
	m_iterMsg = m_mapMessage.begin();
	m_endMsg = m_mapMessage.end();
	for (;m_iterMsg != m_endMsg;++m_iterMsg)
	{
		m_iterProc = m_iterMsg->second->begin();
		while (m_iterProc != m_iterMsg->second->end())
		{
			if ((*m_iterProc)->m_pObject->GetUserNumber() <= 0)
			{
				delete (*m_iterProc);
				m_iterProc = m_iterMsg->second->erase(m_iterProc);
			}
			else
			{
				++m_iterProc;
			}
		}
	}
}

VOID XzMessage::RemoveLose()
{
	RemoveLoseKey();
	RemoveLoseMouse();
	RemoveLoseMsg();
}
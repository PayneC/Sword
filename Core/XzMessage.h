#ifndef XZ_MESSAGE_HEADFILE
#define XZ_MESSAGE_HEADFILE

#include "XzObject.h" 

struct cp
{
	bool operator()(XzObject* o1,XzObject* o2){return o1->GetDepth() < o2->GetDepth();}
};

class XzMessage
{
	static XzMessage* m_pSingleton;
private:
    std::map<UINT, std::list<XzCallback*>*> m_mapMessage;

	std::list<XzObject*> m_listMouseMsg;
    short OnMouseMsg(UINT msg,LPARAM lParam);
	std::list<XzObject*> m_vtKeyDown;
    short OnKeyDown(WPARAM wParam);
	std::list<XzObject*> m_vtKeyUp;
    short OnKeyUp(WPARAM wParam);
	
public:
    XzMessage();
    ~XzMessage();

	static XzMessage* GetSingleton();

	VOID MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	VOID ListenMouse(XzObject* object);
	VOID ListenKey(UINT msg,XzObject* object);
    VOID RegisterMessage(UINT msg, XzObject* object, XzFunction f);

	VOID RemoveLose();
	VOID RemoveLoseMouse();
	VOID RemoveLoseKey();
	VOID RemoveLoseMsg();
};

#endif
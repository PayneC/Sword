#ifndef _WINDOW_HEADFILE
#define _WINDOW_HEADFILE

#include "CXzEngine.h"

class CWindow : public XzLayer
{
private:
	XzButtonSprite* m_pClose;			//¹Ø±Õ¼ü
	XzButtonSprite* m_pBackground;		//±³¾°
	WPARAM          m_HotKey;			//¿ì½Ý¼ü
	
public:
	CWindow();
	~CWindow();

	static CWindow* Create(std::wstring bg = L"/0",std::wstring close = L"/0");

	
	short SetVisible(WPARAM wParam, LPARAM lParam);
	VOID RegisterHotKey(UINT msg,WPARAM key);
	virtual short OnButtonUp(WPARAM wParam,LPARAM lParam);
	VOID AddGUIObject(XzNode * node,UINT tag = 0);

	static CWindow* CreateFromXML(std::string file);
	static CWindow* CreateFromXML(TiXmlElement * ele,XzNode * node);
};
#endif
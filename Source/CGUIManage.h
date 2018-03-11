#ifndef _GUIMANAGE_FILEHEAD
#define _GUIMANAGE_FILEHEAD

#include "CXzEngine.h"

class CGUIManage : public XzObject
{
private:
	static CGUIManage* m_pSingleton;
public:
	static CGUIManage* GetSingleton();

	CGUIManage();
	~CGUIManage();

	short OnButtonUp(WPARAM wParam, LPARAM lParam);
	short OnButtonDown(WPARAM wParam, LPARAM lParam);
	short OnButtonLeave(WPARAM wParam, LPARAM lParam);
};

#endif
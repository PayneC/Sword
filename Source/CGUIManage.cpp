#include "CGUIManage.h"
#include "../core/XzDirector.h"


CGUIManage* CGUIManage::m_pSingleton = 0;

CGUIManage* CGUIManage::GetSingleton()
{
	if (!m_pSingleton)
	{
		static CGUIManage m_singleton;
		m_pSingleton = &m_singleton;
	}
	return m_pSingleton;
}
CGUIManage::CGUIManage()
{
	AddUser();
	XzMessage::GetSingleton()->RegisterMessage(MYMSG_BUTTONDOWN,this,type_conversion(CGUIManage::OnButtonUp));
	XzMessage::GetSingleton()->RegisterMessage(MYMSG_BUTTONUP,this,type_conversion(CGUIManage::OnButtonDown));
	XzMessage::GetSingleton()->RegisterMessage(MYMSG_BUTTONLEAVE,this,type_conversion(CGUIManage::OnButtonLeave));
}
CGUIManage::~CGUIManage()
{

}

short CGUIManage::OnButtonUp(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case BUTTON_LEVEL:
		XzDirector::GetSingleton()->SetIsPushScene(lParam);
		return MSG_END;
		break;
	case BUTTON_EXIT:
		XzDirector::GetSingleton()->SetGameOver();
		break;
	case BUTTON_HOME:
		XzDirector::GetSingleton()->SetIsPopScene();
		break;
	case BUTTON_AGAIN:
		XzDirector::GetSingleton()->SetIsPopScene();
		XzDirector::GetSingleton()->SetIsPushScene(XzDirector::GetSingleton()->GetSceneInfo());
		break;
	default:
		break;
	}

	return 0;
}
short CGUIManage::OnButtonDown(WPARAM wParam, LPARAM lParam)
{
	return 0;
}
short CGUIManage::OnButtonLeave(WPARAM wParam, LPARAM lParam)
{
	return 0;
}
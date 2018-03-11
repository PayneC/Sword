#include "XzInput.h"

XzInput* XzInput::m_pSingleton = NULL;
XzInput* XzInput::GetSingleton()
{
	if (!m_pSingleton)
	{
		static XzInput m_singleton;
		m_pSingleton = &m_singleton;
	}
	return m_pSingleton;
}
XzInput::XzInput()
	:m_cMaxKeyCount(char(125))
	,m_cKeycount(char(0))
{

}
XzInput::~XzInput()
{

}
void XzInput::SetMaxKeyCount(char maxKeyCount)
{
	m_cMaxKeyCount = maxKeyCount;
}
void XzInput::ProcMsg(unsigned int msg,unsigned int wParam,long lParam)
{
    if (m_cKeycount >= m_cMaxKeyCount)
    {
        return;
    }
    switch (msg)
    {
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		m_vc2MouseMove.x = (float)LOWORD(lParam) - m_vc2MouseBeforePos.x;
		m_vc2MouseMove.y = (float)HIWORD(lParam) - m_vc2MouseBeforePos.y;
		m_vc2MouseBeforePos+=m_vc2MouseMove;
		break;
    case  WM_KEYDOWN:
        if (key[wParam]){ return; }
        key[wParam] = TRUE;
        ++m_cKeycount;
        break;
    case WM_KEYUP:
        if (!key[wParam]){ return; }
        key[wParam] = FALSE;
        --m_cKeycount;
        break;
    default:
        break;
    }
}

bool XzInput::KeyDown(char k)
{
    return key[k];
}
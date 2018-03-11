#include "XzTime.h"

XzTime* XzTime::m_pSingleton = 0;

XzTime* XzTime::GetSingleton()
{
    if (!m_pSingleton)
    {
       static XzTime m_singleton;
       m_pSingleton = &m_singleton;
    }
    return m_pSingleton;
}

XzTime::XzTime()
    :m_dDeltaTime(0)
	,m_fDeltaTime(0)
	,m_dFrameDT(0)
	,m_fFrameDT(0)
{
    m_StartTime = m_dCurrentTime = GetTickCount();
    m_dPreviousTime = m_dCurrentTime;
}

XzTime::~XzTime()
{
}

DWORD XzTime::GetCurrTime()
{
    return  GetTickCount();
}

void XzTime::Update()
{
    m_dCurrentTime = GetTickCount();
    m_dDeltaTime = m_dCurrentTime - m_dPreviousTime;
	m_fDeltaTime = (FLOAT)m_dDeltaTime / 1000.f;
    m_dPreviousTime = m_dCurrentTime;
}
VOID XzTime::SetDeletaTime(unsigned long time)
{
	m_dDeltaTime = time;
	m_fDeltaTime = (FLOAT)m_dDeltaTime/1000.f;
}
VOID XzTime::SetDeletaTimeForFrame(unsigned long time)
{
	m_dFrameDT = time;
	m_fFrameDT = (FLOAT)m_dFrameDT / 1000.f;
}


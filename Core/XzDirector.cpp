#include "XzDirector.h"
#include "XzCamera.h"
#include "..\Source\CGUIManage.h"

XzDirector* XzDirector::m_pSingleton = NULL;
XzDirector* XzDirector::GetSingleton()
{
	if (!m_pSingleton)
	{
		static XzDirector m_singleton;
		m_pSingleton = &m_singleton;
	}
	return m_pSingleton;
}
XzDirector::XzDirector()
: m_dItimepiece(0)
, m_dMoreTime(0)
, m_bRuning(FALSE)
, m_bIsAppSurvival(TRUE)
, m_bIsPopScene(FALSE)
, m_bIsPushScene(FALSE)
{
	m_pTime = XzTime::GetSingleton();
	m_pCamera = XzCamera::GetSingleton();
	m_pApplication = CApplication::GetSingleton();
}
XzDirector::~XzDirector()
{
}
VOID XzDirector::AddGlobalObject(XzObject* object)
{
	m_listObject.push_back(object);
	object->AddUser();
}
VOID XzDirector::PushScene(XzScene * _scene)
{
	if (!m_skScene.empty())
	{
		m_skScene.top()->SetIsVisible(FALSE);
	}
	m_skScene.push(_scene);
	_scene->AddUser();
}
VOID XzDirector::PopScene()
{
    m_skScene.top()->EraseUser();
	//m_skScene.top()->Update();
	m_skScene.pop();
	XzCamera::GetSingleton()->SetPos(D3DXVECTOR2(0.f,0.f));
	XzCamera::GetSingleton()->SetFollowObject(NULL);
	if (!m_skScene.empty())
	{
		m_skScene.top()->SetIsVisible(TRUE);
	}
}
VOID XzDirector::RunGame()
{
	m_bRuning = TRUE;
}
VOID XzDirector::SuspendGame()
{
	m_bRuning = FALSE;
}
VOID XzDirector::EndGame()
{
	while(!m_skScene.empty())
	{
		m_skScene.top()->EraseUser();
		m_skScene.pop();
    }
	m_iterObject = m_listObject.begin();
	m_endObject = m_listObject.end();
	while(m_iterObject!= m_endObject)
	{
		(*m_iterObject)->EraseUser();
		++m_iterObject;
	}
	m_listObject.clear();
	XzObject::Release();
	m_pApplication->KillApplication();
}
VOID XzDirector::Init()
{
	CGUIManage::GetSingleton();
	m_pApplication->InitApplication();
}
VOID XzDirector::Update()
{
	//if (!m_bRuning)
		//return;
		//XzObject::Release();
	if (m_skScene.empty())
		return;

	m_pCamera->Update();

	if(m_skScene.top()) 
		m_skScene.top()->Update();

	m_iterObject = m_listObject.begin();
	m_endObject = m_listObject.end();
	while(m_iterObject!= m_endObject)
	{
		if ((*m_iterObject)->m_bIsVisible)
		{
			(*m_iterObject)->Update();
		}
		++m_iterObject;
	}


}
VOID XzDirector::Render()
{
	if (m_skScene.empty())
		return;
	if (m_skScene.top())
		m_skScene.top()->Render();

	m_iterObject = m_listObject.begin();
	m_endObject = m_listObject.end();
	while(m_iterObject!= m_endObject)
	{
		if ((*m_iterObject)->m_bIsVisible)
		{
			(*m_iterObject)->Render();
		}
		++m_iterObject;
	}
}

VOID XzDirector::MainLoop()
{
	if(m_bIsPopScene)
	{
		PopScene();
		XzObject::Release();
		m_bIsPopScene = FALSE;
	}

	if(m_bIsPushScene)
	{
		CApplication::GetSingleton()->ChangeScene(m_lNextSceneInfo);
		m_bIsPushScene = FALSE;
	}
	XzObject::Release();
	m_pTime->Update();
	if (m_pTime->m_dDeltaTime > 33)// 时间间隔控制
	{
		m_pTime->SetDeletaTime(33);
	}

	m_dItimepiece += m_pTime->m_dDeltaTime;
    if (m_dItimepiece >= XzSystem::SysProfile->m_dFPS)
    {
		m_pTime->SetDeletaTimeForFrame(m_dItimepiece - m_dMoreTime);
		m_dItimepiece -= XzSystem::SysProfile->m_dFPS;
		m_dMoreTime = m_dItimepiece;
		if (m_bRuning)
		{
			XzPhysicWorld::GetSingleton()->Update(m_pTime->m_fDeltaTime);
		}
		Update();
		XzSystem::SysProfile->m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,XzSystem::SysProfile->m_color, 1.0f, 0 );
		if(SUCCEEDED( XzSystem::SysProfile->m_pd3dDevice->BeginScene()))
		{
			Render();
			XzSystem::SysProfile->m_pd3dDevice->EndScene();
		}
		XzSystem::SysProfile->m_pd3dDevice->Present( NULL, NULL, NULL, NULL );
    }
}

XzScene* XzDirector::GetCurrentScene()
{
	if (m_skScene.empty())
	{
		return NULL;
	}
	return m_skScene.top();
}

VOID XzDirector::SetIsPushScene(LONG info)
{
	m_lNextSceneInfo = info;
	m_bIsPushScene = TRUE;
}
LONG XzDirector::GetSceneInfo()
{
	return m_lNextSceneInfo ;
}

VOID XzDirector::SetIsPopScene()
{
	m_bIsPopScene = TRUE;
}
VOID XzDirector::SetGameOver()
{
	m_bIsAppSurvival = FALSE;
}

BOOL XzDirector::GetGameSurvival()
{
	return m_bIsAppSurvival;
}
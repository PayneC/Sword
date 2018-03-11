#ifndef _XZ_DIRECTOR_HEADFILE
#define _XZ_DIRECTOR_HEADFILE

#include "..\Source\CApplication.h"

class XzDirector : public XzObject	//单例：导演类
{
	static XzDirector * m_pSingleton;
private:
	XzTime*				m_pTime;							//时间指针	
	XzCamera*			m_pCamera;							//相机指针
	CApplication*		m_pApplication;						//应用指针
    DWORD				m_dItimepiece;						//累计时间
	DWORD				m_dMoreTime;						//累计时间超过帧速的时间					
	BOOL				m_bRuning;							//运行中？
	LONG				m_lNextSceneInfo;					//下一个要切换的场景信息
	BOOL				m_bIsPopScene;						//是否弹出场景
	BOOL				m_bIsPushScene;						//是否增加场景	
	BOOL				m_bIsAppSurvival;					//应用是否存活
	std::stack<XzScene*> m_skScene;							//场景的容器
	std::list<XzObject*> m_listObject;						//全局存在的组件 
	std::list<XzObject*>::iterator m_iterObject;
	std::list<XzObject*>::iterator m_endObject;
public:
    XzDirector();
    ~XzDirector();
	static XzDirector * GetSingleton();


	VOID AddGlobalObject(XzObject* object);
	VOID PushScene(XzScene * _scene);	//增加场景
	VOID PopScene();					//弹出场景

	VOID SetIsPushScene(LONG info);		//切换场景
	VOID SetIsPopScene();				//切换场景
	LONG GetSceneInfo();

	VOID RunGame();						//运行游戏
	VOID SuspendGame();					//暂停游戏
    VOID EndGame();
	VOID Init();
	VOID Update();						
	VOID Render();

    VOID MainLoop();

	VOID SetGameOver();
	BOOL GetGameSurvival();

	XzScene* GetCurrentScene();
};

#endif
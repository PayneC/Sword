#ifndef _APPLICATION_FILEHEAD
#define _APPLICATION_FILEHEAD

#include "CResourceManage.h"
#include "CPlayer.h"


class CApplication 
{
private:
	static CApplication* m_pSingleton;
public:
	static CApplication* GetSingleton();
public:
	CApplication();
	~CApplication();
	VOID ChangeScene(LPARAM lParam);
	
	VOID InitApplication();
	VOID KillApplication();
	VOID InitGlobalObject();

	VOID About();
private:
	//CPlayer* m_pPlayer;
};

#endif
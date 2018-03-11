#ifndef _GAMEINFOUI_HEADFILE
#define _GAMEINFOUI_HEADFILE

#include "CPlayer.h"

class CGameInfoUI : public XzLayer
{
	XzSprite* m_pBlood;
	XzEditSprite* m_pName;
	XzEditSprite* m_pMark;
	INT m_iMark;
	CPlayer* m_pPlayer;
public:
	CGameInfoUI();
	~CGameInfoUI();

	VOID SetPlayer(CPlayer* player);
	VOID Update();
	virtual short MonsterDeath(WPARAM wParam, LPARAM lParam);
	static CGameInfoUI* Create();
};

#endif


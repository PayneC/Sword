#include "..\Core\XzTime.h"
#include "..\Core\XzCamera.h"
#include "..\Core\XzScene.h"
#include "..\Core\XzMessage.h"
#include "..\Core\XzFrameArraySprite.h"
#include "..\Core\XzLayer.h"
#include "..\Core\XzButtonSprite.h"
#include "..\Core\XzEditSprite.h"

//��ײ����
#define BODY_GROUND			1
#define BODY_PLAYER_BODY	2
#define BODY_PLAYER_SWORD	3
#define BODY_MONSTER_BODY   4
#define BODY_MONSTER_FIRE	5
#define BODY_FIRE			6
#define BODY_Flag			7
//��Ϣ��� �� WM_USER + 100 ��ʼ
#define MYMSG_GAME_PLAY_DEATH	WM_USER + 100
#define MYMSG_GAME_PLAY_VICTORY	WM_USER + 101	
#define MYMSG_GAME_MONSTER_DEATH	WM_USER + 102

//Button���
#define BUTTON_PLAY			1
#define BUTTON_ABOUT		2
#define BUTTON_REVIVE		3
#define BUTTON_AGAIN		4
#define BUTTON_HOME			5
#define BUTTON_EXIT			6
#define BUTTON_LEVEL		7
#define BUTTON_PAUSE		8
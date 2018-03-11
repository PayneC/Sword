#ifndef _XZ_DIRECTOR_HEADFILE
#define _XZ_DIRECTOR_HEADFILE

#include "..\Source\CApplication.h"

class XzDirector : public XzObject	//������������
{
	static XzDirector * m_pSingleton;
private:
	XzTime*				m_pTime;							//ʱ��ָ��	
	XzCamera*			m_pCamera;							//���ָ��
	CApplication*		m_pApplication;						//Ӧ��ָ��
    DWORD				m_dItimepiece;						//�ۼ�ʱ��
	DWORD				m_dMoreTime;						//�ۼ�ʱ�䳬��֡�ٵ�ʱ��					
	BOOL				m_bRuning;							//�����У�
	LONG				m_lNextSceneInfo;					//��һ��Ҫ�л��ĳ�����Ϣ
	BOOL				m_bIsPopScene;						//�Ƿ񵯳�����
	BOOL				m_bIsPushScene;						//�Ƿ����ӳ���	
	BOOL				m_bIsAppSurvival;					//Ӧ���Ƿ���
	std::stack<XzScene*> m_skScene;							//����������
	std::list<XzObject*> m_listObject;						//ȫ�ִ��ڵ���� 
	std::list<XzObject*>::iterator m_iterObject;
	std::list<XzObject*>::iterator m_endObject;
public:
    XzDirector();
    ~XzDirector();
	static XzDirector * GetSingleton();


	VOID AddGlobalObject(XzObject* object);
	VOID PushScene(XzScene * _scene);	//���ӳ���
	VOID PopScene();					//��������

	VOID SetIsPushScene(LONG info);		//�л�����
	VOID SetIsPopScene();				//�л�����
	LONG GetSceneInfo();

	VOID RunGame();						//������Ϸ
	VOID SuspendGame();					//��ͣ��Ϸ
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
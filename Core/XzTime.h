#ifndef _XZ_TIME_FILEHEAD 
#define _XZ_TIME_FILEHEAD 

#include <d3dx9.h>

class XzTime
{
    static XzTime* m_pSingleton;
public:
	static XzTime* GetSingleton();
private:
    unsigned long m_StartTime;
    unsigned long m_dCurrentTime;	//����ѭ����ʼ��ʱ��
    unsigned long m_dPreviousTime;	
public:  
	unsigned long m_dDeltaTime;
	FLOAT m_fDeltaTime;

	unsigned long m_dFrameDT;
	FLOAT m_fFrameDT;

    XzTime();
public:
    ~XzTime();

    void Update();
	VOID SetDeletaTime(unsigned long time);
	VOID SetDeletaTimeForFrame(unsigned long time);
    unsigned long GetCurrTime();	//���»�ȡ�ĵ�ǰʱ��
};

#endif
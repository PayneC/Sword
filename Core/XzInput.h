#ifndef _XZ_INPUT_HEADFILE
#define _XZ_INPUT_HEADFILE

#include <d3dx9.h>

class XzInput
{
private:
    static XzInput* m_pSingleton;
public:
	static XzInput* GetSingleton();
    bool key[256];
private:
	D3DXVECTOR2 m_vc2MouseBeforePos;
public:
    XzInput();
    ~XzInput();
    char m_cKeycount;
    char m_cMaxKeyCount;
	D3DXVECTOR2 m_vc2MouseMove;
    void SetMaxKeyCount(char);
    void ProcMsg(unsigned int,unsigned int,long lParam);
    bool KeyDown(char);

   
};
#endif
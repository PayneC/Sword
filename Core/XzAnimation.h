#ifndef _XZ_ANIMATION_HEADFILE
#define _XZ_ANIMATION_HEADFILE

#include "XzTexture.h"

class XzAnimation : public XzTexture
{
    DWORD           m_fTime;                //��ʱ��
    DWORD           m_fFramesPerSecond;     //֡��
    DWORD           m_dRate;                //����

    BOOL            m_bPlay;                //����
    BOOL            m_bPause;               //��ͣ

    XzCallback*		m_callback;				//�ص�����
    INT             m_iFrequency;           //���Ŵ���  -1Ϊ���޴�
    INT             m_iCurrentFrequency;    //��ǰ����

    std::vector<XzTexture*> m_vtTexture;
    std::vector<XzTexture*>::iterator m_iter;
    std::vector<XzTexture*>::iterator m_iterEnd;
public:
    XzAnimation();
    ~XzAnimation();

    VOID Update();
    VOID AddFrame(XzTexture* texture);
	virtual VOID Draw(LPD3DXSPRITE & sprite,D3DXVECTOR3 pos);
    virtual VOID SetPos(D3DXVECTOR2& point);
    virtual VOID SetDepth(FLOAT depth);
    virtual VOID SetAnchorPoint(D3DXVECTOR2& point);
    virtual VOID SetBeginFrame();
    virtual VOID SetPlayFrequency(INT number, XzObject* object, XzFunction function);
    virtual VOID SetFPS(DWORD FPS);
    virtual VOID SetPlay(BOOL boolean);

    friend class XzCollision;
    static XzAnimation* Create(std::wstring filePath, UINT row = 1, UINT col = 1, UINT frist = 0, UINT frame = 0);
	static XzAnimation* CreateFromXML(std::string file);
	static XzAnimation* CreateFromXML(TiXmlElement * ele,XzSprite * node);
};

#endif
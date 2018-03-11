#ifndef _XZ_TEXTURE_HEADFILE
#define _XZ_TEXTURE_HEADFILE

#include "XzObject.h"
class XzSprite;
class XzTexture : public XzObject
{
protected:
    LPDIRECT3DTEXTURE9		m_pTexture;				//ͼƬָ��
    D3DCOLOR 				m_color;				//���ɫ
    RECT					m_rtRect;				//��������
	D3DXVECTOR3				m_vc3AnchorPoint;		//ê��λ��
    friend class XzAnimation;
	friend class XzSprite;
public: 
    XzTexture();
    ~XzTexture();

	static XzTexture * Create(std::wstring filePath);
	static XzTexture * Create(std::wstring filePath, RECT* rect);
	static XzTexture * Create(const XzTexture* texture, RECT* rect);
	static XzTexture* CreateFromXML(std::string file);
	static XzTexture* CreateFromXML(TiXmlElement * ele,XzSprite * node);

    virtual VOID Draw(LPD3DXSPRITE & sprite,D3DXVECTOR3 pos);
    //����λ��
    virtual VOID SetPos(D3DXVECTOR2& point);
    //�������
    virtual VOID SetDepth(FLOAT depth);
    //����ê��λ��
    virtual VOID SetAnchorPoint(D3DXVECTOR2& point);
    //���ö���Ϊ��ʼ֡��������
    virtual VOID SetBeginFrame();
    //���ö������Ŵ�������������������ʵ�����ص�������
    virtual VOID SetPlayFrequency(INT number, XzObject* node, XzFunction function);
    //���ö���֡�٣�������
    virtual VOID SetFPS(DWORD FPS);
    //���ö�������
    virtual VOID SetPlay(BOOL boolean);
    //��������
    virtual VOID Insert(INT type, XzTexture* unit);
   
	BOOL InRect(D3DXVECTOR2 & piont);
	BOOL InRectX(D3DXVECTOR2 & piont);
	BOOL InRectY(D3DXVECTOR2 & piont);
    LONG GetWidth();
    LONG GetHeight();
};
#endif
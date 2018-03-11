#ifndef _XZ_TEXTURE_HEADFILE
#define _XZ_TEXTURE_HEADFILE

#include "XzObject.h"
class XzSprite;
class XzTexture : public XzObject
{
protected:
    LPDIRECT3DTEXTURE9		m_pTexture;				//图片指针
    D3DCOLOR 				m_color;				//混合色
    RECT					m_rtRect;				//矩形区域
	D3DXVECTOR3				m_vc3AnchorPoint;		//锚点位置
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
    //设置位置
    virtual VOID SetPos(D3DXVECTOR2& point);
    //设置深度
    virtual VOID SetDepth(FLOAT depth);
    //设置锚点位置
    virtual VOID SetAnchorPoint(D3DXVECTOR2& point);
    //设置动画为起始帧（动画）
    virtual VOID SetBeginFrame();
    //设置动画播放次数（动画）（次数，实例，回调函数）
    virtual VOID SetPlayFrequency(INT number, XzObject* node, XzFunction function);
    //设置动画帧速（动画）
    virtual VOID SetFPS(DWORD FPS);
    //设置动画播放
    virtual VOID SetPlay(BOOL boolean);
    //增加内容
    virtual VOID Insert(INT type, XzTexture* unit);
   
	BOOL InRect(D3DXVECTOR2 & piont);
	BOOL InRectX(D3DXVECTOR2 & piont);
	BOOL InRectY(D3DXVECTOR2 & piont);
    LONG GetWidth();
    LONG GetHeight();
};
#endif
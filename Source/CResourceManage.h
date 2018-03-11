#ifndef _RESOURCEMANAGE_HEADFILE
#define _RESOURCEMANAGE_HEADFILE

#include "CXzEngine.h"

class CResourceManage
{
private:
	static CResourceManage* m_pSingleton;
public:
	static CResourceManage* GetSingleton();

	CResourceManage();
	~CResourceManage();
	XzScene* LoadScene(std::string file);
	XzScene* LoadFromXML(std::string file);
	VOID LoadLayer(TiXmlElement * ele,XzScene * node);
	VOID LoadSprite(TiXmlElement * ele,XzNode * node,const char* _value);
	VOID LoadArrSprite(TiXmlElement * ele,XzNode * node,const char* _value);
	VOID LoadButtonSprite(TiXmlElement * ele,XzNode * node,const char* _value);
	VOID LoadPhysicBody(TiXmlElement * ele,XzSprite * node,const char* _value);
	VOID LoadTexture(TiXmlElement * ele,XzSprite * node,const char* _value);
	VOID LoadAnimation(TiXmlElement * ele,XzSprite * node,const char* _value);



};

#endif
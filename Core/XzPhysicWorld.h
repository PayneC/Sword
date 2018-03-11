#ifndef _XZ_PHYSICWORLD_HEADFILE
#define _XZ_PHYSICWORLD_HEADFILE

#include "XzPhysicBody.h"

struct Projection
{
	FLOAT m_fMin;
	FLOAT m_fMax;
};

class XzPhysicWorld:public XzObject
{
	static XzPhysicWorld* m_pSingleton;
public:
	
	static XzPhysicWorld* GetSingleton();
private:
	RECT			m_rtWorldAABB;
	D3DXVECTOR2		m_vc2Gravity;
	bool			m_bSEIRI;		//是否需要整理
	bool			m_bIsUsePhysic;
private:
	std::list<XzPhysicBody*> m_listaAtivityBody;
	std::list<XzPhysicBody*> m_listFixedBody;

	VOID _ReSeiri();//整理
	VOID _Collision(FLOAT dt);
	bool _CollisionOBBAndOBB(XzPhysicBody* body1,XzPhysicBody* body2);

	VOID GetAxis(D3DXVECTOR2* OBB,D3DXVECTOR2* axis);
	Projection GetProjection(D3DXVECTOR2* OBB,D3DXVECTOR2 axis);
	bool _CollisionSTA(D3DXVECTOR2* OBB,D3DXVECTOR2* OBB2);
public:
	XzPhysicWorld();
	~XzPhysicWorld();

	VOID SetGravity(D3DXVECTOR2 gravity);
	VOID SetAABB(RECT* rect);
	VOID ReSeiri();//整理
	
	VOID Update(FLOAT dt);
	VOID ChildUpdate(FLOAT dt);

	XzPhysicBody* CreatevAtivityBody(int id);
	XzPhysicBody* CreateFixedBody(int id);

	static XzPhysicBody* CreateFromXML(std::string file);
	static XzPhysicBody* CreateFromXML(TiXmlElement * ele,XzSprite * node);
};

#endif
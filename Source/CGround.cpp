#include "CGround.h"

CGround::CGround()
{

}
CGround::~CGround()
{

}
VOID CGround::ProcCollision(XzPhysicBody* body,char type)
{

}

CGround* CGround::Create(XzScene* scene)
{
	if (!scene)
	{
		return NULL;
	}
	CGround* m_tmp = new CGround;
	m_tmp->AutoRelease();
	scene->AddChild(m_tmp);
	XzPhysicWorld* m_physicworld = scene->GetPhysicWorld();
	if (m_physicworld)
	{
		XzPhysicBody* m_body = m_physicworld->CreateFixedBody(1);
		m_tmp->AddObject(m_body);
	}
	return m_tmp;
}
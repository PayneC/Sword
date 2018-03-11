#include "CXzEngine.h"

class CGround : public XzSprite
{
public:
	CGround();
	~CGround();
	virtual VOID ProcCollision(XzPhysicBody* body,char type);

	static CGround* Create(XzScene* scene);
};
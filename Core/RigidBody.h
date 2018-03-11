#ifndef XZ_RIGIDBODY_HEADFILE
#define XZ_RIGIDBODY_HEADFILE

#include "XzSprite.h"

typedef struct	tagHitStruct
{
	float	Value;
	char	flag;
}HITSTRUCT;//标记死亡不死亡用到的结构体类型

#define SWAP(X, Y) { t = List[X]; List[X] = List[Y]; List[Y] = t; }//碰撞矩形区域元素交换

class XzCollision
{
public:
    XzCollision();
    ~XzCollision();

    BOOL IsCollision(Sphere * _sphere, Line * _line);
    VOID _CollisionProcessInA(Sphere * _sphere, Line * _line);
    VOID _CollisionProcessInB(Sphere * _sphere, Line * _line);
    VOID _CollisionProcessInC(Sphere * _sphere, Line * _line);
    VOID _SpeedProcessInA(Sphere * _sphere, Line * _line);
    VOID _SpeedProcessInB(Sphere * _sphere, Line * _line);
    VOID _SpeedProcessInC(Sphere * _sphere, Line * _line);

    BOOL CollisionSphereAndSphere(Sphere * _sphere, Sphere * _sphere2);



    BOOL CollisionPixel(XzSprite * _rectangle, XzSprite * _rectangle2);
    VOID Sort4(HITSTRUCT* list);
    BOOL IsCollision(XzSprite * _rectangle, XzSprite * _rectangle2, RECT *_rect);
private:


};




#endif
#ifndef _XZ_SCENE_FILEHEAD
#define _XZ_SCENE_FILEHEAD

/*
 * @defgroup XzScene 类
 * @author  payne
 * @version 1.0
 * @date    2014.09
 * @{
 */

#include "XzNode.h"
#include "XzPhysicWorld.h"

class XzScene : public XzNode
{
private:
	D3DXVECTOR2 m_vc2SceneSize;
public:
    XzScene();
    ~XzScene();

/*
 * @name 函数接口
 * @{
 */

/*
 *	创建场景
 *  @param [in] width 场景的宽度
 *  @param [in] height 场景的高度
 *  @return VOID
 */
	static XzScene* Create(INT width, INT height);
/*
 *	通过XML文档创建一个场景
 *  @param [in] file XML文件名
 *  @return XzScene 场景的指针
 */
	static XzScene*CreateFromXML(std::string file);
/*
 *	通过XML文档创建一个场景
 *  @param [in] ele XML节点
 *  @param [in] node 要挂载到的父节点指针（没有则填NULL）
 *  @return XzScene 场景的指针
 */
	static XzScene*CreateFromXML(TiXmlElement * ele,XzNode * node);
/*
 *	获取场景的尺寸
 *  @return D3DXVECTOR2
 */	
	const D3DXVECTOR2& GetSceneSize();

	//VOID SetIsVisible(BOOL boolean);
};

#endif
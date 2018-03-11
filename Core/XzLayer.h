#ifndef _XZ_LAYER_FILEHEAD
#define _XZ_LAYER_FILEHEAD

/*
 * @defgroup XzLayer 类
 * @author  payne
 * @version 1.0
 * @date    2014.09
 * @{
 */

#include "XzNode.h"

class XzLayer : public XzNode
{
public:
    XzLayer();
    ~XzLayer();
/*
 * @name 函数接口
 * @{
 */

/*
 *	增加子节点
 *  @param [in] node 要增加的子节点的指针
 *  @param [in] tag	 该子节点在其中的索引
 *  @return VOID
 */
	virtual VOID AddChild(XzNode * node,UINT tag = 0);

/*
 *	创建一个层
 *  @param [in] depth 要创建的层的深度值
 *  @param [in] getMsg 创建的层是否接受鼠标点击的消息
 *  @return XzLayer 层的指针
 */
	static XzLayer* Create(FLOAT depth,BOOL getMsg);

/*
 *	通过XML文档创建一个层
 *  @param [in] file XML文件名
 *  @return XzLayer 层的指针
 */
	static XzLayer* CreateFromXML(std::string file);
	
/*
 *	通过XML文档创建一个层
 *  @param [in] ele XML节点
 *  @param [in] node 要挂载到的父节点指针（没有则填NULL）
 *  @return XzLayer 层的指针
 */
	static XzLayer* CreateFromXML(TiXmlElement * ele,XzNode * node);
};

#endif
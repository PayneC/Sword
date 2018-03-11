#ifndef _XZ_LAYER_FILEHEAD
#define _XZ_LAYER_FILEHEAD

/*
 * @defgroup XzLayer ��
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
 * @name �����ӿ�
 * @{
 */

/*
 *	�����ӽڵ�
 *  @param [in] node Ҫ���ӵ��ӽڵ��ָ��
 *  @param [in] tag	 ���ӽڵ������е�����
 *  @return VOID
 */
	virtual VOID AddChild(XzNode * node,UINT tag = 0);

/*
 *	����һ����
 *  @param [in] depth Ҫ�����Ĳ�����ֵ
 *  @param [in] getMsg �����Ĳ��Ƿ�������������Ϣ
 *  @return XzLayer ���ָ��
 */
	static XzLayer* Create(FLOAT depth,BOOL getMsg);

/*
 *	ͨ��XML�ĵ�����һ����
 *  @param [in] file XML�ļ���
 *  @return XzLayer ���ָ��
 */
	static XzLayer* CreateFromXML(std::string file);
	
/*
 *	ͨ��XML�ĵ�����һ����
 *  @param [in] ele XML�ڵ�
 *  @param [in] node Ҫ���ص��ĸ��ڵ�ָ�루û������NULL��
 *  @return XzLayer ���ָ��
 */
	static XzLayer* CreateFromXML(TiXmlElement * ele,XzNode * node);
};

#endif
#ifndef _XZ_SCENE_FILEHEAD
#define _XZ_SCENE_FILEHEAD

/*
 * @defgroup XzScene ��
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
 * @name �����ӿ�
 * @{
 */

/*
 *	��������
 *  @param [in] width �����Ŀ��
 *  @param [in] height �����ĸ߶�
 *  @return VOID
 */
	static XzScene* Create(INT width, INT height);
/*
 *	ͨ��XML�ĵ�����һ������
 *  @param [in] file XML�ļ���
 *  @return XzScene ������ָ��
 */
	static XzScene*CreateFromXML(std::string file);
/*
 *	ͨ��XML�ĵ�����һ������
 *  @param [in] ele XML�ڵ�
 *  @param [in] node Ҫ���ص��ĸ��ڵ�ָ�루û������NULL��
 *  @return XzScene ������ָ��
 */
	static XzScene*CreateFromXML(TiXmlElement * ele,XzNode * node);
/*
 *	��ȡ�����ĳߴ�
 *  @return D3DXVECTOR2
 */	
	const D3DXVECTOR2& GetSceneSize();

	//VOID SetIsVisible(BOOL boolean);
};

#endif
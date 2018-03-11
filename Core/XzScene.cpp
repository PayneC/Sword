#include "XzScene.h"

XzScene* XzScene::Create(INT width, INT height)
{
	XzScene* m_tmp = new XzScene;

	m_tmp->m_vc2SceneSize.x = (FLOAT)width;
	m_tmp->m_vc2SceneSize.y = (FLOAT)height;
	m_tmp->AutoRelease();
	return m_tmp;
}

XzScene* XzScene::CreateFromXML(std::string file)
{
	return NULL;
}

XzScene* XzScene::CreateFromXML(TiXmlElement * ele,XzNode * node)
{
	if (ele)
	{
		INT width = 0;
		INT height = 0;
		ele->Attribute("width",&width);							//读取场景宽
		ele->Attribute("height",&height);						//读取场景高	
		XzScene* m_pScene = XzScene::Create(width,height);		//创建场景	
		if(node)
			node->AddChild(m_pScene);
		return m_pScene;
	}
	return NULL;
}

XzScene::XzScene()
	:m_vc2SceneSize(0,0)
{
}

XzScene::~XzScene()
{
}

const D3DXVECTOR2& XzScene::GetSceneSize()
{
	return m_vc2SceneSize;
}
//
//VOID XzScene::SetIsVisible(BOOL boolean)
//{
//	m_bIsVisible = boolean;
//	m_endNode = m_mmpNode.end();
//	for (m_iterNode = m_mmpNode.begin();m_iterNode != m_endNode;++m_iterNode)
//	{
//		m_iterNode->second->SetIsVisible(boolean);
//	}
//}
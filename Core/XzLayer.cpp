#include "XzLayer.h"
#include "..\core\XzMessage.h"
XzLayer::XzLayer()
{
}

XzLayer::~XzLayer()
{
}

XzLayer* XzLayer::Create(FLOAT depth,BOOL getMsg)
{
	XzLayer* m_tmp = new XzLayer;
	m_tmp->SetLocalDepth(depth);
	m_tmp->AutoRelease();
	if (getMsg)
	{
		XzMessage::GetSingleton()-> ListenMouse(m_tmp);
	}
	return m_tmp;
}

VOID XzLayer::AddChild(XzNode * node,UINT tag)
{
	XzNode::AddChild(node,tag);
	node->SetGlobalDepth(m_vc3GlobalPosition.z);
}

XzLayer* XzLayer::CreateFromXML(std::string file)
{
	return NULL;
}

XzLayer* XzLayer::CreateFromXML(TiXmlElement * ele,XzNode * node)
{
	if(ele)
	{
		DOUBLE depth = 0;
		INT tag = 0;
		INT camera = 0;
		INT getmsg = 0;

		ele->Attribute("depth",&depth);								//��ȡ������
		ele->Attribute("camera",&camera);							//�����Ƿ�ʹ�����
		ele->Attribute("getmsg",&getmsg);							//�Ƿ�����������Ϣ
		XzLayer* m_pLayer = XzLayer::Create((FLOAT)depth,getmsg);	//������
		if(node)
			node->AddChild(m_pLayer,(UINT)tag);						//���뵽������
		m_pLayer->SetIsUseCamera(camera);							//�����Ƿ�ʹ�����
		return m_pLayer;
	}
	return NULL;
}
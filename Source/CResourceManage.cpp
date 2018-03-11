#include "CResourceManage.h"
#include "CWindow.h"
#include "CMonster.h"
CResourceManage* CResourceManage::m_pSingleton = 0;

CResourceManage* CResourceManage::GetSingleton()
{
	if (!m_pSingleton)
	{
		static CResourceManage m_singleton;
		m_pSingleton = &m_singleton;
	}
	return m_pSingleton;
}
CResourceManage::CResourceManage()
{

}
CResourceManage::~CResourceManage()
{

}

XzScene* CResourceManage::LoadFromXML(std::string file)
{
	TiXmlDocument m_doc(file.c_str());
	if (m_doc.LoadFile())
	{
		TiXmlElement * m_scene = m_doc.FirstChildElement("scene");
		TiXmlElement * m_layer;
		TiXmlElement * m_sprite;
		TiXmlElement * m_buttonSprite;
		TiXmlElement * m_arraySprite;
		TiXmlElement * m_window;
		TiXmlElement * m_monster;

		XzScene* m_pScene = XzScene::CreateFromXML(m_scene,NULL);
		XzLayer* m_pLayer;
		XzSprite* m_pSprite;
		XzButtonSprite* m_pButtonSprite;
		XzFrameArraySprite* m_pFrameArraySprite;
		CWindow* m_pWindow;
		CMonster* m_pMonster;

		m_layer = m_scene->FirstChildElement("layer");
		while(m_layer)
		{
			m_pLayer = XzLayer::CreateFromXML(m_layer,m_pScene);
			m_sprite = m_layer->FirstChildElement("sprite");
			while(m_sprite)
			{
				m_pSprite = XzSprite::CreateFromXML(m_sprite,m_pLayer);
				m_sprite = m_sprite->NextSiblingElement("sprite");
			}

			m_buttonSprite = m_layer->FirstChildElement("buttonsprite");
			while(m_buttonSprite)
			{
				m_pButtonSprite = XzButtonSprite::CreateFromXML(m_buttonSprite,m_pLayer);
				m_buttonSprite = m_buttonSprite->NextSiblingElement("buttonsprite");
			}

			m_arraySprite = m_layer->FirstChildElement("arrsprite");
			while(m_arraySprite)
			{
				m_pFrameArraySprite = XzFrameArraySprite::CreateFromXML(m_arraySprite,m_pLayer);
				m_arraySprite = m_arraySprite->NextSiblingElement("arrsprite");
			}
			m_layer = m_layer->NextSiblingElement("layer");
		}

		m_window = m_scene->FirstChildElement("window");
		while(m_window)
		{
			m_pWindow = CWindow::CreateFromXML(m_window,m_pScene);
			m_window = m_window->NextSiblingElement("window");
		}

		m_monster = m_scene->FirstChildElement("monster");
		while(m_monster)
		{
			m_pMonster = CMonster::CreateFromXML(m_monster,m_pScene);
			m_monster = m_monster->NextSiblingElement("monster");
		}
		return m_pScene;
	}
	 return NULL;
}

XzScene* CResourceManage::LoadScene(std::string file)
{
	TiXmlDocument m_doc(file.c_str());
	if (m_doc.LoadFile())
	{
		TiXmlElement * m_scene = m_doc.FirstChildElement("scene");	
		TiXmlElement * m_layer;	
		XzScene* m_pScene = NULL;
		if (m_scene)
		{
			INT width  = 0,height = 0;
			m_scene->Attribute("width",&width);				//读取场景宽
			m_scene->Attribute("height",&height);			//读取场景高	
			m_pScene = XzScene::Create(width,height);		//创建场景
			m_layer = m_scene->FirstChildElement("layer");	
			LoadLayer(m_layer,m_pScene);					//加载场景下的层
			return m_pScene;
		}
	}
	return NULL;
}
VOID CResourceManage::LoadLayer(TiXmlElement * ele,XzScene * node)
{
	TiXmlElement * child;
	XzLayer* m_pLayer = NULL;
	DOUBLE depth = 0;
	INT    camera = 0,tag=0,getmsg =0;
	while(ele)
	{
		ele->Attribute("depth",&depth);								//读取层的深度
		ele->Attribute("camera",&camera);							//设置是否使用相机
		ele->Attribute("getmsg",&getmsg);							//
		m_pLayer = XzLayer::Create((FLOAT)depth,getmsg);			//创建层	
		node->AddChild(m_pLayer,(UINT)tag);							//加入到父场景
		m_pLayer->SetIsUseCamera(camera);							//设置是否使用相机
		if (child = ele->FirstChildElement("sprite"))				//判断是否存在普通精灵
		{
			LoadSprite(child,m_pLayer,"sprite");					//加载普通精灵
		}
		if (child = ele->FirstChildElement("arrsprite"))				//判断是否存在图片组精灵
		{
			LoadArrSprite(child,m_pLayer,"arrsprite");				//加载普通图片组精灵
		}
		if (child = ele->FirstChildElement("buttonsprite"))			//判断是否存在按钮精灵
		{
			LoadButtonSprite(child,m_pLayer,"buttonsprite");		//加载按钮精灵
		}
		ele = ele->NextSiblingElement("layer");						//下一个layer
	}
}
VOID CResourceManage::LoadSprite(TiXmlElement * ele,XzNode * node,const char* _value)
{
	TiXmlElement * child;
	XzSprite* m_pSprite = NULL;
	double x = 0,y = 0,ratote = 0,scaleX = 1,scaleY = 1;
	INT tag = 0;
	while(ele)
	{
		ele->Attribute("x",&x);										//读取位置x
		ele->Attribute("y",&y);										//读取位置y
		ele->Attribute("scaleX",&scaleX);							//读取缩放x
		ele->Attribute("scaleY",&scaleY);							//读取缩放y
		ele->Attribute("ratote",&ratote);							//读取选择
		ele->Attribute("tag",&tag);									//读取标签
		m_pSprite = XzSprite::Create();								//创建精灵
		node->AddChild(m_pSprite,(UINT)tag);							//加入到父节点
		m_pSprite->SetGlobalPos((FLOAT)x,(FLOAT)y);
		m_pSprite->SetGlobalRatoteZ((FLOAT)ratote);					
		m_pSprite->SetGlobalScale((FLOAT)scaleX,(FLOAT)scaleY);		
		if (child = ele->FirstChildElement("sprite"))				//判断是否存在普通精灵
		{
			LoadSprite(child,m_pSprite,"sprite");					//加载普通精灵
		}
		if (child = ele->FirstChildElement("arrsprite"))				//判断是否存在图片组精
		{
			LoadArrSprite(child,m_pSprite,"arrsprite");				//加载普通图片组精灵
		}
		if (child = ele->FirstChildElement("buttonsprite"))			//判断是否存在按钮精灵
		{
			LoadButtonSprite(child,m_pSprite,"buttonsprite");		//加载按钮精灵
		}
		if(child = ele->FirstChildElement("texture"))				//判断是否存在图片
		{
			LoadTexture(child,m_pSprite,"texture");					//加载图片
		}
		if (child = ele->FirstChildElement("animation"))				//判断是否存在动画
		{
			LoadAnimation(child,m_pSprite,"animation");				//加载动画
		}
		if (child = ele->FirstChildElement("body"))					//判断是否存在body
		{
			LoadPhysicBody(child,m_pSprite,"body");					//加载body
		}
		ele = ele->NextSiblingElement(_value);
	}
}
VOID CResourceManage::LoadArrSprite(TiXmlElement * ele,XzNode * node,const char* _value)
{
	TiXmlElement * child;
	XzFrameArraySprite* m_pSprite = NULL;
	double x = 0,y = 0,ratote = 0,scaleX = 1,scaleY = 1;
	INT tag = 0;
	while(ele)
	{
		ele->Attribute("x",&x);										//读取位置x
		ele->Attribute("y",&y);										//读取位置y
		ele->Attribute("scaleX",&scaleX);							//读取缩放x
		ele->Attribute("scaleY",&scaleY);							//读取缩放y
		ele->Attribute("ratote",&ratote);							//读取选择
		ele->Attribute("tag",&tag);									//读取标签
		m_pSprite = XzFrameArraySprite::Create();					//创建精灵
		node->AddChild(m_pSprite,(UINT)tag);							//加入到父节点
		m_pSprite->SetGlobalPos((FLOAT)x,(FLOAT)y);
		m_pSprite->SetGlobalRatoteZ((FLOAT)ratote);					
		m_pSprite->SetGlobalScale((FLOAT)scaleX,(FLOAT)scaleY);		
		if (child = ele->FirstChildElement("sprite"))				//判断是否存在普通精灵
		{
			LoadSprite(child,m_pSprite,"sprite");					//加载普通精灵
		}
		if (child = ele->FirstChildElement("arrsprite"))				//判断是否存在图片组精
		{
			LoadArrSprite(child,m_pSprite,"arrsprite");				//加载普通图片组精灵
		}
		if (child = ele->FirstChildElement("buttonsprite"))			//判断是否存在按钮精灵
		{
			LoadButtonSprite(child,m_pSprite,"buttonsprite");		//加载按钮精灵
		}
		if(child = ele->FirstChildElement("texture"))				//判断是否存在图片
		{
			LoadTexture(child,m_pSprite,"texture");					//加载图片
		}
		if (child = ele->FirstChildElement("animation"))				//判断是否存在动画
		{
			LoadAnimation(child,m_pSprite,"animation");				//加载动画
		}
		if (child = ele->FirstChildElement("body"))					//判断是否存在body
		{
			LoadPhysicBody(child,m_pSprite,"body");					//加载body
		}
		ele = ele->NextSiblingElement(_value);
	}
}
VOID CResourceManage::LoadButtonSprite(TiXmlElement * ele,XzNode * node,const char* _value)
{
	TiXmlElement * child;
	XzButtonSprite* m_pSprite = NULL;
	double x = 0,y = 0,ratote = 0,scaleX = 1,scaleY = 1;
	INT tag = 0,id = 0,msg = 0,Fixed=1;
	while(ele)
	{
		ele->Attribute("x",&x);										//读取位置x
		ele->Attribute("y",&y);										//读取位置y
		ele->Attribute("scaleX",&scaleX);							//读取缩放x
		ele->Attribute("scaleY",&scaleY);							//读取缩放y
		ele->Attribute("ratote",&ratote);							//读取选择
		ele->Attribute("tag",&tag);									//读取标签
		ele->Attribute("id",&id);									//读取按钮ID
		ele->Attribute("msg",&msg);									//读取消息内容
		ele->Attribute("Fixed",&Fixed);
		m_pSprite = XzButtonSprite::Create();						//创建精灵
		node->AddChild(m_pSprite,(UINT)tag);							//加入到父节点
		m_pSprite->SetGlobalPos((FLOAT)x,(FLOAT)y);
		m_pSprite->SetGlobalRatoteZ((FLOAT)ratote);					
		m_pSprite->SetGlobalScale((FLOAT)scaleX,(FLOAT)scaleY);	
		m_pSprite->SetID(id);
		m_pSprite->SetMessage(msg);
		m_pSprite->SetIsFixed(Fixed);
		if (child = ele->FirstChildElement("sprite"))				//判断是否存在普通精灵
		{
			LoadSprite(child,m_pSprite,"sprite");					//加载普通精灵
		}
		if (child = ele->FirstChildElement("arrsprite"))				//判断是否存在图片组精
		{
			LoadArrSprite(child,m_pSprite,"arrsprite");				//加载普通图片组精灵
		}
		if (child = ele->FirstChildElement("buttonsprite"))			//判断是否存在按钮精灵
		{
			LoadButtonSprite(child,m_pSprite,"buttonsprite");		//加载按钮精灵
		}
		if(child = ele->FirstChildElement("texture"))				//判断是否存在图片
		{
			LoadTexture(child,m_pSprite,"texture");					//加载图片
		}
		if (child = ele->FirstChildElement("animation"))				//判断是否存在动画
		{
			LoadAnimation(child,m_pSprite,"animation");				//加载动画
		}
		if (child = ele->FirstChildElement("body"))					//判断是否存在body
		{
			LoadPhysicBody(child,m_pSprite,"body");					//加载body
		}
		ele = ele->NextSiblingElement(_value);
	}
}
VOID CResourceManage::LoadPhysicBody(TiXmlElement * ele,XzSprite * node,const char* _value)
{
	INT type,id;
	ele->Attribute("type",&type);
	ele->Attribute("id",&id);
	XzPhysicBody* m_pBody = XzPhysicWorld::GetSingleton()->CreateFixedBody(id);
	node->AddPhysicBody(m_pBody);
}
VOID CResourceManage::LoadTexture(TiXmlElement * ele,XzSprite * node,const char* _value)
{
	XzTexture* m_pTexture = NULL;
	INT tag;
	while(ele)
	{
		m_pTexture = XzTexture::Create(XzSystem::CU_A2U(ele->Attribute("file")));
		ele->Attribute("tag",&tag);
		if (tag < 0)
			tag = -tag;
		node->AddTexture(m_pTexture,tag);
		ele = ele->NextSiblingElement("texture");
	}
}
VOID CResourceManage::LoadAnimation(TiXmlElement * ele,XzSprite * node,const char* _value)
{
	TiXmlElement * child;
	XzAnimation* m_pAnimation = NULL;
	INT tag,row = 0,col = 0,begin = 0,end = 0, frame;
	ele->Attribute("row",&row);			
	ele->Attribute("col",&col);			
	ele->Attribute("begin",&begin);
	ele->Attribute("end",&end);
	ele->Attribute("frame",&frame);
	while(ele)
	{
		if (row)
		{
			m_pAnimation = XzAnimation::Create(XzSystem::CU_A2U(ele->Attribute("file")),(UINT)row,(UINT)col,(UINT)begin,(UINT)end);
			m_pAnimation->SetFPS(frame);
			ele->Attribute("tag",&tag);
			if (tag < 0)
				tag = -tag;
			node->AddTexture(m_pAnimation,tag);
		}
		child = ele->FirstChildElement("texture");
		while(child)
		{
			XzTexture* m_pTexture = XzTexture::Create(XzSystem::CU_A2U(ele->Attribute("file")));
			m_pAnimation->AddFrame(m_pTexture);
			child = child->NextSiblingElement("texture");
		}
		ele = ele->NextSiblingElement("animation");
	}
}
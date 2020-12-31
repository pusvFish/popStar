#include "GameScene.h"
#include "ui/CocosGUI.h"

using namespace ui;
CGameScene* CGameScene::m_pInstance = nullptr;
CGameScene::CGameScene()
{
}

CGameScene::~CGameScene()
{
}

CGameScene* CGameScene::getInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = CGameScene::create();
	}
	return m_pInstance;
}

void CGameScene::destroy()
{
	m_pInstance = nullptr;
}

bool CGameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	m_nLevel = 100;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* pBg = Sprite::create("image/game_bg.jpg");
	pBg->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(pBg);

	m_pStarMgr = CStarMgr::create();
	this->addChild(m_pStarMgr);
	m_pStarMgr->test(m_nLevel);

	Button* btnStart = Button::create("CloseNormal.png", "CloseNormal.png");
	btnStart->setPosition(Vec2(160, 450));
	this->addChild(btnStart);
	btnStart->addClickEventListener(CC_CALLBACK_1(CGameScene::onBtnClick, this));

	return true;
}

void CGameScene::onBtnClick(Ref* pSender)
{
	CCLOG("onBtnClick!");
	CGameScene::destroy();
	CGameScene* pGameScene = CGameScene::getInstance();
	Director::getInstance()->replaceScene(pGameScene);
}

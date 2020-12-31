#include "Star.h"
#include "GameScene.h"

CStar::CStar()
:m_nRow(0)
, m_nCol(0)
, m_bSearch(false)
{
}

CStar::~CStar()
{
}

CStar* CStar::createWithData(int nColor)
{
	CStar* pStar = new CStar();
	if (pStar&&pStar->initWithData(nColor))
	{
		pStar->autorelease();
		return pStar;
	}
	CC_SAFE_DELETE(pStar);
	return nullptr;
}

bool CStar::initWithData(int nType)
{
	if (!Node::init())
	{
		return false;
	}
	m_nType = nType;
	char szName[32] = {};
	sprintf_s(szName, "image/star%d.png", nType);
	m_pImage = Sprite::create(szName);
	this->addChild(m_pImage);

	m_pBox = Sprite::create("image/box.png");
	this->addChild(m_pBox);
	m_pBox->setVisible(false);
	return true;
}

Size CStar::getSize()
{
	return m_pImage->getContentSize();
}

void CStar::setSearch(bool bSearch)
{
	m_bSearch = bSearch;
	m_pBox->setVisible(bSearch);
}

void CStar::fall(int nCount)
{
	if (nCount <= 0)
	{
		return;
	}
	m_nRow -= nCount;
	float tileHeight = m_pImage->getContentSize().height;
	MoveBy* pMoveBy = MoveBy::create(3, Vec2(0, -nCount * tileHeight));
	CallFunc* pFunc = CallFunc::create(CC_CALLBACK_0(CStar::fallFinish, this));
	Sequence* pSeq = Sequence::createWithTwoActions(pMoveBy, pFunc);
	this->runAction(pSeq);
}

void CStar::moveLeft(int nCount)
{
	if (nCount <= 0)
	{
		return;
	}
	m_nCol -= nCount;
	float tileWidth = m_pImage->getContentSize().width;
	MoveBy* pMoveBy = MoveBy::create(5, Vec2(-nCount * tileWidth, 0));
	this->runAction(pMoveBy);
}

void CStar::fallFinish()
{
	_eventDispatcher->dispatchCustomEvent("fallFinish");
	//CGameScene::getInstance()->getStarMgr()->setFallFinish();
}

#include "StarMgr.h"
#include "GameScene.h"

CStarMgr::CStarMgr()
{
	memset(m_arrStar, 0, sizeof(m_arrStar));
	m_bFalling = false;
}

CStarMgr::~CStarMgr()
{
}

bool CStarMgr::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->createStar();
	this->addTouchEvent();
// 	int nLevel = CGameScene::getInstance()->getLevel();
// 	CCLOG("nLevel = %d", nLevel);

	_eventDispatcher->addCustomEventListener("fallFinish", CC_CALLBACK_1(CStarMgr::finishCb, this));
	return true;
}

void CStarMgr::createStar()
{
	//两个for循环
	//保存在数组中
	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COL_SIZE; j++)
		{
			int nType = random() % 5 + 1;
			CStar* pStar = CStar::createWithData(nType);
			Size size = pStar->getSize();
			float fX = size.width*j + size.width / 2;
			float fY = size.height * i + size.height / 2;
			pStar->setPosition(fX, fY);
			this->addChild(pStar);
			m_arrStar[i][j] = pStar;
			pStar->setRow(i);
			pStar->setCol(j);
		}
	}

}

void CStarMgr::addTouchEvent()
{
	EventListenerTouchOneByOne* pListener = EventListenerTouchOneByOne::create();
	pListener->onTouchBegan = CC_CALLBACK_2(CStarMgr::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(pListener, this);
}

bool CStarMgr::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	if (m_bFalling)
	{
		return false;
	}
	Vec2 pos = this->convertTouchToNodeSpaceAR(pTouch);
	int nRow = pos.y / 40;
	int nCol = pos.x / 40;
	if (nRow < 0 || nRow >(ROW_SIZE - 1) || nCol < 0 || nCol >(COL_SIZE - 1))
	{
		return false;;
	}
	CStar* pStar = m_arrStar[nRow][nCol];
	if (!pStar)
	{
		return false;
	}
	m_VecSearch.clear();
	if (pStar->getSearch())
	{
		//消除
		bool bFall = (m_VecResult.size() > 0);
		for (CStar* pStar : m_VecResult)
		{
			m_arrStar[pStar->getRow()][pStar->getCol()] = nullptr;
			pStar->removeFromParent();
		}

		m_VecResult.clear();
		if (bFall)
		{
			this->fall();
			//this->moveLeft();
		}
		
		
	}
	else{
		for (CStar* pStar : m_VecResult)
		{
			pStar->setSearch(false);
		}
		m_VecResult.clear();
		//搜索
// 		m_VecSearch.push_back(pStar);
// 		m_VecResult.insert(pStar);
		this->search(pStar);
	}

	return true;
}

//void CStarMgr::search()
//{
//	while (m_VecSearch.size() > 0)
//	{
//		CStar* pStar = m_VecSearch[0];
//		int nRow = pStar->getRow();
//		int nCol = pStar->getCol();
//
//		//上
//		if (nRow < ROW_SIZE - 1)
//		{
//			CStar* pUp = m_arrStar[nRow + 1][nCol];
//			if (pUp && !pUp->getSearch() && pUp->getType() == pStar->getType())
//			{
//				m_VecSearch.push_back(pUp);
//				m_VecResult.push_back(pUp);
//			}
//		}
//		
//		
//		//下
//		if (nRow > 0)
//		{
//			CStar* pDown = m_arrStar[nRow - 1][nCol];
//			if (pDown && !pDown->getSearch() && pDown->getType() == pStar->getType())
//			{
//				m_VecSearch.push_back(pDown);
//				m_VecResult.push_back(pDown);
//			}
//		}
//		//左
//		if (nCol > 0)
//		{
//			CStar* pLeft = m_arrStar[nRow][nCol - 1];
//			if (pLeft && !pLeft->getSearch() && pLeft->getType() == pStar->getType())
//			{
//				m_VecSearch.push_back(pLeft);
//				m_VecResult.push_back(pLeft);
//			}
//		}
//		//右
//		if (nCol < COL_SIZE - 1)
//		{
//			CStar* pRight = m_arrStar[nRow][nCol + 1];
//			if (pRight && !pRight->getSearch() && pRight->getType() == pStar->getType())
//			{
//				m_VecSearch.push_back(pRight);
//				m_VecResult.push_back(pRight);
//			}
//		}
//		pStar->setSearch(true);
//		m_VecSearch.erase(m_VecSearch.begin());
//	}
//
//	if (m_VecResult.size() == 1)
//	{
//		m_VecResult[0]->setSearch(false);
//		m_VecResult.clear();
//	}
//}

void CStarMgr::search()
{
	while (m_VecSearch.size() > 0)
	{
		CStar* pStar = m_VecSearch[0];
		int nRow = pStar->getRow();
		int nCol = pStar->getCol();
		
		bool arrCondition[4] = { nRow < ROW_SIZE - 1, nRow > 0, nCol > 0, nCol < COL_SIZE - 1 };
		int arrRowIndex[4] = { nRow + 1, nRow - 1, nRow, nRow };
		int arrColIndex[4] = { nCol, nCol, nCol - 1, nCol + 1 };
		for (int i = 0; i < 4; i++)
		{
			if (arrCondition[i])
			{
				this->checkSame(pStar, arrRowIndex[i], arrColIndex[i]);
			}
		}

// 		//上
// 		if (nRow < ROW_SIZE - 1)
// 		{
// 			this->checkSame(pStar, nRow + 1, nCol);
// 		}
// 		//下
// 		if (nRow > 0)
// 		{
// 			this->checkSame(pStar, nRow - 1, nCol);
// 		}
// 		//左
// 		if (nCol > 0)
// 		{
// 			this->checkSame(pStar, nRow, nCol - 1);
// 		}
// 		//右
// 		if (nCol < COL_SIZE - 1)
// 		{
// 			this->checkSame(pStar, nRow, nCol + 1);
// 		}
		pStar->setSearch(true);
		m_VecSearch.erase(m_VecSearch.begin());
	}
	if (m_VecResult.size() == 1)
	{
		for (CStar* pStar : m_VecResult){
			pStar->setSearch(false);
		}
		m_VecResult.clear();
	}
}

void CStarMgr::search(CStar* pStar)
{
	m_VecResult.insert(pStar);
	pStar->setSearch(true);
	int nRow = pStar->getRow();
	int nCol = pStar->getCol();
	//上下左右四个方向的条件
	bool arrCondition[4] = { nRow < ROW_SIZE - 1, nRow > 0, nCol > 0, nCol < COL_SIZE - 1 };
	//上下左右四个方向的行列索引
	int arrRowIndex[4] = { nRow + 1, nRow - 1, nRow, nRow };
	int arrColIndex[4] = { nCol, nCol, nCol - 1, nCol + 1 };
	for (int i = 0; i < 4; i++)
	{
		if (arrCondition[i])
		{
			int nRowDest = arrRowIndex[i];
			int nColDest = arrColIndex[i];
			CStar* pStarDest = m_arrStar[nRowDest][nColDest];
			if (pStarDest && !pStarDest->getSearch() && pStarDest->getType() == pStar->getType())
			{
				m_VecResult.insert(pStarDest);
				this->search(pStarDest);
			}
		}
	}
	if (m_VecResult.size() == 1)
	{
		for (CStar* pStar : m_VecResult){
			pStar->setSearch(false);
		}
		m_VecResult.clear();
	}
}

void CStarMgr::checkSame(CStar* pSrcStar, int nRowDest, int nColDest)
{
	CStar* pStar = m_arrStar[nRowDest][nColDest];
	if (pStar && !pStar->getSearch() && pSrcStar->getType() == pStar->getType())
	{
		m_VecSearch.push_back(pStar);
		m_VecResult.insert(pStar);
		//m_VecResult.push_back(pStar);
	}
}

void CStarMgr::fall()
{
	for (int i = 0; i < COL_SIZE; i++)
	{
		//一列遍历结束
		int nCount = 0;
		for (int j = 0; j < ROW_SIZE; j++)
		{
			if (!m_arrStar[j][i])
			{
				//统计j以下到空格数
				nCount++;
			}
			else{
				if (nCount > 0)
				{
					//掉落nCount格
					m_bFalling = true;
					m_arrStar[j][i]->fall(nCount);
					m_arrStar[j - nCount][i] = m_arrStar[j][i];
					m_arrStar[j][i] = nullptr;
				}
			}
		}
	}
}

void CStarMgr::moveLeft()
{
	int nCount = 0;
	for (int i = 0; i < COL_SIZE; i++)
	{
		if (!m_arrStar[0][i])
		{
			nCount++;
		}
		else{
			if (nCount > 0)
			{
				for (int j = 0; j < ROW_SIZE; j++)
				{
					if (m_arrStar[j][i])
					{
						m_arrStar[j][i]->moveLeft(nCount);
						m_arrStar[j][i - nCount] = m_arrStar[j][i];
						m_arrStar[j][i] = nullptr;
					}

				}
			}
		}
	}
}

void CStarMgr::setFallFinish()
{
	if (m_bFalling)
	{
		this->moveLeft();
		m_bFalling = false;
	}
}

void CStarMgr::test(int nLevel)
{
	CCLOG("nLevel = %d", nLevel);
}

void CStarMgr::finishCb(EventCustom* pEvent)
{
	if (m_bFalling)
	{
		this->moveLeft();
		m_bFalling = false;
	}
}

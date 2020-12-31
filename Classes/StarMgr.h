#ifndef __StarMgr_H__
#define __StarMgr_H__

#include "Star.h"
using namespace std;

const int ROW_SIZE = 10;
const int COL_SIZE = 8;
class CStarMgr : public Node
{
public:
	CStarMgr();
	~CStarMgr();

	virtual bool init();
	void test(int nLevel);
	bool onTouchBegan(Touch* pTouch, Event* pEvent);
	void setFallFinish();
	void finishCb(EventCustom* pEvent);
	CREATE_FUNC(CStarMgr);
	CC_SYNTHESIZE_READONLY(bool, m_bFalling, Falling);
private:
	void search(CStar* pStar);
	void fall();
	void moveLeft();
	void createStar();
	void addTouchEvent();
	void search();
	//1:要比较到星星
	//2，3:另一个星星到索引
	void checkSame(CStar* pSrcStar, int nRowDest, int nColDest);
private:
	CStar* m_arrStar[ROW_SIZE][COL_SIZE];
	vector<CStar*> m_VecSearch;
	set<CStar*> m_VecResult;
};


#endif
#ifndef __Star_H__
#define __Star_H__

#include "cocos2d.h"
USING_NS_CC;

enum
{
	E_TYPE_NONE,
	E_TYPE_YELLOW,
	E_TYPE_BLUE,
	E_TYPE_RED,
	E_TYPE_PURPLE,
	E_TYPE_GREEN
};

class CStar : public Node
{
public:
	CStar();
	~CStar();

	bool initWithData(int nType);
	static CStar* createWithData(int nType);
	Size getSize();
	void setSearch(bool bSearch);
	void fall(int nCount);
	void moveLeft(int nCount);
	CC_SYNTHESIZE_READONLY(Sprite*, m_pImage, Image);
	CC_SYNTHESIZE_READONLY(Sprite*, m_pBox, Box);
	CC_SYNTHESIZE_READONLY(int, m_nType, Type);
	CC_SYNTHESIZE(int, m_nRow, Row);
	CC_SYNTHESIZE(int, m_nCol, Col);
	CC_SYNTHESIZE_READONLY(bool, m_bSearch, Search);
private:
	void fallFinish();
};

#endif
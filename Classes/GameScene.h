#ifndef __GameScene_H__
#define __GameScene_H__

#include "cocos2d.h"
#include "StarMgr.h"
USING_NS_CC;

class CGameScene : public Scene
{
public:
	CGameScene();
	~CGameScene();

	static CGameScene* getInstance();
	static void destroy();
	virtual bool init();
	CREATE_FUNC(CGameScene);

	CC_SYNTHESIZE_READONLY(CStarMgr*, m_pStarMgr, StarMgr);
	CC_SYNTHESIZE_READONLY(int, m_nLevel, Level);
private:
	void onBtnClick(Ref* pSender);
private:
	static CGameScene* m_pInstance;
};


#endif
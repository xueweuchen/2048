#ifndef _LEADER_BOARD_LAYOUT_H_
#define _LEADER_BOARD_LAYOUT_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "LeaderData.h"
#include "ItemLabel.h"
#include "HelloWorldScene.h"

class LeaderBoardLayout: public cocos2d::ui::Layout
{
public:
	LeaderBoardLayout(void);
	~LeaderBoardLayout(void);
	static LeaderBoardLayout* create(std::vector<recordItem> &leaderBoardTen);
	virtual bool initWithVector(std::vector<recordItem> &leaderBoardTen);
private:
	void refreshCallback(cocos2d::CCObject *pSender, cocos2d::ui::TouchEventType type);
	void cancelCallback(cocos2d::CCObject *pSender, cocos2d::ui::TouchEventType type);
	void exitCallback(cocos2d::CCObject *pSender, cocos2d::ui::TouchEventType type);
};


#endif


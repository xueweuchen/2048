#ifndef _WINFAIL_LAYOUT_H_
#define _WINFAIL_LAYOUT_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "LeaderData.h"
#include "ItemLabel.h"
#include "HelloWorldScene.h"

class WinFailLayout: public cocos2d::ui::Layout
{
public:
	WinFailLayout(void);
	~WinFailLayout(void);
	static WinFailLayout* create(int score, int bestScore, int winOrFail);
	virtual bool initWithScore(int score, int bestScore, int winOrFail);
private:
	void refreshCallback(cocos2d::CCObject *pSender, cocos2d::ui::TouchEventType type);
	void cancelCallback(cocos2d::CCObject *pSender, cocos2d::ui::TouchEventType type);
	void exitCallback(cocos2d::CCObject *pSender, cocos2d::ui::TouchEventType type);
};


#endif


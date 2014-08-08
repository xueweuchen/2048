#include "LeaderBoardLayout.h"


LeaderBoardLayout::LeaderBoardLayout(void)
{
}


LeaderBoardLayout::~LeaderBoardLayout(void)
{
}

LeaderBoardLayout* LeaderBoardLayout::create(std::vector<recordItem> &leaderBoardTen)
{
	LeaderBoardLayout* layout = new LeaderBoardLayout();
	if (layout && layout->init())
	{
		layout->autorelease();
		layout->initWithVector(leaderBoardTen);
		return layout;
	}
	CC_SAFE_DELETE(layout);
	return NULL;
}

void LeaderBoardLayout::refreshCallback(cocos2d::CCObject *pSender, cocos2d::ui::TouchEventType type)
{
	cocos2d::Director::getInstance()->replaceScene(HelloWorld::createScene());
}

void LeaderBoardLayout::cancelCallback(cocos2d::CCObject *pSender, cocos2d::ui::TouchEventType type)
{
	this->getParent()->removeChild(this);
}

void LeaderBoardLayout::exitCallback(cocos2d::CCObject *pSender, cocos2d::ui::TouchEventType type)
{
	cocos2d::Director::getInstance()->end();
}

bool LeaderBoardLayout::initWithVector(std::vector<recordItem> &leaderBoardTen)
{
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	this->setTouchEnabled(true);
	this->setBackGroundColor(cocos2d::Color3B(0, 130, 140));
	this->setBackGroundColorOpacity(128);
	this->setBackGroundColorType(cocos2d::ui::LAYOUT_COLOR_SOLID);  
	this->setSize(visibleSize);
	this->setPosition(cocos2d::Point(0,0));
	this->setLayoutType(cocos2d::ui::LAYOUT_LINEAR_VERTICAL);

	ItemLabel* title = ItemLabel::create(60,
		"LEADER BOARD",
		"leader_title.png",
		cocos2d::Size(visibleSize.width/2, visibleSize.height/6));
	title->setTouchEnabled(false);

	cocos2d::ui::LinearLayoutParameter* titleParam = cocos2d::ui::LinearLayoutParameter::create();
	titleParam->setGravity(cocos2d::ui::LINEAR_GRAVITY_CENTER_HORIZONTAL);
	titleParam->setMargin(cocos2d::ui::Margin(0, visibleSize.height/40, 0, visibleSize.height/40));
	title->setLayoutParameter(titleParam);
	this->addChild(title);

	cocos2d::ui::ListView* lv = cocos2d::ui::ListView::create();
	cocos2d::ui::LinearLayoutParameter* listParam = cocos2d::ui::LinearLayoutParameter::create();
	listParam->setGravity(cocos2d::ui::LINEAR_GRAVITY_CENTER_HORIZONTAL);
	lv->setLayoutParameter(listParam);
	lv->setTouchEnabled(true);

	std::vector<recordItem>::iterator it = leaderBoardTen.begin();
	while (it != leaderBoardTen.end())
	{
		ItemLabel* imageItem = ItemLabel::create(40,
			cocos2d::String::createWithFormat("%s    %d", it->time.c_str(), it->score)->getCString(),
			"leader_item.png",
			cocos2d::Size(visibleSize.width/2, visibleSize.height/10));
		imageItem->setTouchEnabled(false);
		lv->pushBackCustomItem(imageItem);
		
		it ++;
	}

	//lv->setItemsMargin(0);
	lv->setGravity(cocos2d::ui::LISTVIEW_GRAVITY_CENTER_HORIZONTAL);  
	lv->setSize(cocos2d::Size(visibleSize.width/2, visibleSize.height*3/5));  
	lv->setBackGroundColorType(cocos2d::ui::LAYOUT_COLOR_SOLID);  
	lv->setBackGroundColor(cocos2d::Color3B::BLACK);
	lv->setBackGroundColorOpacity(168);
	this->addChild(lv);

	cocos2d::ui::Layout* buttonLayout = cocos2d::ui::Layout::create();
	cocos2d::ui::LinearLayoutParameter* blParam = cocos2d::ui::LinearLayoutParameter::create();
	blParam->setGravity(cocos2d::ui::LINEAR_GRAVITY_CENTER_HORIZONTAL);
	blParam->setMargin(cocos2d::ui::Margin(0, visibleSize.height/40, 0, visibleSize.height/40));
	buttonLayout->setLayoutParameter(blParam);
	buttonLayout->setBackGroundColor(cocos2d::Color3B::BLACK);
	buttonLayout->setBackGroundColorType(cocos2d::ui::LAYOUT_COLOR_SOLID);
	buttonLayout->setBackGroundColorOpacity(168);
	buttonLayout->setSize(cocos2d::Size(visibleSize.height*6/8, visibleSize.height/8));
	
	buttonLayout->setLayoutType(cocos2d::ui::LAYOUT_LINEAR_HORIZONTAL);
	ItemLabel* buttonRefresh = ItemLabel::create(0, "", "button_refresh.png",
		cocos2d::Size(visibleSize.height/8, visibleSize.height/8));
	buttonRefresh->addTouchEventListener(this, (cocos2d::ui::SEL_TouchEvent) &LeaderBoardLayout::refreshCallback);

	ItemLabel* buttonOff = ItemLabel::create(0, "", "button_off.png",
		cocos2d::Size(visibleSize.height/8, visibleSize.height/8));
	buttonOff->addTouchEventListener(this, (cocos2d::ui::SEL_TouchEvent) &LeaderBoardLayout::exitCallback);

	ItemLabel* buttonCancel = ItemLabel::create(0, "", "button_cancel.png",
		cocos2d::Size(visibleSize.height/8, visibleSize.height/8));
	buttonCancel->addTouchEventListener(this, (cocos2d::ui::SEL_TouchEvent) &LeaderBoardLayout::cancelCallback);

	cocos2d::ui::LinearLayoutParameter* btParam = cocos2d::ui::LinearLayoutParameter::create();
	btParam->setGravity(cocos2d::ui::LINEAR_GRAVITY_CENTER_VERTICAL);
	btParam->setMargin(cocos2d::ui::Margin(visibleSize.height/16, 0, visibleSize.height/16,0));
	buttonRefresh->setLayoutParameter(btParam);
	buttonOff->setLayoutParameter(btParam);
	buttonCancel->setLayoutParameter(btParam);
	
	buttonLayout->addChild(buttonRefresh);
	buttonLayout->addChild(buttonOff);
	buttonLayout->addChild(buttonCancel);
	this->addChild(buttonLayout);
	
	return true;
}
#include "WinFailLayout.h"


WinFailLayout::WinFailLayout(void)
{
}


WinFailLayout::~WinFailLayout(void)
{
}

WinFailLayout* WinFailLayout::create(int score, int bestScore, int winOrFail)
{
	WinFailLayout* layout = new WinFailLayout();
	if (layout && layout->init())
	{
		layout->autorelease();
		layout->initWithScore(score, bestScore, winOrFail);
		return layout;
	}
	CC_SAFE_DELETE(layout);
	return NULL;
}

void WinFailLayout::refreshCallback(cocos2d::CCObject *pSender, cocos2d::ui::TouchEventType type)
{
	cocos2d::Director::getInstance()->replaceScene(HelloWorld::createScene());
}

void WinFailLayout::cancelCallback(cocos2d::CCObject *pSender, cocos2d::ui::TouchEventType type)
{
	this->getParent()->removeChild(this);
}

void WinFailLayout::exitCallback(cocos2d::CCObject *pSender, cocos2d::ui::TouchEventType type)
{
	cocos2d::Director::getInstance()->end();
}

bool WinFailLayout::initWithScore(int score, int bestScore, int winOrFail)
{
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	this->setTouchEnabled(true);
	this->setBackGroundColor(cocos2d::Color3B::BLACK);
	this->setBackGroundColorOpacity(128);
	this->setBackGroundColorType(cocos2d::ui::LAYOUT_COLOR_SOLID);  
	this->setSize(visibleSize);
	this->setPosition(cocos2d::Point(0,0));
	this->setLayoutType(cocos2d::ui::LAYOUT_LINEAR_VERTICAL);

	std::string titleImage = ((winOrFail == 1) ? "game_over.png" : "game_win.png");
	std::string mainImage = ((winOrFail == 1) ? "over_lose.png" : "win_cup.png");

	ItemLabel* title = ItemLabel::create(0, "",
		titleImage,
		cocos2d::Size(visibleSize.width/2, visibleSize.height/6));
	title->setTouchEnabled(false);

	cocos2d::ui::LinearLayoutParameter* titleParam = cocos2d::ui::LinearLayoutParameter::create();
	titleParam->setGravity(cocos2d::ui::LINEAR_GRAVITY_CENTER_HORIZONTAL);
	titleParam->setMargin(cocos2d::ui::Margin(0, visibleSize.height/40, 0, visibleSize.height/40));
	title->setLayoutParameter(titleParam);
	this->addChild(title);

	
	ItemLabel* img = ItemLabel::create(0, "",
		mainImage,
		cocos2d::Size(visibleSize.width/3, visibleSize.height/2));
	img->setTouchEnabled(false);

	cocos2d::ui::LinearLayoutParameter* imageParam = cocos2d::ui::LinearLayoutParameter::create();
	imageParam->setGravity(cocos2d::ui::LINEAR_GRAVITY_CENTER_HORIZONTAL);
	img->setLayoutParameter(imageParam);
	this->addChild(img);

	ItemLabel* scoreText = ItemLabel::create(
		30, 
		cocos2d::String::createWithFormat("Your Score : %d", score)->getCString(),
		"",
		cocos2d::Size(visibleSize.width/4, visibleSize.height/16));
	scoreText->setTouchEnabled(false);

	cocos2d::ui::LinearLayoutParameter* scoreParam = cocos2d::ui::LinearLayoutParameter::create();
	scoreParam->setGravity(cocos2d::ui::LINEAR_GRAVITY_CENTER_HORIZONTAL);
	scoreText->setLayoutParameter(scoreParam);
	this->addChild(scoreText);

	ItemLabel* bestText = ItemLabel::create(
		15, 
		cocos2d::String::createWithFormat("Best : %d", bestScore)->getCString(),
		"",
		cocos2d::Size(visibleSize.width/8, visibleSize.height/20));
	bestText->setTouchEnabled(false);

	cocos2d::ui::LinearLayoutParameter* bestParam = cocos2d::ui::LinearLayoutParameter::create();
	bestParam->setGravity(cocos2d::ui::LINEAR_GRAVITY_CENTER_HORIZONTAL);
	bestText->setLayoutParameter(bestParam);
	this->addChild(bestText);
	
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
	buttonRefresh->addTouchEventListener(this, (cocos2d::ui::SEL_TouchEvent) &WinFailLayout::refreshCallback);

	ItemLabel* buttonOff = ItemLabel::create(0, "", "button_off.png",
		cocos2d::Size(visibleSize.height/8, visibleSize.height/8));
	buttonOff->addTouchEventListener(this, (cocos2d::ui::SEL_TouchEvent) &WinFailLayout::exitCallback);

	ItemLabel* buttonCancel = ItemLabel::create(0, "", "button_cancel.png",
		cocos2d::Size(visibleSize.height/8, visibleSize.height/8));
	buttonCancel->addTouchEventListener(this, (cocos2d::ui::SEL_TouchEvent) &WinFailLayout::cancelCallback);

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
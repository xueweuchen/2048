#include "HelloWorldScene.h"
#include "CardSprite.h"
#include "WinFailLayout.h"
#include "math.h"
#include "stdlib.h"
#include "time.h"
#include "ui/CocosGUI.h"
#include "LeaderBoardLayout.h"

USING_NS_CC;

void HelloWorld::createCardSprite(cocos2d::Size size)
{
    int unitSize = (size.height)/5;
	int leftpadding = (size.width - size.height);

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            cardArr[j][i] = CardSprite::createCardSprite(0, unitSize, unitSize, 
				unitSize*i+leftpadding+size.height/10, unitSize*(3-j)+size.height/10);
            this->addChild(cardArr[j][i]);
        }
    }
	randomCreateCard();
	randomCreateCard();
}

void HelloWorld::moveAction(int number, int fromx, int fromy, int destx, int desty)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int unitSize = (visibleSize.height)/5;
	int leftpadding = (visibleSize.width - visibleSize.height);

	CardSprite* card = CardSprite::createCardSprite(number, unitSize, unitSize, 
		unitSize*fromy+leftpadding+visibleSize.height/10, unitSize*(3-fromx)+visibleSize.height/10);
	this->addChild(card);

	card->runAction(cocos2d::Sequence::create(cocos2d::MoveTo::create(0.1f, cocos2d::Vec2(unitSize*(desty-fromy), unitSize*(fromx-destx))), 
		cocos2d::CallFunc::create([=](){
			card->removeFromParent();
		}), NULL));
}

void HelloWorld::randomCreateCard()
{
	int isZeroI[16] = {0};
	int isZeroJ[16] = {0};
	int isZeroNum = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (cardArr[i][j]->getNumber() == 0)
			{
				isZeroI[isZeroNum] = i;
				isZeroJ[isZeroNum] = j;
				isZeroNum ++;
			}
		}
	
	int randomPos = (int)(CCRANDOM_0_1() * isZeroNum);
	int randomNum = ((int)(CCRANDOM_0_1() * 2) + 1) * 2;
	cardArr[isZeroI[randomPos]][isZeroJ[randomPos]]->setNumber(randomNum);
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
	Point point = touch->getLocation();
	beginX = point.x;
	beginY = point.y;

	return true;
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{
	Point point = touch->getLocation();
	endX = point.x;
	endY = point.y;

	int deltaX = beginX - endX;
	int deltaY = beginY - endY;

	if (abs(deltaX) > abs(deltaY))
	{
		if (deltaX > 5)
		{
			if (moveLeft())
				randomCreateCard();
		} else if (deltaX < -5)
		{
			if (moveRight())
				randomCreateCard();
		}
	} else
	{
		if (deltaY > 5)
		{
			if (moveDown())
				randomCreateCard();
		} else if (deltaY < -5)
		{
			if (moveUp())
				randomCreateCard();
		}
	}
	updateTotalScore();
	int winOrFail = checkGameOver();
	if (winOrFail)
	{
		doGameOver(winOrFail);
	}	
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	cocos2d::log("Key with keycode %d pressed", keyCode);
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (moveLeft())
			randomCreateCard();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (moveRight())
			randomCreateCard();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		if (moveUp())
			randomCreateCard();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		if (moveDown())
			randomCreateCard();
		break;
	default:
		break;
	}	
	
	updateTotalScore();
	int winOrFail = checkGameOver();
	if (winOrFail)
	{
		doGameOver(winOrFail);
	}	
}

bool HelloWorld::moveUp()
{
	bool haveMove = 0;
	bool haveMerge[4][4] = {0};
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (cardArr[i][j]->getNumber() > 0)
			{
				int k = i-1;
				for (; k >= 0; k--)
				{
					if (cardArr[k][j]->getNumber() == 0)
					{
						moveAction(cardArr[k+1][j]->getNumber(), k+1, j, k, j);
						cardArr[k][j]->setNumber(cardArr[k+1][j]->getNumber());
						cardArr[k+1][j]->setNumber(0);
						haveMove = 1;
					}
					else if (cardArr[k][j]->getNumber() == cardArr[k+1][j]->getNumber() && !haveMerge[k][j])
					{
						moveAction(cardArr[k+1][j]->getNumber(), k+1, j, k, j);
						cardArr[k][j]->setNumber(2*cardArr[k+1][j]->getNumber());
						cardArr[k+1][j]->setNumber(0);
						totalScore += cardArr[k][j]->getNumber();
						haveMerge[k][j] = 1;
						haveMove = 1;
						break;
					}
					else
						break;
				}
			}
		}
	}
	return haveMove;
}

bool HelloWorld::moveDown()
{
	bool haveMove = 0;
	bool haveMerge[4][4] = {0};
	for (int j = 0; j < 4; j++)
	{
		for (int i = 3; i >= 0; i--)
		{
			if (cardArr[i][j]->getNumber() > 0)
			{
				int k = i+1;
				for (; k < 4; k++)
				{
					if (cardArr[k][j]->getNumber() == 0)
					{
						moveAction(cardArr[k-1][j]->getNumber(), k-1, j, k, j);
						cardArr[k][j]->setNumber(cardArr[k-1][j]->getNumber());
						cardArr[k-1][j]->setNumber(0);
						haveMove = 1;
					}
					else if (cardArr[k][j]->getNumber() == cardArr[k-1][j]->getNumber() && !haveMerge[k][j])
					{
						moveAction(cardArr[k-1][j]->getNumber(), k-1, j, k, j);
						cardArr[k][j]->setNumber(2*cardArr[k-1][j]->getNumber());
						cardArr[k-1][j]->setNumber(0);
						totalScore += cardArr[k][j]->getNumber();
						haveMerge[k][j] = 1;
						haveMove = 1;
						break;
					}
					else
						break;
				}
			}
		}
	}
	return haveMove;
}

bool HelloWorld::moveLeft()
{
	bool haveMove = 0;
	bool haveMerge[4][4] = {0};
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (cardArr[i][j]->getNumber() > 0)
			{
				int k = j-1;
				for (; k >= 0; k--)
				{
					if (cardArr[i][k]->getNumber() == 0)
					{
						moveAction(cardArr[i][k+1]->getNumber(), i, k+1, i, k);
						cardArr[i][k]->setNumber(cardArr[i][k+1]->getNumber());
						cardArr[i][k+1]->setNumber(0);
						haveMove = 1;
					}
					else if (cardArr[i][k]->getNumber() == cardArr[i][k+1]->getNumber() && !haveMerge[i][k])
					{
						moveAction(cardArr[i][k+1]->getNumber(), i, k+1, i, k);
						cardArr[i][k]->setNumber(2*cardArr[i][k+1]->getNumber());
						cardArr[i][k+1]->setNumber(0);
						totalScore += cardArr[i][k]->getNumber();
						haveMerge[i][k] = 1;
						haveMove = 1;
						break;
					}
					else
						break;
				}
			}
		}
	}
	return haveMove;
}

bool HelloWorld::moveRight()
{
	bool haveMove = 0;
	bool haveMerge[4][4] = {0};
	for (int i = 0; i < 4; i++)
	{
		for (int j = 3; j >= 0; j--)
		{
			if (cardArr[i][j]->getNumber() > 0)
			{
				int k = j+1;
				for (; k < 4; k++)
				{
					if (cardArr[i][k]->getNumber() == 0)
					{
						moveAction(cardArr[i][k-1]->getNumber(), i, k-1, i, k);
						cardArr[i][k]->setNumber(cardArr[i][k-1]->getNumber());
						cardArr[i][k-1]->setNumber(0);
						haveMove = 1;
					}
					else if (cardArr[i][k]->getNumber() == cardArr[i][k-1]->getNumber() && !haveMerge[i][k])
					{
						moveAction(cardArr[i][k-1]->getNumber(), i, k-1, i, k);
						cardArr[i][k]->setNumber(2*cardArr[i][k-1]->getNumber());
						cardArr[i][k-1]->setNumber(0);
						totalScore += cardArr[i][k]->getNumber();
						haveMerge[i][k] = 1;
						haveMove = 1;
						break;
					}
					else
						break;
				}
			}
		}
	}
	return haveMove;
}

int HelloWorld::checkGameOver()
{
	// isGameOver 0 : not finish 1 : fail 2 : win
	int isGameOver = 1;

	
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (cardArr[i][j]->getNumber() == 2048)
			{
				isGameOver = 2;
				return isGameOver;
			}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (cardArr[i][j]->getNumber() == 0 ||
				(i-1 >= 0 && cardArr[i][j]->getNumber() == cardArr[i-1][j]->getNumber()) ||
				(i+1 < 3 && cardArr[i][j]->getNumber() == cardArr[i+1][j]->getNumber()) ||
				(j-1 >= 0 && cardArr[i][j]->getNumber() == cardArr[i][j-1]->getNumber()) ||
				(j+1 < 3 && cardArr[i][j]->getNumber() == cardArr[i][j+1]->getNumber()))
					isGameOver = 0;
		}
	}

	return isGameOver;
}

void HelloWorld::doGameOver(int winOrFail)
{
	leaderBoard->updateLederData(totalScore);
	bestScore = leaderBoard->getBestScore();
	popupLayout(winOrFail);
}

void HelloWorld::popupLayout(int winOrFail)
{
	WinFailLayout* pl = WinFailLayout::create(this->totalScore, this->bestScore, winOrFail);
	this->addChild(pl);
}

void HelloWorld::updateTotalScore()
{
	totalScoreTTF->setString(cocos2d::String::createWithFormat("%i", totalScore)->getCString());
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
	srand((unsigned)time(NULL));

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
	auto panelSprite = Sprite::create("panel.png");
	panelSprite->setPosition(Point(visibleSize.width - visibleSize.height/2, visibleSize.height/2));
	Size orignalPanelSize = panelSprite->getContentSize();
	panelSprite->setScaleX(visibleSize.height*9.3/10/orignalPanelSize.width);
	panelSprite->setScaleY(visibleSize.height*9.3/10/orignalPanelSize.height);
	this->addChild(panelSprite);

    createCardSprite(visibleSize);

	// create menu, it's an autorelease object
	auto menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	int leftPadding = visibleSize.width - visibleSize.height;
	Sprite* totalScoreSprite = Sprite::create("score2.png");
	totalScoreSprite->setPosition(Point(leftPadding/2, visibleSize.height*5/6));
	Size orignalSize = totalScoreSprite->getContentSize();
	totalScoreSprite->setScaleX(leftPadding*3/4/orignalSize.width);
	totalScoreSprite->setScaleY(visibleSize.height/5/orignalSize.height);
	this->addChild(totalScoreSprite);

	Sprite* bestScoreSprite = Sprite::create("score2.png");
	bestScoreSprite->setPosition(Point(leftPadding/2, visibleSize.height*5/8));
	orignalSize = bestScoreSprite->getContentSize();
	bestScoreSprite->setScaleX(leftPadding*3/4/orignalSize.width);
	bestScoreSprite->setScaleY(visibleSize.height/5/orignalSize.height);
	this->addChild(bestScoreSprite);

	leaderBoard =  LeaderData::create();
	leaderBoard->retain();
	totalScore = 0;
	bestScore = leaderBoard->getBestScore();

	totalScoreTTF = cocos2d::LabelTTF::create(cocos2d::String::createWithFormat("%i", totalScore)->getCString(), "fonts/consolas.ttf", 80);	
	totalScoreTTF->setPosition(totalScoreSprite->getPosition());
	this->addChild(totalScoreTTF);
	bestScoreTTF = cocos2d::LabelTTF::create(cocos2d::String::createWithFormat("%i", bestScore)->getCString(), "fonts/consolas.ttf", 80);
	bestScoreTTF->setPosition(bestScoreSprite->getPosition());
	this->addChild(bestScoreTTF);


	auto restartItem = MenuItemImage::create(
		"restart.png",
		"restart_select.png",
		CC_CALLBACK_1(HelloWorld::restartCallback, this));
	restartItem->setPosition(Point(leftPadding/2, visibleSize.height*6/16));
	orignalSize = restartItem->getContentSize();
	restartItem->setScaleX(leftPadding*2/3/orignalSize.width);
	restartItem->setScaleY(visibleSize.height/8.0/orignalSize.height);
	menu->addChild(restartItem);

	auto leaderItem = MenuItemImage::create(
		"leaderboard.png",
		"leaderboard_select.png",
		CC_CALLBACK_1(HelloWorld::leaderBoardCallback, this));
	leaderItem->setPosition(Point(leftPadding/2, restartItem->getPosition().y - visibleSize.height*4/32));
	//orignalSize = leaderItem->getContentSize();
	leaderItem->setScaleX(leftPadding*2/3/orignalSize.width);
	leaderItem->setScaleY(visibleSize.height/8.0/orignalSize.height);
	menu->addChild(leaderItem);

	auto optionItem = MenuItemImage::create(
		"option.png",
		"option_select.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	optionItem->setPosition(Point(leftPadding/2, leaderItem->getPosition().y - visibleSize.height*4/32));
	//orignalSize = optionItem->getContentSize();
	optionItem->setScaleX(leftPadding*2/3/orignalSize.width);
	optionItem->setScaleY(visibleSize.height/8.0/orignalSize.height);
	menu->addChild(optionItem);


	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::restartCallback(cocos2d::Ref* pSender)
{
	cocos2d::Director::getInstance()->replaceScene(HelloWorld::createScene());
}

void HelloWorld::leaderBoardCallback(cocos2d::Ref* pSender)
{
	this->addChild(LeaderBoardLayout::create(leaderBoard->getLederBoardTen()));
}

void HelloWorld::optionCallback(cocos2d::Ref* pSender)
{

}
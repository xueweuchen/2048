#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CardSprite.h"
#include "LeaderData.h"

 
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void restartCallback(cocos2d::Ref* pSender);
	void leaderBoardCallback(cocos2d::Ref* pSender);
	void optionCallback(cocos2d::Ref* pSender);
    
	// touch events
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();
	
	void moveAction(int number, int fromx, int fromy, int destx, int desty);
	// random create initial cards
	void randomCreateCard();
	// create cards
    void createCardSprite(cocos2d::Size size);
	// check whether game ends or not
	int checkGameOver();
	void doGameOver(int winOrFail);
	// update the value of totalTTF
	void updateTotalScore();

	// pop up fail layer
	void popupLayout(int winOrFail);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	CardSprite* cardArr[4][4];
	int beginX, beginY, endX, endY;
	int totalScore;
	int bestScore;
	cocos2d::LabelTTF* totalScoreTTF;
	cocos2d::LabelTTF* bestScoreTTF;
	LeaderData* leaderBoard;
};

#endif // __HELLOWORLD_SCENE_H__

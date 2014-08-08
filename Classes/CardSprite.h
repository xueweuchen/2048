#ifndef _CARD_SPRITE_H_
#define  _CARD_SPRITE_H_

#include "cocos2d.h"

class CardSprite : public cocos2d::Sprite
{
public:
	CardSprite(void);
	~CardSprite(void);
    static CardSprite* createCardSprite(int number, int width, int height, float cardx, float cardy);
    virtual bool init();
    int getNumber();
    void setNumber(int num);
private:
    int number;
    void enemyInit(int number, int width, int height, float cardx, float cardy);

    cocos2d::LabelTTF* labelTTFCardNumber;
	cocos2d::Sprite* cardsprite;
};  

#endif // _CARD_SPRITE_H_

#include "CardSprite.h"


CardSprite::CardSprite(void)
{
}


CardSprite::~CardSprite(void)
{
}

CardSprite* CardSprite::createCardSprite(int number, int width, int height, float cardx, float cardy)
{
	CardSprite* enemy = new CardSprite();
	if (enemy && enemy->init())
	{
		enemy->autorelease();
		enemy->enemyInit(number, width, height, cardx, cardy);

		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

bool CardSprite::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

int CardSprite::getNumber()
{
	return number;
}

void CardSprite::setNumber(int num)
{
	number = num;
	cardsprite->setTexture(cocos2d::TextureCache::sharedTextureCache()->addImage(
		cocos2d::String::createWithFormat("%i.png", number)->getCString()));
	if (number > 0)
	{
		labelTTFCardNumber->setString(cocos2d::String::createWithFormat("%i", number)->getCString());	
	}
	else
	{
		labelTTFCardNumber->setString("");	
	}
	if (number >= 0)
	{
		labelTTFCardNumber->setFontSize(100);
	}
	if (number >= 16) 
	{
		labelTTFCardNumber->setFontSize(90);
	}
	if(number >= 128)
	{
		labelTTFCardNumber->setFontSize(60);
	}
	if(number >= 1024){
		labelTTFCardNumber->setFontSize(40);
	}
}

void CardSprite::enemyInit(int number, int width, int height, float cardx, float cardy)
{
	this->number = number;

	cardsprite = cocos2d::Sprite::create(cocos2d::String::createWithFormat("%i.png", number)->getCString());
	cardsprite->setPosition(cocos2d::Point(cardx + width/2, cardy + height/2));
	cocos2d::Size orignalSize = cardsprite->getContentSize();
	cardsprite->setScaleX(width/orignalSize.width);
	cardsprite->setScaleY(height/orignalSize.height);

	this->addChild(cardsprite);

	if (number > 0)
	{
		labelTTFCardNumber = cocos2d::LabelTTF::create(cocos2d::String::createWithFormat("%i", number)->getCString(), "fonts/consolas.ttf", 100);	
	}
	else
	{
		labelTTFCardNumber = cocos2d::LabelTTF::create("", "fonts/consolas.ttf", 100);	
	}
	labelTTFCardNumber->setPosition(cocos2d::Point(cardx + width/2, cardy + height/2));
	labelTTFCardNumber->setTag(8);
	this->addChild(labelTTFCardNumber);
}
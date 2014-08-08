#include "ItemLabel.h"


ItemLabel::ItemLabel(void)
{
}


ItemLabel::~ItemLabel(void)
{
}

ItemLabel* ItemLabel::create(float fontSize, const std::string &text, const std::string &texturefile, cocos2d::Size size)
{
	ItemLabel* item = new ItemLabel();
	if (item && item->init())
	{
		item->autorelease();
		item->initLabel(fontSize, text, texturefile, size);
		return item;
	}
	CC_SAFE_DELETE(item);
	return NULL;
}

bool ItemLabel::initLabel(float fontSize, const std::string &text, const std::string &texturefile, cocos2d::Size size)
{
	this->setTitleText(text);
	this->setTitleFontSize(fontSize);
	//this->setTouchEnabled(false);
	if (texturefile.size() > 0)
	{
		this->loadTextureNormal(texturefile);
		this->_scaleX = size.width/this->getContentSize().width;
		this->_scaleY = size.height/this->getContentSize().height;
	}
	this->_normalTextureSize = size;
	return true;
}

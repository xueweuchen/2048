#ifndef _ITEM_LABEL_H_
#define _ITEM_LABEL_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>

class ItemLabel : public cocos2d::ui::Button
{
public:
	ItemLabel(void);
	~ItemLabel(void);
	static ItemLabel* create(float fontSize, const std::string &text, const std::string &texturefile, cocos2d::Size size);
	virtual bool initLabel(float fontSize, const std::string &text, const std::string &texturefile, cocos2d::Size size);
};


#endif



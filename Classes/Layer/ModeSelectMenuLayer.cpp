//
//  ModeSelectMenuLayer.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/27.
//
//

#include "ModeSelectMenuLayer.h"

USING_NS_CC;

bool ModeSelectMenuLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto s = Director::getInstance()->getWinSize();
    
    auto item_label = Label::createWithBMFont("fonts/message_font.fnt", "ITEM");
    item_label->getTexture()->setAliasTexParameters();
    item_label->setScale(3.0f);
    item_label->setPosition(Point(s.width / 2.0f, s.height * 3.0f / 4.0f));
    addChild(item_label);
    
    auto make_label = Label::createWithBMFont("fonts/message_font.fnt", "MAKE");
    make_label->getTexture()->setAliasTexParameters();
    make_label->setScale(3.0f);
    make_label->setPosition(Point(s.width / 2.0f, s.height * 2.5f / 4.0f));
    addChild(make_label);
    
    return true;
}
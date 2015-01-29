//
//  MakeMenuLayer.cpp
//  solno
//
//  Created by Mitsushige Komiya on 2015/01/29.
//
//

#include "MakeMenuLayer.h"

USING_NS_CC;

bool MakeMenuLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto s = Director::getInstance()->getWinSize();
    auto item_label = Label::createWithBMFont("fonts/message_font.fnt", "MAKE");
    item_label->getTexture()->setAliasTexParameters();
    item_label->setPosition(s.width / 2.0f, s.height * 3.0f / 4.0f);
    item_label->setScale(3.0f);
    addChild(item_label);
    
    return true;
}
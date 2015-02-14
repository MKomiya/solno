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
    
    auto frame = Sprite::create("ui/ui_menu_make_frame.png");
    frame->setPosition(s.width / 2.0f, s.height * 2.0f / 3.0f);
    addChild(frame);
    
    // カーソル表示
    current_cursor = Sprite::create("ui/ui_menu_item_cursor.png");
    current_cursor->setAnchorPoint(Point(0, 1));
    current_cursor->setPosition(67, s.height - 105);
    addChild(current_cursor);
    
    return true;
}
//
//  ControllerLayer.cpp
//  solno
//
//  Created by S_Wyvern on 2014/12/27.
//
//

#include "ControllerLayer.h"

USING_NS_CC;

bool ControllerLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto texture = Director::getInstance()->getTextureCache()->addImage("ui/ui_common_frame.png");
    texture->setAliasTexParameters();
    
    auto frame = Sprite::createWithTexture(texture);
    frame->setAnchorPoint(Point::ZERO);
    frame->setScale(2.0f);
    addChild(frame);
    
    return true;
}
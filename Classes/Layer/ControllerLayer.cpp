//
//  ControllerLayer.cpp
//  solno
//
//  Created by S_Wyvern on 2014/12/27.
//
//

#include "ControllerLayer.h"
#include "MenuArrowItem.h"
#include "MenuDecideItem.h"

USING_NS_CC;

bool ControllerLayer::init()
{
    if (!Raciela::View::init()) {
        return false;
    }
    
    auto visible_size = Director::getInstance()->getVisibleSize();
    auto texture = Director::getInstance()->getTextureCache()->addImage("ui/ui_common_frame.png");
    texture->setAliasTexParameters();
    
    /*
    auto mask = Sprite::create("ui/mask.png");
    mask->setAnchorPoint(Point(0, 1));
    mask->setPosition(16, visible_size.height - 16);
    addChild(mask);
    */
     
    auto mask2 = Sprite::create("ui/mask2.png");
    mask2->setAnchorPoint(Point(0, 1));
    mask2->setPosition(16, visible_size.height - 16);
    addChild(mask2);
    
    auto mask3 = Sprite::create("ui/mask2.png");
    mask3->setAnchorPoint(Point(0, 1));
    mask3->setPosition(16, visible_size.height - 16 - mask3->getContentSize().height);
    addChild(mask3);
    
    auto action2 = RepeatForever::create(
                                        Sequence::create(MoveBy::create(0.8f, Point(0, 144)),
                                                         MoveTo::create(0, Point(16, visible_size.height - 16)),
                                                         NULL)
                                        );
    mask2->runAction(action2);
    
    auto action3 = RepeatForever::create(
                                         Sequence::create(MoveBy::create(0.8f, Point(0, 144)),
                                                          MoveTo::create(0, Point(16, visible_size.height - 16 - mask3->getContentSize().height)),
                                                          NULL)
                                         );
    mask3->runAction(action3);
    
    auto frame = Sprite::createWithTexture(texture);
    frame->setPosition(Point(visible_size.width / 2.0f, visible_size.height / 2.0f));
    addChild(frame);
    
    return true;
}
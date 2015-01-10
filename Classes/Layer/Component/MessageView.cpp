//
//  MessageView.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/10.
//
//

#include "MessageView.h"

USING_NS_CC;

MessageView::MessageView(std::string msg_data) :
msg_data(msg_data),
string_idx(0){}

MessageView* MessageView::create(std::string msg_data)
{
    auto ret = new MessageView(msg_data);
    if (ret && ret->initWithFile("ui/message_window.png")) {
        ret->autorelease();
        
        // 開始位置固定
        ret->setAnchorPoint(Point(0, 0));
        ret->setPosition(16, 96);
        ret->setScale(2.0f);
        ret->getTexture()->setAliasTexParameters();
        
        // 空のstring
        auto msg_label = LabelTTF::create("", "Arial", 6);
        msg_label->setAnchorPoint(Point(0, 1));
        msg_label->setPosition(8, 40);
        msg_label->setTag(MESSAGE_LABEL);
        ret->addChild(msg_label);
    } else {
        delete ret;
        ret = NULL;
    }
    return ret;
}

void MessageView::onEnter()
{
    Sprite::onEnter();
    
    auto move  = MoveTo::create(0.3f, Point(16, 176));
    auto moved = CallFunc::create([=]() {
        this->scheduleUpdate();
    });
    runAction(Sequence::create(move, moved, NULL));
}

void MessageView::update(float dt)
{
    string_idx++;
    string_idx = string_idx >= msg_data.length() ? msg_data.length() : string_idx;
    
    auto output = msg_data.substr(0, string_idx);
    auto msg_label = (LabelTTF*)getChildByTag(MESSAGE_LABEL);
    msg_label->setString(output.c_str());
}
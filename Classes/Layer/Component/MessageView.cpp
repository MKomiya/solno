//
//  MessageView.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/10.
//
//

#include "MessageView.h"

USING_NS_CC;

MessageView::MessageView() :
state(DISABLED),
msg_data(""),
string_idx(0){}

MessageView* MessageView::create()
{
    auto ret = new MessageView();
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
        
        // disabled view
        ret->setVisible(false);
    } else {
        delete ret;
        ret = NULL;
    }
    return ret;
}

void MessageView::viewMessages(std::string msg_data)
{
    this->msg_data = msg_data;
    this->state    = PROGRESS;
    
    setVisible(true);
    
    auto move  = MoveTo::create(0.3f, Point(16, 176));
    auto moved = CallFunc::create([=]() {
        this->schedule(schedule_selector(MessageView::updateMessage), 0.03f);
    });
    runAction(Sequence::create(move, moved, NULL));
}

void MessageView::updateMessage(float dt)
{
    string_idx += 3;
    string_idx = string_idx >= msg_data.length() ? msg_data.length() : string_idx;
    
    auto output = msg_data.substr(0, string_idx);
    auto msg_label = (LabelTTF*)getChildByTag(MESSAGE_LABEL);
    msg_label->setString(output.c_str());
    
    if (string_idx == msg_data.length()) {
        unschedule(schedule_selector(MessageView::updateMessage));
        state = WAIT;
    }
}

void MessageView::releaseMessages()
{
    auto move  = MoveTo::create(0.1f, Point(16, 96));
    auto moved = CallFunc::create([=]() {
        state = DISABLED;
        string_idx = 0;
        setVisible(false);
        
        auto msg_label = (LabelTTF*)getChildByTag(MESSAGE_LABEL);
        msg_label->setString("");
    });
    runAction(Sequence::create(move, moved, NULL));
}
//
//  MessageView.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/10.
//
//

#include <json11.hpp>
#include "MessageView.h"

USING_NS_CC;

MessageView::MessageView() :
state(DISABLED),
string_idx(0),
msg_idx(0){}

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
        auto msg_label = Label::createWithBMFont("fonts/message_font.fnt", "");
        msg_label->getTexture()->setAliasTexParameters();
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

void MessageView::viewMessages(std::vector<std::string> msg_data)
{
    this->msg_data = msg_data;
    
    this->now_msg  = this->msg_data.front();
    this->state    = PROGRESS;
    this->msg_idx  = 0;
    this->string_idx = 0;
    
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
    string_idx = string_idx >= now_msg.length() ? now_msg.length() : string_idx;
    
    auto output = now_msg.substr(0, string_idx);
    auto msg_label = (Label*)getChildByTag(MESSAGE_LABEL);
    msg_label->setString(output.c_str());
    
    if (string_idx == now_msg.length()) {
        unschedule(schedule_selector(MessageView::updateMessage));
        state = WAIT;
    }
}

void MessageView::nextMessage()
{
    msg_idx++;
    string_idx = 0;
    now_msg = msg_data[msg_idx];
    
    if (msg_idx == msg_data.size()) {
        releaseMessages();
        return ;
    }
    
    auto msg_label = (Label*)getChildByTag(MESSAGE_LABEL);
    msg_label->setString("");
    
    schedule(schedule_selector(MessageView::updateMessage), 0.03f);
}

void MessageView::releaseMessages()
{
    auto move  = MoveTo::create(0.1f, Point(16, 96));
    auto moved = CallFunc::create([=]() {
        state = DISABLED;
        string_idx = 0;
        setVisible(false);
        
        auto msg_label = (Label*)getChildByTag(MESSAGE_LABEL);
        msg_label->setString("");
    });
    runAction(Sequence::create(move, moved, NULL));
}

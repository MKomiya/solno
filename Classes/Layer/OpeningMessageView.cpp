//
//  OpeningMessageView.cpp
//  solno
//
//  Created by S_Wyvern on 2015/03/03.
//
//

#include "OpeningMessageView.h"
#include "Dispatcher.h"

USING_NS_CC;

OpeningMessageView* OpeningMessageView::create()
{
    auto ret = new OpeningMessageView();
    if (!ret) {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    ret->autorelease();
    
    // 開始位置固定
    ret->setAnchorPoint(Point(0, 0));
    ret->setPosition(16, 176);
    ret->setScale(2.0f);
    
    auto msg_label = Label::createWithBMFont("fonts/message_font.fnt", "");
    msg_label->getTexture()->setAliasTexParameters();
    msg_label->setAnchorPoint(Point(0, 1));
    msg_label->setPosition(8, 40);
    msg_label->setColor(Color3B(0, 255, 30));
    msg_label->setWidth(132);
    msg_label->setLineBreakWithoutSpace(true);
    ret->addChild(msg_label);
    
    ret->setMsgLabel(msg_label);
    ret->setVisible(false);
    ret->setStringIdx(0);
    ret->setMsg("");
    
    return ret;
}

void OpeningMessageView::viewMessage(std::string msg)
{
    setStringIdx(0);
    setMsg(msg);
    
    auto dispatcher = Raciela::Dispatcher::getInstance();
    dispatcher->dispatch("update_msg_state", OpeningMessageViewState::PROGRESS);
    
    setVisible(true);
    schedule(schedule_selector(OpeningMessageView::update), 0.03f);
}

void OpeningMessageView::update(float dt)
{
    string_idx += 3;
    string_idx = string_idx >= msg.length() ? msg.length() : string_idx;
    
    auto output = msg.substr(0, string_idx);
    msg_label->setString(output.c_str());
    if (string_idx == msg.length()) {
        auto dispatcher = Raciela::Dispatcher::getInstance();
        dispatcher->dispatch("update_msg_state", OpeningMessageViewState::WAIT);
        
        unschedule(schedule_selector(OpeningMessageView::update));
    }
}

void OpeningMessageView::releaseMessage()
{
    auto dispatcher = Raciela::Dispatcher::getInstance();
    dispatcher->dispatch("update_msg_state", OpeningMessageViewState::DISABLED);
    
    setVisible(false);
}
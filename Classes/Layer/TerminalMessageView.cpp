//
//  TerminalMessageView.cpp
//  solno
//
//  Created by S_Wyvern on 2015/03/01.
//
//

#include "TerminalMessageView.h"
#include "Dispatcher.h"

USING_NS_CC;

TerminalMessageView* TerminalMessageView::create()
{
    auto ret = new TerminalMessageView();
    if (!ret) {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    ret->autorelease();
    
    // 開始位置固定
    ret->setAnchorPoint(Point(0, 0));
    ret->setPosition(16, 56);
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

void TerminalMessageView::viewMessage(std::string msg)
{
    setStringIdx(0);
    setMsg(msg);
    
    auto dispatcher = Raciela::Dispatcher::getInstance();
    dispatcher->dispatch("update_terminal_msg_state", TerminalMessageViewState::PROGRESS);
    
    setVisible(true);
    schedule(schedule_selector(TerminalMessageView::update), 0.03f);
}

void TerminalMessageView::update(float dt)
{
    string_idx += 3;
    string_idx = string_idx >= msg.length() ? msg.length() : string_idx;
    
    auto output = msg.substr(0, string_idx);
    msg_label->setString(output.c_str());
    if (string_idx == msg.length()) {
        auto dispatcher = Raciela::Dispatcher::getInstance();
        dispatcher->dispatch("update_terminal_msg_state", TerminalMessageViewState::WAIT);
        
        unschedule(schedule_selector(TerminalMessageView::update));
    }
}

void TerminalMessageView::releaseMessage()
{
    auto dispatcher = Raciela::Dispatcher::getInstance();
    dispatcher->dispatch("update_terminal_msg_state", TerminalMessageViewState::DISABLED);

    setVisible(false);
}
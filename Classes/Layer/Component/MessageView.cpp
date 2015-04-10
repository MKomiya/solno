//
//  MessageView.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/10.
//
//

#include <json11.hpp>
#include "MessageView.h"
#include "Dispatcher.h"

USING_NS_CC;

MessageView* MessageView::create(bool visible_window)
{
    auto ret = new MessageView();
    if (!ret) {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    ret->autorelease();
    
    ret->setVisibleWindow(visible_window);
    
    // 開始位置固定
    ret->setAnchorPoint(Point(0, 0));
    ret->setPosition(16, 176);
    ret->setScale(2.0f);
    
    // メッセージウィンドウ
    if (visible_window) {
        auto msg_window = Sprite::create("ui/message_window.png");
        msg_window->getTexture()->setAliasTexParameters();
        msg_window->setAnchorPoint(Point(0, 0));
        ret->setMsgWindow(msg_window);
        ret->addChild(msg_window);
        
        ret->setPosition(16, 96);
    }
    
    // 空のstring
    auto msg_label = Label::createWithBMFont("fonts/message_font.fnt", "");
    msg_label->getTexture()->setAliasTexParameters();
    msg_label->setAnchorPoint(Point(0, 1));
    msg_label->setPosition(8, 40);
    msg_label->setWidth(132);
    msg_label->setLineBreakWithoutSpace(true);
    ret->setMsgLabel(msg_label);
    ret->addChild(msg_label);
    
    // disabled view
    ret->setVisible(false);
    
    ret->setStringIdx(0);
    ret->setmsgIdx(0);
    
    return ret;
}

void MessageView::viewMessages(std::vector<std::string> msg_data)
{
    this->msg_data = msg_data;
    
    now_msg    = msg_data.front();
    msg_idx    = 0;
    string_idx = 0;
    
    auto dispatcher = Raciela::Dispatcher::getInstance();
    dispatcher->dispatch("update_msg_state", MessageViewState::PROGRESS);
    
    setVisible(true);
    
    if (visible_window) {
        auto move  = MoveTo::create(0.3f, Point(16, 176));
        auto moved = CallFunc::create([this]() {
            schedule(schedule_selector(MessageView::updateMessage), 0.03f);
        });
        runAction(Sequence::create(move, moved, NULL));
        
        return ;
    }
    
    schedule(schedule_selector(MessageView::updateMessage), 0.03f);
}

void MessageView::updateMessage(float dt)
{
    string_idx += 3;
    string_idx = string_idx >= (int)now_msg.length() ? (int)now_msg.length() : string_idx;
    
    auto output = now_msg.substr(0, string_idx);
    msg_label->setString(output.c_str());
    
    if (string_idx == now_msg.length()) {
        unschedule(schedule_selector(MessageView::updateMessage));
        
        auto dispatcher = Raciela::Dispatcher::getInstance();
        dispatcher->dispatch("update_msg_state", MessageViewState::WAIT);
    }
}

void MessageView::nextMessage()
{
    msg_idx++;
    string_idx = 0;
    if (msg_idx == msg_data.size()) {
        releaseMessages();
        return ;
    }
    
    now_msg = msg_data[msg_idx];
    
    msg_label->setString("");
    
    schedule(schedule_selector(MessageView::updateMessage), 0.03f);
}

void MessageView::releaseMessages()
{
    if (visible_window) {
        auto move  = MoveTo::create(0.1f, Point(16, 96));
        auto moved = CallFunc::create([=]() {
            disabledMessage();
        });
        runAction(Sequence::create(move, moved, NULL));
        return;
    }
    
    disabledMessage();
}

void MessageView::setMessageColor(cocos2d::Color3B color)
{
    msg_label->setColor(color);
}

void MessageView::disabledMessage()
{
    auto dispatcher = Raciela::Dispatcher::getInstance();
    dispatcher->dispatch("update_msg_state", MessageViewState::DISABLED);
    
    string_idx = 0;
    setVisible(false);
    msg_label->setString("");
}

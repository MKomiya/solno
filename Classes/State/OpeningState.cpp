//
//  OpeningState.cpp
//  solno
//
//  Created by S_Wyvern on 2015/02/28.
//
//

#include "OpeningState.h"
#include "OpeningLayer.h"
#include "ControllerLayer.h"
#include "MessageView.h"
#include "TerminalMessageView.h"
#include "Router.h"
#include "Dispatcher.h"
#include "FieldState.h"

USING_NS_CC;

OpeningState* OpeningState::create()
{
    auto ret = new OpeningState();
    if (!ret) {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    ret->init();
    ret->setMessageViewState(MessageViewState::DISABLED);
    ret->setTerminalMessageViewState(TerminalMessageViewState::DISABLED);
    
    ret->autorelease();
    ret->created();
    return ret;
}

void OpeningState::enter()
{
    view = OpeningLayer::create();
    auto frame = ControllerLayer::create();
    
    auto router = Raciela::Router::getInstance();
    router->addView(frame);
    router->addView(view);
    
    std::vector<std::string> data;
    data.push_back("オープニングメッセージ");
    data.push_back("ハローハロー");
    data.push_back("キコエテマスカ");
    data.push_back("アトハタノミマシタヨ");
    
    view->viewMessages(data);
    
    view->viewTerminalMessage("ターミナルメッセージ");
}

void OpeningState::update()
{
}

void OpeningState::exit()
{
    Raciela::Router::getInstance()->removeView(view);
}

void OpeningState::delegate()
{
    dispatcher->subscribe<void ()>("touched", [=]() {
        if (msg_view_state == MessageViewState::WAIT) {
            view->nextMessages();
        }
        
        if (terminal_message_view_state == TerminalMessageViewState::WAIT) {
            view->releaseTerminalMesage();
        }
    });
    
    dispatcher->subscribe<void (MessageViewState)>("update_msg_state", [=](MessageViewState state) {
        msg_view_state = state;
    });
    
    dispatcher->subscribe<void (TerminalMessageViewState)>("update_terminal_msg_state", [=](TerminalMessageViewState state) {
        terminal_message_view_state = state;
    });
    
    dispatcher->subscribe<void ()>("exit_opening", [=]() {
        auto router = Raciela::Router::getInstance();
        router->pushState(FieldState::create());
    });
}
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
#include "OpeningMessageView.h"
#include "TerminalMessageView.h"
#include "Router.h"
#include "Dispatcher.h"
#include "FieldState.h"
#include "MasterStorageModule.h"

USING_NS_CC;

OpeningState* OpeningState::create()
{
    auto ret = new OpeningState();
    if (!ret) {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    ret->init();
    ret->setMessageViewState(OpeningMessageViewState::WAIT);
    ret->setTerminalMessageViewState(TerminalMessageViewState::WAIT);
    
    ret->autorelease();
    ret->created();
    return ret;
}

bool OpeningState::init()
{
    if (!Raciela::State::init()) {
        return false;
    }

    auto master    = MasterStorageModule::getInstance();
    auto data_list = master->getOpeningList();
    for (auto data : data_list) {
        if (data.type == MasterOpeningType::NORMAL) {
            normal_msg.insert(std::make_pair(data.id, data.msg));
            continue ;
        }
        if (data.type == MasterOpeningType::TERMINAL){
            terminal_msg.insert(std::make_pair(data.id, data.msg));
            continue ;
        }
    }
    
    setMsgIndex(1);
    
    return true;
}

void OpeningState::enter()
{
    view = OpeningLayer::create();
    auto frame = ControllerLayer::create();
    
    auto router = Raciela::Router::getInstance();
    router->addView(frame);
    router->addView(view);
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
        if (msg_view_state != OpeningMessageViewState::PROGRESS &&
            terminal_message_view_state != TerminalMessageViewState::PROGRESS)
        {
            msg_index++;
            CCLOG("msg_index: %d", msg_index);
            
            if (normal_msg.size() == 0) {
                auto router = Raciela::Router::getInstance();
                router->pushState(FieldState::create());
                return ;
            }
            
            auto it_normal = normal_msg.find(msg_index);
            if (it_normal == normal_msg.end()) {
                view->nextMessages();
            } else {
                view->viewMessages(it_normal->second);
                normal_msg.erase(it_normal);
            }
            
            if (terminal_msg.size() != 0) {
                auto it_terminal = terminal_msg.find(msg_index);
                if (it_terminal == terminal_msg.end()) {
                    view->releaseTerminalMesage();
                } else {
                    view->viewTerminalMessage(it_terminal->second);
                    terminal_msg.erase(it_terminal);
                }
            }
        }
    });
    
    dispatcher->subscribe<void (OpeningMessageViewState)>("update_msg_state", [=](OpeningMessageViewState state) {
        CCLOG("state: %d", state);
        msg_view_state = state;
    });
    
    dispatcher->subscribe<void (TerminalMessageViewState)>("update_terminal_msg_state", [=](TerminalMessageViewState state) {
        CCLOG("state: %d", state);
        terminal_message_view_state = state;
    });
}

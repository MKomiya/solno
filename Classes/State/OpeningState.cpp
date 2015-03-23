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
#include "ViewManager.h"
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
    
    auto view_manager = Raciela::ViewManager::getInstance();
    view_manager->addView(frame);
    view_manager->addView(view);
}

void OpeningState::update()
{
}

void OpeningState::exit()
{
    Raciela::State::exit();
    Raciela::ViewManager::getInstance()->removeView(view);
}

void OpeningState::delegate()
{
    dispatcher->subscribe<void ()>("touched", [=]() {
        if (msg_view_state == OpeningMessageViewState::PROGRESS ||
            terminal_message_view_state == TerminalMessageViewState::PROGRESS)
        {
            return ;
        }

        msg_index++;
        if (normal_msg.size() == 0) {
            auto router = Raciela::Router::getInstance();
            router->replaceState(FieldState::create());
            return ;
        }
        playMessages(OpeningMessageType::NORMAL_MESSAGE);

        if (terminal_msg.size() == 0) {
            return ;
        }
        playMessages(OpeningMessageType::TERMINAL_MESSAGE);
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

void OpeningState::playMessages(OpeningMessageType type)
{
    auto msg_list = getMessageDataRef(type);
    auto it = msg_list.find(msg_index);
    if (it == msg_list.end()) {
        view->nextMessage(type);
    } else {
        view->viewMessage(type, it->second);
        msg_list.erase(it);
    }
}

std::unordered_map<int, std::string>& OpeningState::getMessageDataRef(OpeningMessageType type)
{
    switch (type) {
        case OpeningMessageType::NORMAL_MESSAGE:
            return normal_msg;
        case OpeningMessageType::TERMINAL_MESSAGE:
            return terminal_msg;
    }
}
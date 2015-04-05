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
    
    std::vector<std::string> multi_terminal_buff;
    for (auto it = data_list.begin(); it != data_list.end(); ++it) {
        auto data = (*it);
        
        if (data.type == MasterOpeningType::NORMAL) {
            normal_msg.insert(std::make_pair(data.id, data.msg));
        }
        
        if (data.type == MasterOpeningType::TERMINAL){
            terminal_msg.insert(std::make_pair(data.id, data.msg));
        }
        
        if (data.type == MasterOpeningType::MULTI_TERMINAL) {
            multi_terminal_buff.push_back(data.msg);
            
            auto next = it + 1;
            if (next == data_list.end() || (*next).type != MasterOpeningType::MULTI_TERMINAL) {
                auto id = data.id - multi_terminal_buff.size() + 1;
                multi_terminal_msg.insert(std::make_pair(id, multi_terminal_buff));
                multi_terminal_buff.clear();
            }
        }
        
        if (data.type == MasterOpeningType::CHANGE_STATE) {
            change_state_idx = data.id;
        }
    }
    
    setMsgIndex(0);
    
    return true;
}

void OpeningState::enter()
{
    Raciela::State::enter();
    
    view = OpeningLayer::create();
    auto frame = ControllerLayer::create();
    
    auto view_manager = Raciela::ViewManager::getInstance();
    view_manager->addView(frame);
    view_manager->addView(view);
    
    dispatcher->dispatch("touched");
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
        if (normal_msg.size() != 0) {
            playMessages(OpeningMessageType::NORMAL_MESSAGE);
        }

        if (terminal_msg.size() != 0) {
            playMessages(OpeningMessageType::TERMINAL_MESSAGE);
        }
        
        if (multi_terminal_msg.size() != 0) {
            auto it = multi_terminal_msg.find(msg_index);
            if (it == multi_terminal_msg.end()) {
                return;
            }
            msg_index += it->second.size();
            view->viewMultiMessages(it->second);
            multi_terminal_msg.erase(it);
            return ;
        }

        if (msg_index >= change_state_idx) {
            Raciela::Router::getInstance()->replaceState(FieldState::create());
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

void OpeningState::playMessages(OpeningMessageType type)
{
    auto msg_list = getMessageDataPtr(type);
    auto it = msg_list->find(msg_index);
    if (it == msg_list->end()) {
        view->nextMessage(type);
    } else {
        view->viewMessage(type, it->second);
        msg_list->erase(it);
    }
}

std::unordered_map<int, std::string>* OpeningState::getMessageDataPtr(OpeningMessageType type)
{
    switch (type) {
        case OpeningMessageType::NORMAL_MESSAGE:
            return &normal_msg;
        case OpeningMessageType::TERMINAL_MESSAGE:
            return &terminal_msg;
    }
}
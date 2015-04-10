//
//  OpeningLayer.cpp
//  solno
//
//  Created by S_Wyvern on 2015/02/28.
//
//

#include "OpeningLayer.h"
#include "OpeningMessageView.h"
#include "Dispatcher.h"
#include "TerminalMessageView.h"

USING_NS_CC;

bool OpeningLayer::init()
{
    if (!Raciela::View::init()) {
        return false;
    }
    
    msg_view = OpeningMessageView::create();
    addChild(msg_view);
    
    terminal_msg_view = TerminalMessageView::create();
    addChild(terminal_msg_view);
    
    // add touch event listener
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [](Touch* t, Event* e) -> bool {
        return true;
    };
    listener->onTouchMoved = [](Touch* t, Event* e) {
    };
    listener->onTouchEnded = [=](Touch* t, Event* e) {
        dispatcher->dispatch("touched");
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void OpeningLayer::viewMessage(OpeningMessageType type, std::string msg_data)
{
    switch (type) {
        case OpeningMessageType::NORMAL_MESSAGE:
            viewMainMessages(msg_data);
            break;
        case OpeningMessageType::TERMINAL_MESSAGE:
            viewTerminalMessage(msg_data);
            break;
        default:
            throw "Invalid type";
    }
}

void OpeningLayer::nextMessage(OpeningMessageType type)
{
    switch (type) {
        case OpeningMessageType::NORMAL_MESSAGE:
            nextMainMessages();
            break;
        case OpeningMessageType::TERMINAL_MESSAGE:
            releaseTerminalMesage();
            break;
        default:
            throw "Invalid type";
    }
}

void OpeningLayer::viewMainMessages(std::string msg_data)
{
    msg_view->viewMessage(msg_data);
}

void OpeningLayer::nextMainMessages()
{
    msg_view->releaseMessage();
}

void OpeningLayer::viewTerminalMessage(std::string msg)
{
    terminal_msg_view->viewMessage(msg);
}

void OpeningLayer::releaseTerminalMesage()
{
    terminal_msg_view->releaseMessage();
}

void OpeningLayer::viewMultiMessages(std::vector<std::string> msg_list)
{
    terminal_msg_view->viewMultiMessage(msg_list);
}
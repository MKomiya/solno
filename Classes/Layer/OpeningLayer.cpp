//
//  OpeningLayer.cpp
//  solno
//
//  Created by S_Wyvern on 2015/02/28.
//
//

#include "OpeningLayer.h"
#include "MessageView.h"
#include "Dispatcher.h"

USING_NS_CC;

bool OpeningLayer::init()
{
    if (!Raciela::View::init()) {
        return false;
    }
    
    msg_view = MessageView::create();
    addChild(msg_view);
    
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
    
    return true;
}

void OpeningLayer::viewMessages(std::vector<std::string> msg_data)
{
    msg_view->viewMessages(msg_data);
}

void OpeningLayer::nextMessages()
{
    msg_view->nextMessage();
}
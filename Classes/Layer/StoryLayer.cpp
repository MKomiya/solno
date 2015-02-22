//
//  StoryLayer.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/17.
//
//

#include "StoryLayer.h"

bool StoryLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    msg_view = MessageView::create();
    addChild(msg_view);
    
    return true;
}

void StoryLayer::viewMessages(std::vector<std::string> msg_data)
{
    msg_view->viewMessages(msg_data);
}

void StoryLayer::releaseMessages()
{
    msg_view->nextMessage();
}
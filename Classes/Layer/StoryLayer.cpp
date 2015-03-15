//
//  StoryLayer.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/17.
//
//

#include "StoryLayer.h"
#include "OpeningMessageView.h"

bool StoryLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    msg_view = OpeningMessageView::create();
    addChild(msg_view);
    
    return true;
}

void StoryLayer::viewMessage(std::string msg_data)
{
    msg_view->viewMessage(msg_data);
}

void StoryLayer::releaseMessages()
{
    msg_view->releaseMessage();
}
//
//  StoryLayer.h
//  solno
//
//  Created by S_Wyvern on 2015/01/17.
//
//

#ifndef __solno__StoryLayer__
#define __solno__StoryLayer__

#include <stdio.h>
#include <cocos2d.h>

#include "MessageView.h"

class StoryLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(StoryLayer);
    
    void viewMessages(std::vector<std::string> msg_data);
    void releaseMessages();
    MessageView::ViewState getMessageState();
    
private:
    MessageView* msg_view;
};

#endif /* defined(__solno__StoryLayer__) */

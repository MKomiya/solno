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
#include "View.h"

class OpeningMessageView;
class StoryLayer : public Raciela::View
{
public:
    virtual bool init();
    CREATE_FUNC(StoryLayer);
    
    void viewMessage(std::string msg_data);
    void releaseMessages();
    
private:
    OpeningMessageView* msg_view;
};

#endif /* defined(__solno__StoryLayer__) */

//
//  OpeningLayer.h
//  solno
//
//  Created by S_Wyvern on 2015/02/28.
//
//

#ifndef __solno__OpeningLayer__
#define __solno__OpeningLayer__

#include <stdio.h>
#include <cocos2d.h>

#include "View.h"

class MessageView;
class OpeningLayer : public Raciela::View
{
public:
    virtual bool init();
    CREATE_FUNC(OpeningLayer);
    
    void viewMessages(std::vector<std::string> msg_data);
    void nextMessages();
    
    CC_SYNTHESIZE(MessageView*, msg_view, MessageView);
};

#endif /* defined(__solno__OpeningLayer__) */

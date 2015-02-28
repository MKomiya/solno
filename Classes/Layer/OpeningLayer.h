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

enum class MessageViewState;
enum class TerminalMessageViewState;

class MessageView;
class TerminalMessageView;
class OpeningLayer : public Raciela::View
{
public:
    virtual bool init();
    CREATE_FUNC(OpeningLayer);
    
    void viewMessages(std::vector<std::string> msg_data);
    void nextMessages();
    
    void viewTerminalMessage(std::string msg);
    void releaseTerminalMesage();
    
    CC_SYNTHESIZE(MessageView*, msg_view, MessageView);
    CC_SYNTHESIZE(MessageViewState, msg_view_state, MessageViewState);
    CC_SYNTHESIZE(TerminalMessageView*, terminal_msg_view, TerminalMessageView);
    CC_SYNTHESIZE(TerminalMessageViewState, terminal_msg_view_state, TerminalMessageViewState);
};

#endif /* defined(__solno__OpeningLayer__) */

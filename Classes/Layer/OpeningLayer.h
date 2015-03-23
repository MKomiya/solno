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

enum class OpeningMessageViewState;
enum class TerminalMessageViewState;

enum class OpeningMessageType {
    NORMAL_MESSAGE,
    TERMINAL_MESSAGE,
};

class OpeningMessageView;
class TerminalMessageView;
class OpeningLayer : public Raciela::View
{
public:
    virtual bool init();
    CREATE_FUNC(OpeningLayer);
    
    void viewMessage(OpeningMessageType type, std::string msg_data);
    void nextMessage(OpeningMessageType type);
    
    CC_SYNTHESIZE(OpeningMessageView*, msg_view, MessageView);
    CC_SYNTHESIZE(OpeningMessageViewState, msg_view_state, MessageViewState);
    CC_SYNTHESIZE(TerminalMessageView*, terminal_msg_view, TerminalMessageView);
    CC_SYNTHESIZE(TerminalMessageViewState, terminal_msg_view_state, TerminalMessageViewState);
    
private:
    void viewMainMessages(std::string msg_data);
    void viewTerminalMessage(std::string msg);
    void nextMainMessages();
    void releaseTerminalMesage();
};

#endif /* defined(__solno__OpeningLayer__) */

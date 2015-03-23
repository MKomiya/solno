//
//  OpeningState.h
//  solno
//
//  Created by S_Wyvern on 2015/02/28.
//
//

#ifndef __solno__OpeningState__
#define __solno__OpeningState__

#include <stdio.h>
#include <unordered_map>
#include <cocos2d.h>
#include "State.h"

enum class OpeningMessageViewState;
enum class TerminalMessageViewState;
enum class OpeningMessageType;

class OpeningLayer;
class OpeningState : public Raciela::State
{
public:
    static OpeningState* create();
    
    virtual bool init() override;
    virtual void enter() override;
    virtual void update() override;
    virtual void exit() override;
    virtual void delegate() override;

    CC_SYNTHESIZE(int, msg_index, MsgIndex);
    CC_SYNTHESIZE(OpeningLayer*, view, View);
    CC_SYNTHESIZE(OpeningMessageViewState, msg_view_state, MessageViewState);
    CC_SYNTHESIZE(TerminalMessageViewState, terminal_message_view_state, TerminalMessageViewState);
    
private:
    std::unordered_map<int, std::string> normal_msg;
    std::unordered_map<int, std::string> terminal_msg;
    
    void playMessages(OpeningMessageType type);
    std::unordered_map<int, std::string>& getMessageDataRef(OpeningMessageType type);
};

#endif /* defined(__solno__OpeningState__) */

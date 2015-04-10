//
//  TerminalMessageView.h
//  solno
//
//  Created by S_Wyvern on 2015/03/01.
//
//

#ifndef __solno__TerminalMessageView__
#define __solno__TerminalMessageView__

#include <stdio.h>
#include <cocos2d.h>

enum class TerminalMessageViewState {
    DISABLED,
    PROGRESS,
    WAIT,
};

class TerminalMessageView : public cocos2d::Node
{
public:
    static TerminalMessageView* create();
    void viewMessage(std::string msg);
    void viewMultiMessage(std::vector<std::string> msg_list);
    void update(float dt);
    void updateMultiMessage(float dt);
    void releaseMessage();
    
    CC_SYNTHESIZE(cocos2d::Label*, msg_label, MsgLabel);
    CC_SYNTHESIZE(std::string, msg, Msg);
    CC_SYNTHESIZE(int, string_idx, StringIdx);
    CC_SYNTHESIZE(int, msg_idx, MessageIdx);
    CC_SYNTHESIZE(std::vector<std::string>, multi_msg, MultiMsg);
};

#endif /* defined(__solno__TerminalMessageView__) */

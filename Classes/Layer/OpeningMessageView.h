//
//  OpeningMessageView.h
//  solno
//
//  Created by S_Wyvern on 2015/03/03.
//
//

#ifndef __solno__OpeningMessageView__
#define __solno__OpeningMessageView__

#include <stdio.h>
#include <cocos2d.h>

enum class OpeningMessageViewState {
    DISABLED,
    PROGRESS,
    WAIT,
};

class OpeningMessageView : public cocos2d::Node
{
public:
    static OpeningMessageView* create();
    void viewMessage(std::string msg);
    void update(float dt);
    void releaseMessage();
    
    CC_SYNTHESIZE(cocos2d::Label*, msg_label, MsgLabel);
    CC_SYNTHESIZE(std::string, msg, Msg);
    CC_SYNTHESIZE(int, string_idx, StringIdx);
};

#endif /* defined(__solno__OpeningMessageView__) */

//
//  MessageView.h
//  solno
//
//  Created by S_Wyvern on 2015/01/10.
//
//

#ifndef __solno__MessageView__
#define __solno__MessageView__

#include <stdio.h>
#include <cocos2d.h>

enum class MessageViewState {
    DISABLED,
    PROGRESS,
    HIGH_SPEED,
    WAIT,
    NEXT,
    END,
};

class MessageView : public cocos2d::Node
{
public:
    static MessageView* create(bool visible_window = true);
    void viewMessages(std::vector<std::string> msg_data);
    void updateMessage(float dt);
    void nextMessage();
    void releaseMessages();
    void setMessageColor(cocos2d::Color3B color);
    
    CC_SYNTHESIZE(bool, visible_window, VisibleWindow);
    CC_SYNTHESIZE(cocos2d::Label*, msg_label, MsgLabel);
    CC_SYNTHESIZE(std::vector<std::string>, msg_data, MsgData);
    CC_SYNTHESIZE(std::string, now_msg, NowMsg);
    CC_SYNTHESIZE(int, string_idx, StringIdx);
    CC_SYNTHESIZE(int, msg_idx, msgIdx);
    CC_SYNTHESIZE(cocos2d::Sprite*, msg_window, MsgWindow);
    
private:
    void disabledMessage();
};

#endif /* defined(__solno__MessageView__) */

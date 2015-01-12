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

class MessageView : public cocos2d::Sprite
{
public:
    enum ChildTag {
        MESSAGE_LABEL = 1,
    };
    enum ViewState {
        DISABLED = 1,
        PROGRESS,
        HIGH_SPEED,
        WAIT,
        NEXT,
        END,
    };
    MessageView();
    
    static MessageView* create();
    void viewMessages(std::string msg_data);
    void updateMessage(float dt);
    void releaseMessages();
    
    inline ViewState getState() {
        return state;
    }
    
private:
    ViewState state;
    std::string msg_data;
    int string_idx;
};

#endif /* defined(__solno__MessageView__) */

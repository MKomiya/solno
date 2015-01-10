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
    MessageView(std::string msg_data);
    
    static MessageView* create(std::string msg_data);
    virtual void onEnter();
    virtual void update(float dt);
    
private:
    std::string msg_data;
    int string_idx;
};

#endif /* defined(__solno__MessageView__) */

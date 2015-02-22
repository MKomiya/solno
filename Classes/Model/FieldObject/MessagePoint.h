//
//  MessagePoint.h
//  solno
//
//  Created by S_Wyvern on 2015/01/21.
//
//

#ifndef __solno__MessagePoint__
#define __solno__MessagePoint__

#include <stdio.h>
#include "FieldObject.h"

class FieldLayer;
class MessagePoint : public FieldObject
{
public:
    virtual void executeMovedAction() override;
    virtual void executeDecideAction() override;
    virtual bool isPassablePlayer() override;
    
    CC_SYNTHESIZE(std::string, msg_data, MessageData);
    CC_SYNTHESIZE(bool, decide_trigger, DecideTrigger);
    
private:
    cocos2d::CallFunc* getViewMessageAction(FieldLayer* view);
};

#endif /* defined(__solno__MessagePoint__) */

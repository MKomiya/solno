//
//  StoryState.h
//  solno
//
//  Created by S_Wyvern on 2015/01/17.
//
//

#ifndef __solno__StoryState__
#define __solno__StoryState__

#include <stdio.h>

#include "State.h"
#include "Story.h"

enum class MessageViewState;

class Story;
class StoryLayer;
class StoryState : public Raciela::State
{
public:
    static StoryState* create();
    
    virtual void enter() override;
    virtual void update() override;
    virtual void exit() override;
    virtual void delegate() override;
    
    CC_SYNTHESIZE(MessageViewState, msg_view_state, MsgViewState);
    CC_SYNTHESIZE(int, msg_idx, MsgIdx);
    CC_SYNTHESIZE(Story*, running_story, RunningStory);
    CC_SYNTHESIZE(StoryLayer*, view, View);
    CC_SYNTHESIZE(cocos2d::Vector<Story*>, story_data, StoryData);
};
#endif /* defined(__solno__StoryState__) */

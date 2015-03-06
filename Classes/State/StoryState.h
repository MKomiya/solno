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

class Story;
class StoryLayer;
class StoryState : public Raciela::State
{
public:
    static StoryState* create(StoryLayer* view);
    StoryState(StoryLayer* view);
    virtual ~StoryState();
    
    virtual void enter() override;
    virtual void update() override;
    virtual void exit() override;
    virtual void delegate() override;
    
private:
    StoryLayer* view;
    cocos2d::Vector<Story*> story_data;
    Story* running_story;
    
    int msg_idx;
};
#endif /* defined(__solno__StoryState__) */

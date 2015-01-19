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

#include "StateBase.h"
#include "Story.h"

class Story;
class StoryLayer;
class StoryState : public StateBase
{
public:
    StoryState(StoryLayer* view);
    virtual ~StoryState();
    virtual void update();
    
private:
    StoryLayer* view;
    cocos2d::Vector<Story*> story_data;
    Story* running_story;
    
    int msg_idx;
};
#endif /* defined(__solno__StoryState__) */

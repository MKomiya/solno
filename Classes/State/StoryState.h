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
#include "IState.h"

class Story;
class StoryLayer;
class StoryState : public IState
{
public:
    StoryState(StoryLayer* view);
    virtual ~StoryState();
    virtual void update();
    
private:
    StoryLayer* view;
    std::queue<Story*> story_data;
    Story* running_story;
    
    int msg_idx;
};
#endif /* defined(__solno__StoryState__) */

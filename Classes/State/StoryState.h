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

struct StoryNode
{
    int type;
    std::vector<std::string> msg_data;
    
    StoryNode(int t, std::vector<std::string> m) {
        type     = t;
        msg_data = m;
    }
};

class StoryLayer;
class StoryState : public IState
{
public:
    StoryState(StoryLayer* view);
    virtual ~StoryState();
    virtual void update();
    
private:
    StoryLayer* view;
    std::vector<StoryNode> story_data;
    
    int story_idx, msg_idx;
};
#endif /* defined(__solno__StoryState__) */

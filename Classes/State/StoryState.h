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

class StoryState : public IState
{
public:
    StoryState();
    virtual ~StoryState();
    virtual void update();
};
#endif /* defined(__solno__StoryState__) */

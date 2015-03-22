//
//  StoryPoint.h
//  solno
//
//  Created by S_Wyvern on 2015/03/21.
//
//

#ifndef __solno__StoryPoint__
#define __solno__StoryPoint__

#include <stdio.h>
#include "FieldObject.h"
#include "Direction.h"

class FiledLayer;
class StoryPoint : public FieldObject
{
public:
    virtual void executeDecideAction() override;
    virtual bool isPassablePlayer() override;
    
    CC_SYNTHESIZE(std::string, story_id, StoryId);
};

#endif /* defined(__solno__StoryPoint__) */

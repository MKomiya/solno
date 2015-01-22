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
    virtual void executeMovedAction(FieldLayer* view) override;
};

#endif /* defined(__solno__MessagePoint__) */

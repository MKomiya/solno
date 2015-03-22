//
//  ObjectOperateItem.h
//  solno
//
//  Created by S_Wyvern on 2015/02/07.
//
//

#ifndef __solno__ObjectOperateItem__
#define __solno__ObjectOperateItem__

#include <stdio.h>
#include "Item.h"

class FieldState;
class ObjectOperateItem : public Item
{
public:
    ObjectOperateItem(int id, int item_id);
    
    virtual void useItem(FieldState* state) override;
};

#endif /* defined(__solno__ObjectOperateItem__) */

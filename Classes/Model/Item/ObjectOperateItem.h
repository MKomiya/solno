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

class ObjectOperateItem : public Item
{
    virtual void useItem() override;
};

#endif /* defined(__solno__ObjectOperateItem__) */

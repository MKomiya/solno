//
//  MaterialItem.h
//  solno
//
//  Created by S_Wyvern on 2015/03/07.
//
//

#ifndef __solno__MaterialItem__
#define __solno__MaterialItem__

#include <stdio.h>
#include "Item.h"

class FieldState;
class MaterialItem : public Item
{
    virtual void useItem(FieldState* state) override;
};

#endif /* defined(__solno__MaterialItem__) */

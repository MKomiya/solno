//
//  MenuButtonItem.h
//  solno
//
//  Created by S_Wyvern on 2015/02/28.
//
//

#ifndef __solno__MenuButtonItem__
#define __solno__MenuButtonItem__

#include <stdio.h>
#include <cocos2d.h>

class MenuButtonItem : public cocos2d::MenuItemSprite
{
public:
    static MenuButtonItem* create();
    virtual void selected();
    virtual void unselected();
};

#endif /* defined(__solno__MenuButtonItem__) */

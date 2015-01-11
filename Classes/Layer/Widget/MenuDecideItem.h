//
//  MenuDecideItem.h
//  solno
//
//  Created by S_Wyvern on 2015/01/11.
//
//

#ifndef __solno__MenuDecideItem__
#define __solno__MenuDecideItem__

#include <stdio.h>
#include <cocos2d.h>

class MenuDecideItem : public cocos2d::MenuItemFont
{
public:
    static MenuDecideItem* create();
    virtual void selected();
    virtual void unselected();
};

#endif /* defined(__solno__MenuDecideItem__) */

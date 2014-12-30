//
//  MenuArrowItem.h
//  solno
//
//  Created by S_Wyvern on 2014/12/30.
//
//

#ifndef __solno__MenuArrowItem__
#define __solno__MenuArrowItem__

#include <stdio.h>
#include <cocos2d.h>


class MenuArrowItem : public cocos2d::MenuItemFont
{
public:
    MenuArrowItem(std::string direction);
    static MenuArrowItem* create(std::string direction);
    virtual void selected();
    virtual void unselected();
    
private:
    std::string _direction;
};

#endif /* defined(__solno__MenuArrowItem__) */

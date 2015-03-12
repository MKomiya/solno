//
//  FieldControllerLayer.h
//  solno
//
//  Created by S_Wyvern on 2015/02/26.
//
//

#ifndef __solno__FieldControllerLayer__
#define __solno__FieldControllerLayer__

#include <stdio.h>
#include <cocos2d.h>

#include "View.h"

class FieldControllerLayer : public Raciela::View
{
public:
    virtual bool init();
    CREATE_FUNC(FieldControllerLayer);
    
    void setEnableArrowButtons(bool enabled);
    
private:
    cocos2d::Menu* arrow_menu;
};

#endif /* defined(__solno__FieldControllerLayer__) */

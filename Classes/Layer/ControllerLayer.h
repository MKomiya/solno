//
//  ControllerLayer.h
//  solno
//
//  Created by S_Wyvern on 2014/12/27.
//
//

#ifndef __solno__ControllerLayer__
#define __solno__ControllerLayer__

#include <stdio.h>
#include <cocos2d.h>

#include "View.h"

class ControllerLayer : public Raciela::View
{
public:
    virtual bool init();
    CREATE_FUNC(ControllerLayer);
    
    void setEnableArrowButtons(bool enabled);
    
private:
    cocos2d::Menu* arrow_menu;
};

#endif /* defined(__solno__ControllerLayer__) */

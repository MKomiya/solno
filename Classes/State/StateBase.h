//
//  StateBase.h
//  solno
//
//  Created by S_Wyvern on 2014/12/30.
//
//

#ifndef solno_StateBase_h
#define solno_StateBase_h

#include <stdio.h>
#include <cocos2d.h>

class StateBase : public cocos2d::Ref {
public:
    virtual ~StateBase(){}
    virtual void enter(int gate);
    virtual void update();
    virtual void exit();
};

#endif

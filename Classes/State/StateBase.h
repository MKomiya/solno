//
//  StateBase.h
//  solno
//
//  Created by S_Wyvern on 2014/12/30.
//
//

#ifndef solno_StateBase_h
#define solno_StateBase_h

#include <cocos2d.h>

class StateBase : public cocos2d::Ref {
public:
    virtual ~StateBase(){}
    virtual void update() = 0;
};

#endif

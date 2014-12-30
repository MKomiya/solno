//
//  FieldState.h
//  solno
//
//  Created by S_Wyvern on 2014/12/30.
//
//

#ifndef __solno__FieldState__
#define __solno__FieldState__

#include <stdio.h>
#include "IState.h"
#include "FieldState.h"

class FieldLayer;
class FieldState : public IState {
public:
    FieldState(FieldLayer* view);
    virtual void update();
    
private:
    FieldLayer* _view;
};

#endif /* defined(__solno__FieldState__) */

//
//  FieldState.cpp
//  solno
//
//  Created by S_Wyvern on 2014/12/30.
//
//

#include "FieldState.h"
#include "InputModule.h"

#include "FieldLayer.h"

FieldState::FieldState(FieldLayer* view) :
_view(view)
{
}

void FieldState::update()
{
    CCLOG("FieldState: update");
    
    auto command = InputModule::getInstance()->getInputCommand();
    
    if (command == InputCommand::MOVE_UP) {
        _view->changePlayerAnimation("up");
    } else if (command == InputCommand::MOVE_LEFT) {
        _view->changePlayerAnimation("left");
    } else if (command == InputCommand::MOVE_DOWN) {
        _view->changePlayerAnimation("down");
    } else if (command == InputCommand::MOVE_RIGHT) {
        _view->changePlayerAnimation("right");
    }
}
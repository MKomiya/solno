//
//  MessagePoint.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/21.
//
//

#include <json11.hpp>

#include "MessagePoint.h"

#include "FieldState.h"
#include "FieldLayer.h"
#include "ControllerLayer.h"
USING_NS_CC;

void MessagePoint::executeMovedAction()
{
    if (decide_trigger) {
        return ;
    }
    
    auto view       = state->getFieldView();
    auto controller = state->getControllerView();
    
    controller->setEnableArrowButtons(false);
    auto action = getViewMessageAction(view);
    view->addRunActionAfterMove(action);
}

void MessagePoint::executeDecideAction()
{
    if (!decide_trigger) {
        return ;
    }
    
    auto view       = state->getFieldView();
    auto controller = state->getControllerView();
    
    controller->setEnableArrowButtons(false);
    auto action = getViewMessageAction(view);
    view->runAction(action);
}

bool MessagePoint::isPassablePlayer()
{
    return !decide_trigger;
}

cocos2d::CallFunc* MessagePoint::getViewMessageAction(FieldLayer* view)
{
    auto action = CallFunc::create([this,view]() {
        std::vector<std::string> args; std::string err;
        auto data = json11::Json::parse(msg_data, err);
        for (auto v : data.array_items()) {
            args.push_back(v.string_value());
        }
        view->viewMessages(args);
    });
    return action;
}
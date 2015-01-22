//
//  MessagePoint.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/21.
//
//

#include <json11.hpp>

#include "MessagePoint.h"

#include "FieldLayer.h"

USING_NS_CC;

void MessagePoint::executeMovedAction(FieldLayer* view)
{
    // controller->setEnableArrowButtons(false);
    auto action = CallFunc::create([=]() {
        std::vector<std::string> args; std::string err;
        auto data = json11::Json::parse(getOptionalParams(), err);
        for (auto v : data.array_items()) {
            args.push_back(v.string_value());
        }
        view->viewMessages(args);
    });
    view->addRunActionAfterMove(action);
}
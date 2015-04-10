//
//  Tree.cpp
//  solno
//
//  Created by S_Wyvern on 2015/02/26.
//
//

#include "Tree.h"
#include "FieldState.h"
#include "FieldLayer.h"
#include "FieldControllerLayer.h"

USING_NS_CC;

Tree::Tree(FieldState* state, int id, cocos2d::ValueMap data) :
    FieldObject(state, id, data)
{
}

void Tree::executeDecideAction()
{
    auto view       = state->getFieldView();
    auto controller = state->getControllerView();
    
    controller->setEnableArrowButtons(false);
    view->runAction(CallFunc::create([view]() {
        std::vector<std::string> msg_data;
        msg_data.push_back("斧で壊せそうだ");
        view->viewMessages(msg_data);
    }));
}

bool Tree::isPassablePlayer()
{
    return false;
}

int Tree::getBreakItemId()
{
    return 3; // 斧プラグイン
}
//
//  ObjectOperateItem.cpp
//  solno
//
//  Created by S_Wyvern on 2015/02/07.
//
//

#include "ObjectOperateItem.h"
#include "FieldState.h"
#include "FieldObject.h"
#include "FieldLayer.h"

void ObjectOperateItem::useItem(FieldState* state)
{
    auto break_object = state->findPlayerDirectionAbutObject();
    if (break_object == nullptr) {
        CCLOG("ここでは使えない");
        return ;
    }
    
    if (break_object->getBreakItemId() != getItemId()) {
        auto name = getItemName();
        CCLOG("%sでは壊せそうもない", name.c_str());
        return ;
    }
    
    auto view = state->getFieldView();
    view->destroyObject(getId());
    state->deleteObject(break_object);
}
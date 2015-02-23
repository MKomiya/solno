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

void ObjectOperateItem::useItem()
{
    CCLOG("アイテム使用");
    /*
    auto break_object = state->findPlayerDirectionAbutObject();
    if (break_object == nullptr) {
        CCLOG("ここでは使えない");
        return ;
    }
    
    if (break_object->getObjectType() != FieldObject::ObjectType::TREE) {
        auto name = getItemName();
        CCLOG("%sでは壊せそうもない", name.c_str());
        return ;
    }
    
    // 破壊処理（とりあえず木を壊すだけ）
    state->deleteObject(break_object);
    */
}
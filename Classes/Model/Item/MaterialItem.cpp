//
//  MaterialItem.cpp
//  solno
//
//  Created by S_Wyvern on 2015/03/07.
//
//

#include "MaterialItem.h"
#include "FieldState.h"

MaterialItem::MaterialItem(int id, int item_id) :
    Item(id, item_id)
{
}

void MaterialItem::useItem(FieldState* state)
{
    CCLOG("このアイテムは使えない");
}
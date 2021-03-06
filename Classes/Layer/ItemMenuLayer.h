//
//  ItemMenuLayer.h
//  solno
//
//  Created by S_Wyvern on 2015/01/28.
//
//

#ifndef __solno__ItemMenuLayer__
#define __solno__ItemMenuLayer__

#include <stdio.h>
#include <cocos2d.h>

#include "View.h"
#include "Item.h"

class ItemMenuLayer : public Raciela::View
{
public:
    static const int VIEW_ITEM_W = 4;
    static const int VIEW_ITEM_H = 4;
    
    static ItemMenuLayer* create(cocos2d::Vector<Item*> &item_list);
    virtual bool init();
    
    // カーソルアイテム更新
    void updateViewItem(int index);
    
    CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Vector<Item*>, item_list, ItemList);
    CC_SYNTHESIZE_READONLY(cocos2d::Sprite*, current_cursor, CurrentCursor);
    CC_SYNTHESIZE_READONLY(cocos2d::Label*, name_label, NameLabel);
    CC_SYNTHESIZE_READONLY(cocos2d::Sprite*, prepare_item_1, PrepareItem1);
    CC_SYNTHESIZE_READONLY(cocos2d::Sprite*, prepare_item_2, PrepareItem2);
    CC_SYNTHESIZE_READONLY(cocos2d::Sprite*, prepare_item_3, PrepareItem3);
};

#endif /* defined(__solno__ItemMenuLayer__) */

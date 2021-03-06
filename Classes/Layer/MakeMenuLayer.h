//
//  MakeMenuLayer.h
//  solno
//
//  Created by Mitsushige Komiya on 2015/01/29.
//
//

#ifndef __solno__MakeMenuLayer__
#define __solno__MakeMenuLayer__

#include <iostream>
#include <cocos2d.h>
#include "View.h"
#include "Item.h"

class MakeMenuLayer : public Raciela::View
{
public:
    static const int VIEW_ITEM_W = 4;
    static const int VIEW_ITEM_H = 4;
    
    static MakeMenuLayer* create(cocos2d::Vector<Item*> &item_list);
    virtual bool init();
    
    // カーソルアイテム更新
    void updateViewItem(int index);
    
    void invisibleItemIcon(int index);
    void setOpacityItemIconAll(int value);
    void visibleItemIcons(std::vector<int> indices);
    void setPreparentItemTexture(int preparent_index, cocos2d::Texture2D* texture);
    void invisiblePreparentItem(int preparent_index);
    void showResult(const Item* maked_item);
    
    CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Vector<Item*>, item_list, ItemList);
    CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Vector<cocos2d::MenuItem*>, item_icon_list, ItemIconList);
    CC_SYNTHESIZE_READONLY(cocos2d::Sprite*, current_cursor, CurrentCursor);
    CC_SYNTHESIZE_READONLY(cocos2d::Label*, name_label, NameLabel);
    CC_SYNTHESIZE_READONLY(cocos2d::MenuItemSprite*, prepare_item_1, PrepareItem1);
    CC_SYNTHESIZE_READONLY(cocos2d::MenuItemSprite*, prepare_item_2, PrepareItem2);
    CC_SYNTHESIZE_READONLY(cocos2d::MenuItemSprite*, prepare_item_3, PrepareItem3);
};

#endif /* defined(__solno__MakeMenuLayer__) */

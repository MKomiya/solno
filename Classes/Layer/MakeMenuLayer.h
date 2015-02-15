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

#include "Item.h"

class MakeMenuLayer : public cocos2d::Layer
{
public:
    static const int VIEW_ITEM_W = 4;
    static const int VIEW_ITEM_H = 4;
    
    static MakeMenuLayer* create(cocos2d::Vector<Item*> &item_list);
    virtual bool init();
    
    // カーソルアイテム更新
    void updateViewItem(int index);
    
    void invisibleItemIcon(int index);
    void invisibleItemIconAll();
    void visibleItemIcons(std::vector<int> indices);
    
    CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Vector<Item*>, item_list, ItemList);
    CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Vector<cocos2d::MenuItem*>, item_icon_list, ItemIconList);
    CC_SYNTHESIZE_READONLY(cocos2d::Sprite*, current_cursor, CurrentCursor);
    CC_SYNTHESIZE_READONLY(cocos2d::Label*, name_label, NameLabel);
    CC_SYNTHESIZE(int, current_item_idx, CurrentItemIdx);
};

#endif /* defined(__solno__MakeMenuLayer__) */

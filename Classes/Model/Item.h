//
//  Item.h
//  solno
//
//  Created by S_Wyvern on 2015/01/28.
//
//

#ifndef __solno__Item__
#define __solno__Item__

#include <stdio.h>
#include <cocos2d.h>

class FieldState;
class Item : public cocos2d::Ref
{
public:
    enum EventType {
        BREAK_TREE = 1,
        BREAK_SCRAP,
    };
    enum ItemType {
        OPERATE_OBJECT = 1, // ダンジョンオブジェクトの破壊・生成アイテム
        MATERIAL_ITEM,      // 調合用素材アイテム
        FLAGMENT_ITEM,      // フラグに影響を及ぼすアイテム
    };
    
    static Item* createMock(int id);
    static Item* createByMaster(int item_id);
    
    virtual void useItem(FieldState* state);

    cocos2d::Texture2D* getPrepareItemTexture(int prepare_index);
    Item* getMakeItem();

    CC_SYNTHESIZE(int, id, Id);
    CC_SYNTHESIZE(int, item_id, ItemId);
    CC_SYNTHESIZE(std::string, item_name, ItemName);
    CC_SYNTHESIZE(int, type, Type);
    CC_SYNTHESIZE(int, num, Num);
    CC_SYNTHESIZE(cocos2d::Texture2D*, thumb_texture, ThumbnailTexture);
    CC_SYNTHESIZE(int, prepare_item_id_1, PrepareItemId1);
    CC_SYNTHESIZE(int, prepare_item_id_2, PrepareItemId2);
    CC_SYNTHESIZE(int, prepare_item_id_3, PrepareItemId3);
};

#endif /* defined(__solno__Item__) */

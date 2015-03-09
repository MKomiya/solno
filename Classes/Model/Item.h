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
#include "json11.hpp"

class MasterItem
{
public:
    int item_id, type;
    std::string name;
    int preparent_item_1_id, preparent_item_2_id, preparent_item_3_id;
    
    MasterItem() : item_id(0) {}
    MasterItem(json11::Json::object data) :
    item_id(data["item_id"].int_value()), type(data["type"].int_value()),
    name(data["name"].string_value()),
    preparent_item_1_id(data["preparent_item_1_id"].int_value()),
    preparent_item_2_id(data["preparent_item_2_id"].int_value()),
    preparent_item_3_id(data["preparent_item_3_id"].int_value())
    {}
};

class UserItem
{
public:
    static int index;
    int id, item_id, num;
    
    UserItem() :
    id(-1), item_id(0), num(0) {}
    UserItem(int id, int item_id, int num) :
    id(id), item_id(item_id), num(num) {}
    UserItem(json11::Json::object data) :
    id(data["id"].int_value()),
    item_id(data["item_id"].int_value()),
    num(data["num"].int_value()) {}
    
    json11::Json to_json() const
    {
        return json11::Json::object {
            { "id", id },
            { "item_id", item_id },
            { "num", num }
        };
    }
};

const MasterItem MasterItemNull;
const UserItem   UserItemNull;

class FieldState;
class Item : public cocos2d::Ref
{
public:
    enum EventType {
        BREAK_TREE = 1,
        BREAK_SCRAP,
    };
    enum ItemType {
        MATERIAL_ITEM = 1,  // 調合用素材アイテム
        OPERATE_OBJECT,     // ダンジョンオブジェクトの破壊・生成アイテム
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

//
//  MasterStorageModule.h
//  solno
//
//  Created by S_Wyvern on 2015/02/01.
//
//

#ifndef __solno__MasterStorageModule__
#define __solno__MasterStorageModule__

#include <stdio.h>
#include <cocos2d.h>
#include <dispatch/dispatch.h>
#include <unordered_map>

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

const MasterItem MasterItemNull;

class MasterStorageModule
{
public:
    static std::string MASTER_NS_ITEM;
    
    static MasterStorageModule* getInstance() {
        static dispatch_once_t token;
        dispatch_once(&token, ^{
            if (!instance) {
                instance = new MasterStorageModule();
            }
        });
        return instance;
    }
    
    void init();
    
#pragma mark Read master data
    std::vector<MasterItem> getAll();
    MasterItem getOne(int id);
    std::vector<int> findPrepareItemIdsByItemId(int item_id);

#pragma mark Private funcs
private:
    json11::Json loadJsonData(std::string filepath);
    
    static MasterStorageModule* instance;
    std::vector<MasterItem> master_item_list;
};

#endif /* defined(__solno__MasterStorageModule__) */

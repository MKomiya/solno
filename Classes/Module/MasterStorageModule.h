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
    json11::Json::array getAll(std::string ns);
    json11::Json::object getOne(std::string ns, int id);
    json11::Json::array findPrepareItemIdsByItemId(int item_id);

#pragma mark Private funcs
private:
    json11::Json loadJsonData(std::string filepath);
    
    static MasterStorageModule* instance;
    json11::Json::object master_data;
};

#endif /* defined(__solno__MasterStorageModule__) */

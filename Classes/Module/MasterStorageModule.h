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

#include "Item.h"
#include "Opening.h"
#include "Story.h"

class MasterStorageModule
{
public:
    static std::string MASTER_NS_ITEM;
    static std::string MASTER_NS_OPENING;
    static std::string MASTER_NS_STORY;
    
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
    
#pragma mark Read item master
    std::vector<MasterItem> getAll();
    MasterItem getOne(int id);
    std::vector<int> findPrepareItemIdsByItemId(int item_id);
    
#pragma mark Read opening master
    std::vector<MasterOpening> getOpeningList();
    
#pragma mark Read story master
    std::vector<MasterStory> getStoryList();
    MasterStory getStoryDataById(std::string story_id);

#pragma mark Private funcs
private:
    json11::Json loadJsonData(std::string filepath);
    
    static MasterStorageModule* instance;
    std::vector<MasterItem> master_item_list;
    std::vector<MasterOpening> master_opening_list;
    std::vector<MasterStory> master_story_list;
    std::unordered_map<std::string, MasterStory> master_story_map;
};

#endif /* defined(__solno__MasterStorageModule__) */

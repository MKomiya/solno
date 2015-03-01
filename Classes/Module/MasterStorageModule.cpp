//
//  MasterStorageModule.cpp
//  solno
//
//  Created by S_Wyvern on 2015/02/01.
//
//

#include <fstream>
#include "MasterStorageModule.h"
#include "Template.h"

std::string MasterStorageModule::MASTER_NS_ITEM = "item";
std::string MasterStorageModule::MASTER_NS_OPENING = "opening";
MasterStorageModule* MasterStorageModule::instance;

USING_NS_CC;

void MasterStorageModule::init()
{
    auto master = loadJsonData("data/master.json");
    for (auto data : master[MASTER_NS_ITEM].array_items()) {
        auto master_item = MasterItem(data.object_items());
        master_item_list.push_back(master_item);
    }
    
    for (auto data : master[MASTER_NS_OPENING].array_items()) {
        auto master_opening = MasterOpening(data.object_items());
        master_opening_list.push_back(master_opening);
    }
}

#pragma mark Read master data
std::vector<MasterItem> MasterStorageModule::getAll()
{
    return master_item_list;
}

MasterItem MasterStorageModule::getOne(int id)
{
    for (auto master_item : master_item_list) {
        if (master_item.item_id == id) {
            return master_item;
        }
    }
    return MasterItemNull;
}

std::vector<int> MasterStorageModule::findPrepareItemIdsByItemId(int item_id)
{
    auto ret = std::vector<int>();
    for (auto master_item : master_item_list) {
        if (master_item.preparent_item_1_id == item_id ||
            master_item.preparent_item_2_id == item_id ||
            master_item.preparent_item_3_id == item_id) {
            ret.push_back(master_item.item_id);
        }
    }
    return ret;
}

std::vector<MasterOpening> MasterStorageModule::getOpeningList()
{
    return master_opening_list;
}

#pragma mark Private funcs
json11::Json MasterStorageModule::loadJsonData(std::string filepath)
{
    auto path = FileUtils::getInstance()->fullPathForFilename(filepath);
    
    std::ifstream file(path.c_str());
    std::string json_string, err;
    file >> json_string;
    file.close();
    
    json11::Json json = json11::Json::parse(json_string, err);
    return json;
}
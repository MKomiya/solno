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
MasterStorageModule* MasterStorageModule::instance;

USING_NS_CC;

void MasterStorageModule::init()
{
    auto master = loadJsonData("data/master.json");
    for (auto data : master[MASTER_NS_ITEM].array_items()) {
        auto master_item = MasterItem(data.object_items());
        master_item_list.push_back(master_item);
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
        if (master_item.prepare_item_1_id == item_id ||
            master_item.prepare_item_2_id == item_id ||
            master_item.prepare_item_3_id == item_id) {
            ret.push_back(master_item.item_id);
        }
    }
    return ret;
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
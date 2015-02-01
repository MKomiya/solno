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
    master_data = master.object_items();
}

#pragma mark Read master data
json11::Json::array MasterStorageModule::getAll(std::string ns)
{
    return master_data[ns].array_items();
}

json11::Json::object MasterStorageModule::getOne(std::string ns, int id)
{
    std::string primary_key_label = "id";
    if (!ns.empty()) {
        auto tmp_model = Template::create("#ns#_id");
        tmp_model->assign("#ns#", ns);
        primary_key_label = tmp_model->getString();
    }
    
    auto data = master_data[ns].array_items();
    for (auto elem : data) {
        if (elem[primary_key_label] == id) {
            return elem.object_items();
        }
    }
    
    auto empty = json11::Json::object{};
    return empty;
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
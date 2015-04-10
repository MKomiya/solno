//
//  UserStorageModule.cpp
//  solno
//
//  Created by S_Wyvern on 2015/02/01.
//
//

#include <fstream>

#include "UserStorageModule.h"
#include "Item.h"
#include "Player.h"

int UserItem::index = 1;
std::string UserStorageModule::NS_USER_ITEM = "item";
std::string UserStorageModule::NS_PLAYER_POSITION = "player";
UserStorageModule* UserStorageModule::instance;

USING_NS_CC;

void UserStorageModule::init()
{
    auto user_item_json = readJsonFile(NS_USER_ITEM);
    
    for (auto value : user_item_json) {
        auto data = value.object_items();
        auto ret  = UserItem(data);
        user_item.push_back(ret);
    }
}

void UserStorageModule::flush()
{
    std::string out = json11::Json(user_item).dump();
    writeJsonFile(NS_USER_ITEM, out);
}

#pragma mark Read user data
std::vector<UserItem> UserStorageModule::getAllUserItem()
{
    return user_item;
}

UserItem UserStorageModule::getOneUserItem(int item_id)
{
    for (auto value : user_item) {
        if (value.item_id == item_id) {
            return value;
        }
    }
    return UserItemNull;
}

cocos2d::Point UserStorageModule::getPlayerPosition()
{
    return player_pos;
}

#pragma mark Update user data
void UserStorageModule::updateUserItem(int item_id, int num)
{
    auto it = user_item.begin();
    for (UserItem& value : user_item) {
        if (value.item_id == item_id) {
            if (num <= 0) {
                user_item.erase(it);
                flush();
                return ;
            }
            value.num = num;
            flush();
            return ;
        }
        ++it;
    }
    
    user_item.push_back(UserItem(UserItem::index++, item_id, num));
    flush();
}

void UserStorageModule::updatePlayerPosition(int map_id, cocos2d::Point pos)
{
    player_pos = pos;
    
    auto data = Player(map_id, player_pos);
    writeJsonFile(NS_PLAYER_POSITION, data.to_json().dump());
}

void UserStorageModule::writeJsonFile(std::string ns, std::string data)
{
    auto fu = FileUtils::getInstance();
    
    std::string userdata_root =
        fu->getWritablePath() + "userdata/";
    std::string filepath =
        userdata_root + "user_" + ns + ".json";
    
    if (!fu->isDirectoryExist(userdata_root)) {
        fu->createDirectory(userdata_root);
    }
    
    std::ofstream file(filepath.c_str());
    file << data.c_str();
    file.close();
}

json11::Json::array UserStorageModule::readJsonFile(std::string ns)
{
    auto fu = FileUtils::getInstance();
    std::string filepath =
        fu->getWritablePath() + "userdata/user_" + ns + ".json";

    if (!fu->isFileExist(filepath)) {
        return json11::Json::array();
    }
    
    std::string json_string, err;
    std::ifstream file(filepath.c_str());
    while(!file.eof()) {
        std::string buf; file >> buf;
        json_string += buf;
    }
    file.close();
    
    return json11::Json::parse(json_string, err).array_items();
}

json11::Json::array UserStorageModule::readMockData()
{
    return json11::Json::array {
        json11::Json::object {
            { "id", 1 },
            { "item_id", 1 },
            { "num", 2 }
        },
        json11::Json::object {
            { "id", 2 },
            { "item_id", 2 },
            { "num", 2 }
        },
    };
}

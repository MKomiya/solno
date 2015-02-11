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

std::string UserStorageModule::NS_USER_ITEM = "item";
UserStorageModule* UserStorageModule::instance;

USING_NS_CC;

void UserStorageModule::init()
{
}

#pragma mark Read user data
ValueMap UserStorageModule::getOneUserItem(int id)
{
    auto data = readValueMap(NS_USER_ITEM);
    
    if (data.at("id").asInt() == id) {
        return data;
    }
    
    return ValueMapNull;
}

#pragma mark Update user data
void UserStorageModule::updateUserItem(Item *item)
{
    auto id  = cocos2d::Value(item->getId());
    auto num = cocos2d::Value(item->getNum());
    
    ValueMap data, row;
    row.insert(std::make_pair("id", id));
    row.insert(std::make_pair("num", num));
    
    writeValueMap(NS_USER_ITEM, data);
}

void UserStorageModule::writeValueMap(std::string ns, ValueMap data)
{
    auto fu = FileUtils::getInstance();
    std::string filepath =
        fu->getWritablePath() + "userdata/user_" + ns + ".plist";
    fu->writeToFile(data, filepath);
}

ValueMap UserStorageModule::readValueMap(std::string ns)
{
    auto fu = FileUtils::getInstance();
    /*
    std::string filepath =
        fu->getWritablePath() + "userdata/user_" + ns + ".plist";
    */
    std::string filepath = fu->fullPathForFilename("data/userdata.plist");
    return fu->getValueMapFromFile(filepath);
}
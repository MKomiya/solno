//
//  StorageModule.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/16.
//
//

#include "StorageModule.h"

USING_NS_CC;

void StorageModule::open()
{
    auto file_path = FileUtils::getInstance()->getWritablePath();
    file_path.append("User.db");
    
    auto status = sqlite3_open(file_path.c_str(), &user_db);
    
    if (status != SQLITE_OK) {
        throw "sqlite open failed";
    }
}

void StorageModule::increaseUserItem(int item_id)
{
    char* err;
    auto query = "INSERT INTO user_item(item_id, num) VALUES(" + std::to_string(item_id) + ", 1)";
    sqlite3_exec(user_db, query.c_str(), nullptr, nullptr, &err);
}

void StorageModule::close()
{
    sqlite3_close(user_db);
}
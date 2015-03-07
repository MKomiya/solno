//
//  UserStorageModule.h
//  solno
//
//  Created by S_Wyvern on 2015/02/01.
//
//

#ifndef __solno__UserStorageModule__
#define __solno__UserStorageModule__

#include <stdio.h>
#include <dispatch/dispatch.h>
#include <cocos2d.h>
#include "json11.hpp"

class UserItem;
class UserStorageModule
{
public:
    static std::string NS_USER_ITEM;
    
    static UserStorageModule* getInstance() {
        static dispatch_once_t token;
        dispatch_once(&token, ^{
            if (!instance) {
                instance = new UserStorageModule();
            }
        });
        return instance;
    }
    
    void init();
    void flush();
    
#pragma mark Read user data
    std::vector<UserItem> getAllUserItem();
    UserItem getOneUserItem(int id);
    
#pragma mark Update user data
    void updateUserItem(int item_id, int num);
    
private:
    void writeJsonFile(std::string ns, std::string data);
    json11::Json::array readJsonFile(std::string ns);
    json11::Json::array readMockData();

    static UserStorageModule* instance;
    std::vector<UserItem> user_item;
};

#endif /* defined(__solno__UserStorageModule__) */

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

class Item;
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
    
#pragma mark Read user data
    cocos2d::ValueMap getOneUserItem(int id);
    
#pragma mark Update user data
    void updateUserItem(Item* item);
    
    void writeValueMap(std::string ns, cocos2d::ValueMap data);
    cocos2d::ValueMap readValueMap(std::string ns);
    
private:
    static UserStorageModule* instance;
    cocos2d::ValueMap user_item;
};

#endif /* defined(__solno__UserStorageModule__) */

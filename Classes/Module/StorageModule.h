//
//  StorageModule.h
//  solno
//
//  Created by S_Wyvern on 2015/01/16.
//
//

#ifndef __solno__StorageModule__
#define __solno__StorageModule__

#include <stdio.h>
#include <cocos2d.h>
#include "sqlite3.h"

class StorageModule
{
public:
    static StorageModule* getInstance() {
        if (!_instance) {
            _instance = new StorageModule();
        }
        return _instance;
    }
    
    void open();
    void increaseUserItem(int item_id);
    void close();
    
private:
    static StorageModule* _instance;
    
    sqlite3* user_db;
};

#endif /* defined(__solno__StorageModule__) */

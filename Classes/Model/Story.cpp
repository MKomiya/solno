//
//  Story.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/19.
//
//

#include "Story.h"

Story* Story::createByJson(json11::Json json)
{
    auto type = json["type"].int_value();
    auto msg_data = json["msg_data"].string_value();
    
    return create(type, msg_data);
}

Story* Story::create(int type, std::string msg_data)
{
    auto ret = new Story();
    if (!ret) {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    ret->autorelease();
    
    ret->setType(type);
    ret->setMsgData(msg_data);
    
    return ret;
}
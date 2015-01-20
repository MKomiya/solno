//
//  Story.h
//  solno
//
//  Created by S_Wyvern on 2015/01/19.
//
//

#ifndef __solno__Story__
#define __solno__Story__

#include <stdio.h>
#include <json11.hpp>
#include <cocos2d.h>

class Story : public cocos2d::Ref
{
public:
    static Story* createByJson(json11::Json json);
    static Story* create(int type, std::vector<std::string> msg_data);

    CC_SYNTHESIZE(int, type, Type);
    CC_SYNTHESIZE(std::vector<std::string>, msg_data, MsgData);
};

#endif /* defined(__solno__Story__) */

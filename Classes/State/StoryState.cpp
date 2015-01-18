//
//  StoryState.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/17.
//
//

#include "StoryState.h"

#include <cocos2d.h>
#include <json11.hpp>
#include <fstream>
#include <iostream>

USING_NS_CC;

StoryState::StoryState()
{
    auto path = FileUtils::getInstance()->fullPathForFilename("story/mock.json");
    
    std::ifstream file(path.c_str());
    
    std::string mock_data; file >> mock_data;
    std::string err;
    
    file.close();
    
    auto data = json11::Json::parse(mock_data, err);
    for (auto item : data.array_items()) {
        if (item["msg_data"].is_null()) {
            continue;
        }
        for (auto msg : item["msg_data"].array_items()) {
            CCLOG("%s", msg.string_value().c_str());
        }
    }
}

StoryState::~StoryState()
{
}

void StoryState::update()
{
}
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

#include "InputModule.h"
#include "StoryLayer.h"

USING_NS_CC;

StoryState::StoryState(StoryLayer* view) :
running_story(StoryNode(0, std::vector<std::string>())),
view(view),msg_idx(0)
{
    auto path = FileUtils::getInstance()->fullPathForFilename("story/mock.json");
    
    std::ifstream file(path.c_str());
    
    std::string mock_data; file >> mock_data;
    std::string err;
    
    file.close();
    
    auto data = json11::Json::parse(mock_data, err);
    for (auto item : data.array_items()) {
        if (item["type"].is_null() || item["type"].int_value() != 1) {
            CCLOG("invalid story node. type: %d", item["type"].int_value());
            continue;
        }
        
        std::vector<std::string> msg_data;
        for (auto msg : item["msg_data"].array_items()) {
            msg_data.push_back(msg.string_value());
        }
        story_data.push(StoryNode(1, msg_data));
    }
    
    running_story = story_data.front();
    view->viewMessages(running_story.msg_data);
    story_data.pop();
}

StoryState::~StoryState()
{
}

void StoryState::update()
{
    auto event = InputModule::getInstance()->popEvent();
    
    if (event == InputEvent::RELEASE_DECIDE) {
        // message view disabled
        if (view->getMessageState() == MessageView::WAIT) {
            if (running_story.msg_data.size() <= ++msg_idx) {
                if (story_data.empty()) {
                    view->releaseMessages();
                    return;
                }
                
                msg_idx = 0;
                running_story = story_data.front();
                view->viewMessages(running_story.msg_data);
                story_data.pop();
                
            } else {
                view->releaseMessages();
            }
        }
    }
}
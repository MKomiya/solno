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

#include "Story.h"

USING_NS_CC;

StoryState* StoryState::create(StoryLayer *view)
{
    auto ret = new StoryState(view);
    if (!ret) {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    ret->autorelease();
    return ret;
}

StoryState::StoryState(StoryLayer* view) :
running_story(nullptr),
view(view),msg_idx(0)
{
}

StoryState::~StoryState()
{
}

void StoryState::enter()
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
        auto s = Story::createByJson(item);
        story_data.pushBack(s);
    }
    
    running_story = story_data.front();
    view->viewMessages(running_story->getMsgData());
}

void StoryState::update()
{
    auto event = InputModule::getInstance()->popEvent();
    
    if (event == InputEvent::RELEASE_DECIDE) {
        // message view disabled
        /*
        if (view->getMessageState() == MessageView::WAIT) {
            if (running_story->getMsgData().size() <= ++msg_idx) {
                story_data.erase(0);
                if (story_data.empty()) {
                    view->releaseMessages();
                    return;
                }
                
                msg_idx = 0;
                running_story = story_data.front();
                view->viewMessages(running_story->getMsgData());
            } else {
                view->releaseMessages();
            }
        }
        */
    }
}

void StoryState::exit()
{
    story_data.clear();
}
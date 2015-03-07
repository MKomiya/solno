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

#include "StoryLayer.h"
#include "Dispatcher.h"
#include "Story.h"
#include "MessageView.h"

USING_NS_CC;

StoryState* StoryState::create()
{
    auto ret = new StoryState();
    if (!ret) {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    ret->autorelease();
    
    ret->init();
    ret->setMsgIdx(0);
    ret->setRunningStory(nullptr);
    ret->setView(StoryLayer::create());
    ret->setMsgViewState(MessageViewState::DISABLED);
    ret->created();
    return ret;
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

void StoryState::delegate()
{
    dispatcher->subscribe<void (MessageViewState)>("update_msg_state", [=](MessageViewState state) {
        msg_view_state = state;
    });
    
    dispatcher->subscribe<void ()>("release_decide", [=]() {
        if (msg_view_state == MessageViewState::WAIT) {
            msg_idx++;
            if (running_story->getMsgData().size() > msg_idx) {
                view->releaseMessages();
                return ;
            }
            
            story_data.erase(0);
            if (story_data.empty()) {
                view->releaseMessages();
                return;
            }
            
            msg_idx = 0;
            running_story = story_data.front();
            view->viewMessages(running_story->getMsgData());
        }
    });
}

void StoryState::update()
{
}

void StoryState::exit()
{
    story_data.clear();
}
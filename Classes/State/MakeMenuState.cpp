//
//  MakeMenuState.cpp
//  solno
//
//  Created by Mitsushige Komiya on 2015/01/29.
//
//

#include "MakeMenuState.h"

#include "UserStorageModule.h"
#include "InputModule.h"
#include "Dispatcher.h"

#include "MakeMenuLayer.h"
#include "Router.h"

MakeMenuState* MakeMenuState::create()
{
    auto ret = new MakeMenuState();
    if (!ret) {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    ret->setCurrentItemIndex(0);
    ret->setMakeItem(nullptr);
    ret->autorelease();
    return ret;
}

void MakeMenuState::enter()
{
    // repositoryからitem list読込
    auto user_item_list = UserStorageModule::getInstance()->getAllUserItem();
    for (auto user_item : user_item_list) {
        auto item = Item::createByMaster(user_item.item_id);
        item_list.pushBack(item);
    }
    
    // ItemMenuLayerへset
    view = MakeMenuLayer::create(item_list);
    auto router = Raciela::Router::getInstance();
    router->addView(view);
}

void MakeMenuState::update()
{
    auto e = InputModule::getInstance()->popEvent();
    auto p = InputModule::getInstance()->popParam();
    
    if (e == InputEvent::PRESS_ITEM_SELECT) {
        if (p < 0 || p >= item_list.size()) {
            return ;
        }
        
        auto item = item_list.at(p);
        if (current_item_idx != p) {
            current_item_idx = p;
            return ;
        }
        
        updatePreparentItem(item);
        return ;
    }
    
    if (e == InputEvent::PRESS_PREPARENT_ITEM_SELECT) {
        if (p < 0 || p > preparent_item_ids.size()) {
            return ;
        }
        
        auto item_id = preparent_item_ids.at(p - 1);
        auto it = std::find(preparent_item_ids.begin(),
                            preparent_item_ids.end(),
                            item_id);
        preparent_item_ids.erase(it);
        view->invisiblePreparentItem(p);
        
        if (preparent_item_ids.empty()) {
            view->setOpacityItemIconAll(255);
            make_item = nullptr;
            return ;
        }
        
        view->setOpacityItemIconAll(64);
        std::vector<int> indices;
        for (auto item : item_list) {
            if ((item->getItemId() == make_item->getPrepareItemId1() ||
                 item->getItemId() == make_item->getPrepareItemId2() ||
                 item->getItemId() == make_item->getPrepareItemId3()) &&
                (std::find(preparent_item_ids.begin(), preparent_item_ids.end(), item->getItemId()) == preparent_item_ids.end()))
            {
                auto idx = item_list.getIndex(item);
                indices.push_back(idx);
            }
        }
        if (!indices.empty()) {
            view->visibleItemIcons(indices);
        }
        
        return ;
    }
}

void MakeMenuState::exit()
{
    preparent_item_ids.clear();
    item_list.clear();
    Raciela::Router::getInstance()->removeView(view);
}

void MakeMenuState::delegate()
{
    dispatcher->subscribe<void (int)>("selected_item", [=](int idx) {
        if (idx < 0 || idx >= item_list.size()) {
            return ;
        }
        
        auto item = item_list.at(idx);
        if (current_item_idx != idx) {
            current_item_idx = idx;
            return ;
        }
        
        updatePreparentItem(item);
    });
    
    dispatcher->subscribe<void (int)>("cancel_preparent_item", [=](int idx) {
        if (idx < 0 || idx > preparent_item_ids.size()) {
            return ;
        }
        
        auto item_id = preparent_item_ids.at(idx - 1);
        auto it = std::find(preparent_item_ids.begin(),
                            preparent_item_ids.end(),
                            item_id);
        preparent_item_ids.erase(it);
        view->invisiblePreparentItem(idx);
        
        if (preparent_item_ids.empty()) {
            view->setOpacityItemIconAll(255);
            make_item = nullptr;
            return ;
        }
        
        view->setOpacityItemIconAll(64);
        std::vector<int> indices;
        for (auto item : item_list) {
            if ((item->getItemId() == make_item->getPrepareItemId1() ||
                 item->getItemId() == make_item->getPrepareItemId2() ||
                 item->getItemId() == make_item->getPrepareItemId3()) &&
                (std::find(preparent_item_ids.begin(), preparent_item_ids.end(), item->getItemId()) == preparent_item_ids.end()))
            {
                auto idx = item_list.getIndex(item);
                indices.push_back(idx);
            }
        }
        if (!indices.empty()) {
            view->visibleItemIcons(indices);
        }
    });
}

void MakeMenuState::updatePreparentItem(Item *item)
{
    view->setOpacityItemIconAll(64);
    
    preparent_item_ids.push_back(item->getItemId());
    view->setPreparentItemTexture(preparent_item_ids.size(), item->getThumbnailTexture());
    
    if (!make_item) {
        make_item = item->getMakeItem();
    }
    
    std::vector<int> indices;
    for (auto item : item_list) {
        if ((item->getItemId() == make_item->getPrepareItemId1() ||
             item->getItemId() == make_item->getPrepareItemId2() ||
             item->getItemId() == make_item->getPrepareItemId3()) &&
            (std::find(preparent_item_ids.begin(), preparent_item_ids.end(), item->getItemId()) == preparent_item_ids.end()))
        {
            auto idx = item_list.getIndex(item);
            indices.push_back(idx);
        }
    }
    
    if (!indices.empty()) {
        view->visibleItemIcons(indices);
    }
}
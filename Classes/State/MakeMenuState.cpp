//
//  MakeMenuState.cpp
//  solno
//
//  Created by Mitsushige Komiya on 2015/01/29.
//
//

#include "MakeMenuState.h"

#include "UserStorageModule.h"
#include "Dispatcher.h"

#include "MakeMenuLayer.h"
#include "MakeMenuControllerLayer.h"
#include "Router.h"

MakeMenuState* MakeMenuState::create()
{
    auto ret = new MakeMenuState();
    if (!ret) {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    ret->init();
    ret->setCurrentItemIndex(0);
    ret->setMakeItem(nullptr);
    ret->autorelease();
    ret->created();
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

    controller = MakeMenuControllerLayer::create();
    router->addView(controller);
    
    controller->setVisible(false);
}

void MakeMenuState::update()
{
}

void MakeMenuState::exit()
{
    dispatcher->removeAllListener();
    
    preparent_item_ids.clear();
    item_list.clear();
    Raciela::Router::getInstance()->removeView(controller);
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

    dispatcher->subscribe<void ()>("release_decide", [=]() {
        CCLOG("%s を調合した！", make_item->getItemName().c_str());
        
        auto us   = UserStorageModule::getInstance();
        auto data = us->getOneUserItem(make_item->getItemId());
        us->updateUserItem(make_item->getItemId(), data.num + 1);
        view->showResult(make_item);
    });

    dispatcher->subscribe<void ()>("touched_result", [=]() {
        auto router = Raciela::Router::getInstance();
        router->popState();
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

    // 条件が揃っていたらOKボタンを表示する
    if (canMakeItem(make_item, indices)) {
        controller->setVisible(true);
    }
}

bool MakeMenuState::canMakeItem(const Item* make_item, const std::vector<int> selected_item_ids)
{
    auto preparent_item_1_id = make_item->getPrepareItemId1();
    auto preparent_item_2_id = make_item->getPrepareItemId2();
    auto preparent_item_3_id = make_item->getPrepareItemId3();

    // @todo: preparent_item_idがnilのときの検証
    if (preparent_item_1_id != 0 &&
        std::find(preparent_item_ids.begin(), preparent_item_ids.end(), preparent_item_1_id) == preparent_item_ids.end()) {
        return false;
    }
    if (preparent_item_2_id != 0 &&
        std::find(preparent_item_ids.begin(), preparent_item_ids.end(), preparent_item_2_id) == preparent_item_ids.end()) {
        return false;
    }
    if (preparent_item_3_id != 0 &&
        std::find(preparent_item_ids.begin(), preparent_item_ids.end(), preparent_item_3_id) == preparent_item_ids.end()) {
        return false;
    }
    return true;
}

//
//  MakeMenuLayer.cpp
//  solno
//
//  Created by Mitsushige Komiya on 2015/01/29.
//
//

#include "MakeMenuLayer.h"
#include "Template.h"
#include "Dispatcher.h"

USING_NS_CC;

MakeMenuLayer* MakeMenuLayer::create(cocos2d::Vector<Item *> &item_list)
{
    auto ret = new MakeMenuLayer();
    if (ret && ret->init()) {
        ret->setItemList(item_list);
        if (ret->init()) {
            ret->autorelease();
            return ret;
        }
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool MakeMenuLayer::init()
{
    if (!Raciela::View::init()) {
        return false;
    }
    
    auto s = Director::getInstance()->getWinSize();
    
    auto frame = Sprite::create("ui/ui_menu_item_frame.png");
    frame->setPosition(Point(s.width / 2.0f, s.height * 2.0f / 3.0f));
    addChild(frame);
    
    // 取り敢えずアタッチされたItemを先頭から順に16個取得して表示する
    auto base_pos = Point(26, frame->getContentSize().height - 80);
    
    item_icon_list = Vector<MenuItem*>();
    for (int idx = 0; idx < VIEW_ITEM_H * VIEW_ITEM_W; ++idx) {
        int x = idx % VIEW_ITEM_W;
        int y = idx / VIEW_ITEM_W;
        
        if (item_list.size() <= idx) {
            break;
        }
        
        auto item = item_list.at(idx);
        auto filepath = Template::create("item/#item_id#.png");
        filepath->assign("#item_id#", 1); // item->getItemId()
        auto image_name = filepath->getString();
        
        auto item_menu_value = MenuItemImage::create(image_name, image_name);
        item_menu_value->setPosition(base_pos.x + x * 41, base_pos.y - 40 * y);
        item_menu_value->setCallback([idx, this](Ref* s) {
            updateViewItem(idx);
            
            auto dispatcher = Raciela::Dispatcher::getInstance();
            dispatcher->dispatch("selected_item", idx);
        });
        item_icon_list.pushBack(item_menu_value);
    }
    
    if (!item_icon_list.empty()) {
        auto menu = Menu::createWithArray(item_icon_list);
        menu->setPosition(Point::ZERO);
        frame->addChild(menu);
    }
    
    // カーソル表示（最初はinvisible）
    current_cursor = Sprite::create("ui/ui_menu_item_cursor.png");
    current_cursor->setPosition(base_pos);
    frame->addChild(current_cursor);
    
    // ラベル表示
    name_label = Label::createWithBMFont("fonts/message_font.fnt", "");
    name_label->getTexture()->setAliasTexParameters();
    name_label->setAnchorPoint(Point(0, 0.5f));
    name_label->setPosition(12, frame->getContentSize().height - 16);
    name_label->setScale(2.0f);
    frame->addChild(name_label);
    
    // 選択されたアイテムの表示
    auto prepare_item_1_sprite = Sprite::create("item/1.png");
    auto prepare_item_2_sprite = Sprite::create("item/1.png");
    auto prepare_item_3_sprite = Sprite::create("item/1.png");
    
    prepare_item_1 = MenuItemSprite::create(prepare_item_1_sprite, prepare_item_1_sprite);
    prepare_item_1->setAnchorPoint(Point(0, 1));
    prepare_item_1->setPosition(190, frame->getContentSize().height - 82);
    prepare_item_1->setVisible(false);
    prepare_item_1->setCallback([this](Ref* s) {
        auto dispacher = Raciela::Dispatcher::getInstance();
        dispacher->dispatch("cancel_preparent_item", 1);
    });
    prepare_item_2 = MenuItemSprite::create(prepare_item_2_sprite, prepare_item_2_sprite);
    prepare_item_2->setAnchorPoint(Point(0, 1));
    prepare_item_2->setPosition(222, frame->getContentSize().height - 82);
    prepare_item_2->setVisible(false);
    prepare_item_2->setCallback([this](Ref* s) {
        auto dispacher = Raciela::Dispatcher::getInstance();
        dispacher->dispatch("cancel_preparent_item", 2);
    });
    prepare_item_3 = MenuItemSprite::create(prepare_item_3_sprite, prepare_item_3_sprite);
    prepare_item_3->setAnchorPoint(Point(0, 1));
    prepare_item_3->setPosition(206, frame->getContentSize().height - 56);
    prepare_item_3->setVisible(false);
    prepare_item_3->setCallback([this](Ref* s) {
        auto dispacher = Raciela::Dispatcher::getInstance();
        dispacher->dispatch("cancel_preparent_item", 3);
    });
    
    auto selected_item_menu = Menu::create(prepare_item_1, prepare_item_2, prepare_item_3, NULL);
    selected_item_menu->setPosition(Point::ZERO);
    frame->addChild(selected_item_menu);
    
    updateViewItem(0);
    
    return true;
}

void MakeMenuLayer::updateViewItem(int index)
{
    if (index < 0 || index >= item_list.size()) {
        return ;
    }
    
    auto item  = item_list.at(index);
    
    // カーソル位置切り替え
    auto frame = current_cursor->getParent();
    auto base_pos = Point(26, frame->getContentSize().height - 80);
    
    int idx_x = index % 4;
    int idx_y = index / 4;
    current_cursor->setPosition(base_pos.x + idx_x * 41, base_pos.y - 40 * idx_y);
    
    // 名前表示切り替え
    name_label->setString(item->getItemName());
}

void MakeMenuLayer::invisibleItemIcon(int index)
{
    if (index < 0 || index >= item_list.size()) {
        return ;
    }
    
    auto icon = item_icon_list.at(index);
    icon->setOpacity(64);
}

void MakeMenuLayer::setOpacityItemIconAll(int value)
{
    for (auto item_icon : item_icon_list) {
        item_icon->setOpacity(value);
    }
}

void MakeMenuLayer::visibleItemIcons(std::vector<int> indices)
{
    for (int index : indices) {
        if (index < 0 || index >= item_list.size()) {
            return ;
        }
        
        auto icon = item_icon_list.at(index);
        icon->setOpacity(255);
    }
}

void MakeMenuLayer::setPreparentItemTexture(int preparent_index, cocos2d::Texture2D *texture)
{
    CCASSERT(preparent_index == 1 ||
             preparent_index == 2 ||
             preparent_index == 3, "Invalid preparent item index");
    
    if (preparent_index == 1) {
        auto sprite = (Sprite*)prepare_item_1->getNormalImage();
        sprite->setTexture(texture);
        prepare_item_1->setVisible(true);
    } else if (preparent_index == 2) {
        auto sprite = (Sprite*)prepare_item_2->getNormalImage();
        sprite->setTexture(texture);
        prepare_item_2->setVisible(true);
    } else if (preparent_index == 3) {
        auto sprite = (Sprite*)prepare_item_3->getNormalImage();
        sprite->setTexture(texture);
        prepare_item_3->setVisible(true);
    }
}

void MakeMenuLayer::invisiblePreparentItem(int preparent_index)
{
    CCASSERT(preparent_index == 1 ||
             preparent_index == 2 ||
             preparent_index == 3, "Invalid preparent item index");
    
    if (preparent_index == 1) {
        prepare_item_1->setVisible(false);
    } else if (preparent_index == 2) {
        prepare_item_2->setVisible(false);
    } else if (preparent_index == 3) {
        prepare_item_3->setVisible(false);
    }
}

void MakeMenuLayer::showResult(const Item *maked_item)
{
    std::string str = maked_item->getItemName() + "を調合した！";
    name_label->setString(str);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch* touch, Event* event) -> bool {
        return true;
    };
    listener->onTouchMoved = [=](Touch* touch, Event* event) {
    };
    listener->onTouchEnded = [=](Touch* touch, Event* event) {
        dispatcher->dispatch("touched_result");
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
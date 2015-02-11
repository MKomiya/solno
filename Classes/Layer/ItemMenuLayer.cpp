//
//  ItemMenuLayer.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/28.
//
//

#include "ItemMenuLayer.h"

#include "Template.h"

#include "InputModule.h"

USING_NS_CC;

ItemMenuLayer* ItemMenuLayer::create(cocos2d::Vector<Item *> &item_list)
{
    auto ret = new ItemMenuLayer();
    if (ret && ret->init()) {
        ret->setItemList(item_list);
        if (ret->init()) {
            ret->autorelease();
            ret->setCurrentItemIdx(0);
            return ret;
        }
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool ItemMenuLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto s = Director::getInstance()->getWinSize();
    
    auto frame = Sprite::create("ui/ui_menu_item_frame.png");
    frame->setPosition(Point(s.width / 2.0f, s.height * 2.0f / 3.0f));
    addChild(frame);
    
    // 取り敢えずアタッチされたItemを先頭から順に16個取得して表示する
    auto base_pos = Point(26, frame->getContentSize().height - 80);
    
    auto vec = Vector<MenuItem*>();
    for (int y = 0; y < VIEW_ITEM_H; ++y) {
        for (int x = 0; x < VIEW_ITEM_W; ++x) {
            int idx = x + y * VIEW_ITEM_W;
            
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
                InputModule::getInstance()->pushEvent(InputEvent::PRESS_ITEM_SELECT);
                InputModule::getInstance()->pushParam(idx);
            });
            vec.pushBack(item_menu_value);
        }
    }
    
    if (!vec.empty()) {
        auto menu = Menu::createWithArray(vec);
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
    
    // 調合ツリー表示
    prepare_item_1 = Sprite::create("item/1.png");
    prepare_item_1->setAnchorPoint(Point(0, 1));
    prepare_item_1->setPosition(190, frame->getContentSize().height - 82);
    prepare_item_1->setVisible(false);
    frame->addChild(prepare_item_1);
    prepare_item_2 = Sprite::create("item/1.png");
    prepare_item_2->setAnchorPoint(Point(0, 1));
    prepare_item_2->setPosition(222, frame->getContentSize().height - 82);
    prepare_item_2->setVisible(false);
    frame->addChild(prepare_item_2);
    prepare_item_3 = Sprite::create("item/1.png");
    prepare_item_3->setAnchorPoint(Point(0, 1));
    prepare_item_3->setPosition(206, frame->getContentSize().height - 56);
    prepare_item_3->setVisible(false);
    frame->addChild(prepare_item_3);
    
    updateViewItem(current_item_idx);
    
    return true;
}

void ItemMenuLayer::updateViewItem(int index)
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
    
    // 調合ツリーの表示更新
    auto make_item = item->getMakeItem();
    if (make_item == nullptr) {
        return ;
    }
    
    auto thumb1    = make_item->getPrepareItemTexture(1);
    auto thumb2    = make_item->getPrepareItemTexture(2);
    auto thumb3    = make_item->getPrepareItemTexture(3);

    if (thumb1) {
        prepare_item_1->setTexture(thumb1);
        prepare_item_1->setVisible(true);
    }
    
    if (thumb2) {
        prepare_item_2->setTexture(thumb2);
        prepare_item_2->setVisible(true);
    }
    
    if (thumb3) {
        prepare_item_3->setTexture(thumb3);
        prepare_item_3->setVisible(true);
    }
}
//
//  MakeMenuLayer.cpp
//  solno
//
//  Created by Mitsushige Komiya on 2015/01/29.
//
//

#include "MakeMenuLayer.h"

#include "Template.h"
#include "InputModule.h"

USING_NS_CC;

MakeMenuLayer* MakeMenuLayer::create(cocos2d::Vector<Item *> &item_list)
{
    auto ret = new MakeMenuLayer();
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

bool MakeMenuLayer::init()
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
            
            auto im = InputModule::getInstance();
            im->pushEvent(InputEvent::PRESS_ITEM_SELECT);
            im->pushParam(idx);
        });
        vec.pushBack(item_menu_value);
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
    
    updateViewItem(current_item_idx);
    
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

/*
bool MakeMenuLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto s = Director::getInstance()->getWinSize();
    
    auto frame = Sprite::create("ui/ui_menu_make_frame.png");
    frame->setPosition(s.width / 2.0f, s.height * 2.0f / 3.0f);
    addChild(frame);
    
    // カーソル表示
    current_cursor = Sprite::create("ui/ui_menu_item_cursor.png");
    current_cursor->setAnchorPoint(Point(0, 1));
    current_cursor->setPosition(67, s.height - 105);
    addChild(current_cursor);
    
    return true;
}
*/
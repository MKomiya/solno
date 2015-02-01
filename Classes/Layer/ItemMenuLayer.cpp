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

bool ItemMenuLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto s = Director::getInstance()->getWinSize();
    
    auto frame = Sprite::create("ui/ui_menu_item_frame.png");
    frame->setPosition(Point(s.width / 2.0f, s.height * 2.0f / 3.0f));
    addChild(frame);
    
    // add test data
    for (int i=0; i < 10; ++i) {
        item_list.pushBack(Item::create());
    }
    
    // 取り敢えずアタッチされたItemを先頭から順に16個取得して表示する
    auto base_pos = Point(27, frame->getContentSize().height - 80);
    
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
                InputModule::getInstance()->pushEvent(InputEvent::PRESS_ITEM_SELECT);
                InputModule::getInstance()->pushParam(idx + 1);
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
    
    return true;
}

void ItemMenuLayer::updateViewItem(int index)
{
    if (index < 0 || index >= item_list.size()) {
        return ;
    }
    
    auto item  = item_list.at(index);
    
    // カーソル位置切り替え
    int idx_x = index % 4;
    int idx_y = index / 4;
    //current_cursor->setPosition(base_pos.x + x * 41, base_pos.y - 40 * y);
    
    /*
    // 名前表示切り替え
    name_label->setString(item->getName());
    */
}
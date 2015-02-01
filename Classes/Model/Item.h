//
//  Item.h
//  solno
//
//  Created by S_Wyvern on 2015/01/28.
//
//

#ifndef __solno__Item__
#define __solno__Item__

#include <stdio.h>
#include <cocos2d.h>

class Item : public cocos2d::Ref
{
public:
    enum EventType {
        BREAK_TREE = 1,
        BREAK_SCRAP,
    };
    
    static Item* create();
    
    CC_SYNTHESIZE(int, id, Id);
    CC_SYNTHESIZE(int, item_id, ItemId);
    CC_SYNTHESIZE(int, num, Num);
    CC_SYNTHESIZE(std::string, item_name, ItemName);
    CC_SYNTHESIZE(int, event_id, EventId);
    CC_SYNTHESIZE(cocos2d::Texture2D*, thumb_texture, ThumbnailTexture);
};

#endif /* defined(__solno__Item__) */

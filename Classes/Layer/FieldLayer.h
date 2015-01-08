//
//  FieldLayer.h
//  solno
//
//  Created by S_Wyvern on 2014/12/26.
//
//

#ifndef __solno__FieldLayer__
#define __solno__FieldLayer__

#include <stdio.h>
#include <cocos2d.h>

enum PlayerActionTags {
    MOVE_SEQUENCE = 11,
};

class PlayerView;
class FieldLayer : public cocos2d::Layer
{
public:
    enum FieldActionTag {
        SCROLL_ACTION
    };

    virtual bool init();
    CREATE_FUNC(FieldLayer);
    void changePlayerAnimation(std::string direction);
    void runMoveAction(cocos2d::Point move_vec);
    cocos2d::TMXLayer* getMapCollider();
    void scrollField(cocos2d::Point move_vec, cocos2d::Point scroll_vec);
    bool isRunningPlayerView();
    bool isRunningMapScroll();
    
private:
    cocos2d::TMXTiledMap* map;
    PlayerView* player_sprite;
};

#endif /* defined(__solno__FieldLayer__) */

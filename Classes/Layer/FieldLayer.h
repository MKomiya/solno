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
struct FieldObject;
class FieldLayer : public cocos2d::Layer
{
public:
    enum FieldActionTag {
        SCROLL_ACTION = 1,
    };
    
    virtual bool init();
    CREATE_FUNC(FieldLayer);
    void initFieldObject(std::vector<FieldObject*> objects);
    
    void changePlayerAnimation(std::string direction);
    void runMoveAction(cocos2d::Point move_vec);
    
    void runObjectMoveAction(int object_id, cocos2d::Point move_vec);
    
    cocos2d::TMXLayer* getMapCollider();
    cocos2d::TMXLayer* getObjectsLayer();
    void scrollField(cocos2d::Point move_vec, cocos2d::Point scroll_vec);
    bool isRunningPlayerView();
    bool isRunningMapScroll();
    
    void addRunActionAfterMove(cocos2d::FiniteTimeAction* action);
    
private:
    cocos2d::TMXTiledMap* map;
    PlayerView* player_sprite;
    cocos2d::Node* objects_root;
};

#endif /* defined(__solno__FieldLayer__) */

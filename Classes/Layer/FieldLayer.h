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

#include "View.h"
#include "MessageView.h"

enum PlayerActionTags {
    MOVE_SEQUENCE = 11,
};

enum class FieldViewState {
    NOTHING,
    SCROLL,
};

struct FieldObject;
class PlayerView;
class FieldLayer : public Raciela::View
{
public:
    enum FieldActionTag {
        SCROLL_ACTION = 1,
    };
    
    virtual bool init();
    CREATE_FUNC(FieldLayer);
    void initMapData(cocos2d::TMXTiledMap* value);
    void initFieldObject(std::vector<FieldObject*> objects);
    
    void changePlayerAnimation(std::string direction);
    void stopPlayerAnimation();
    
    void runMoveAction(cocos2d::Point move_vec);
    void runObjectMoveAction(int object_id, cocos2d::Point move_vec);
    
    void scrollField(cocos2d::Point move_vec, cocos2d::Point scroll_vec);
    
    void addRunActionAfterMove(cocos2d::FiniteTimeAction* action);
    void viewMessages(std::vector<std::string> msg_data);
    void releaseMessages();
    
    void destroyObject(int id);
    
    CC_SYNTHESIZE(cocos2d::TMXTiledMap*, map, Map);
    
private:
    PlayerView* player_sprite;
    MessageView* msg_view;
    cocos2d::Node* objects_root;
};

#endif /* defined(__solno__FieldLayer__) */

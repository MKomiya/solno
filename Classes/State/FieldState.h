//
//  FieldState.h
//  solno
//
//  Created by S_Wyvern on 2014/12/30.
//
//

#ifndef __solno__FieldState__
#define __solno__FieldState__

#include <stdio.h>
#include <cocos2d.h>

#include "State.h"

enum MapColliderType {
    NO_COLLISION = 0,
    COLLIDABLE   = 17, // タイルが増えるとGIDが変わるので別途検討
};

enum class ArrowInputEvent;
enum class MessageViewState;
enum class PlayerViewState;
enum class FieldViewState;

class FieldLayer;
class ControllerLayer;
class FieldObject;
class Item;
class FieldState : public Raciela::State {
public:
    static FieldState* create();
    
    virtual void created() override;
    virtual void enter() override;
    virtual void update() override;
    virtual void exit() override;
    virtual void delegate() override;
    
    void addExecuteItem(Item* item);
    FieldObject* findPlayerDirectionAbutObject();
    void deleteObject(FieldObject* target);
    bool isCollidable(int map_x, int map_y);
    
    CC_SYNTHESIZE(cocos2d::TMXTiledMap*, map, Map);
    CC_SYNTHESIZE(cocos2d::Point, player_map_pos, PlayerMapPosition);
    CC_SYNTHESIZE(std::string, player_direction, PlayerDirection);
    CC_SYNTHESIZE(FieldLayer*, view, FieldView);
    CC_SYNTHESIZE(ControllerLayer*, controller, ControllerView);
    CC_SYNTHESIZE(std::vector<FieldObject*>, objects, MapObjects);
    CC_SYNTHESIZE(Item*, execute_item, ExecuteItem);
    CC_SYNTHESIZE(MessageViewState, msg_view_state, MsgViewState);
    CC_SYNTHESIZE(PlayerViewState, player_view_state, PlayerViewState);
    CC_SYNTHESIZE(FieldViewState, field_view_state, FieldViewState);
    
private:
    void decideAction();
    void movePlayerCharacter(ArrowInputEvent event);
};

#endif /* defined(__solno__FieldState__) */

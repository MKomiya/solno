#include "HelloWorldScene.h"
#include "FieldState.h"
#include "StateMachineModule.h"

#include "LayerManager.h"
#include "FieldLayer.h"
#include "ControllerLayer.h"

#include "StoryState.h"
#include "StoryLayer.h"

#include "ModeSelectMenuState.h"
#include "ItemMenuState.h"
#include "MakeMenuState.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    LayerManager::getInstance()->init(scene);
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    // publish state
    StateMachineModule::getInstance()->registerState("field", FieldState::create());
    StateMachineModule::getInstance()->registerState("mode_select_menu", ModeSelectMenuState::create());
    StateMachineModule::getInstance()->registerState("item_menu", ItemMenuState::create());
    StateMachineModule::getInstance()->registerState("make_menu", MakeMenuState::create());
    
    StateMachineModule::getInstance()->changeState("field");
    scheduleUpdate();
    
    /*
    auto story      = StoryLayer::create();
    auto controller = ControllerLayer::create();
    LayerManager::getInstance()->push(story);
    LayerManager::getInstance()->push(controller);
    
    StateMachineModule::getInstance()->registerState("story", StoryState::create(story));
    StateMachineModule::getInstance()->changeState("story");
    scheduleUpdate();
    */
     
    return true;
}

void HelloWorld::update(float dt)
{
    StateMachineModule::getInstance()->update();
}
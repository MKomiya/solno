#include "HelloWorldScene.h"
#include "FieldState.h"
#include "StateMachineModule.h"

#include "LayerManager.h"
#include "FieldLayer.h"
#include "ControllerLayer.h"

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
    
    // initialize view
    auto field      = FieldLayer::create();
    auto controller = ControllerLayer::create();
    LayerManager::getInstance()->push(field);
    LayerManager::getInstance()->push(controller);
    
    // publish state
    auto state = new FieldState(field);
    StateMachineModule::getInstance()->registerState("field", state);
    StateMachineModule::getInstance()->setNowState("field");
    scheduleUpdate();
    
    return true;
}

void HelloWorld::update(float dt)
{
    StateMachineModule::getInstance()->update();
}
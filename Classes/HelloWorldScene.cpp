#include "HelloWorldScene.h"
#include "FieldLayer.h"
#include "ControllerLayer.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    auto map = FieldLayer::create();
    
    auto frame = ControllerLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    scene->addChild(map);
    scene->addChild(frame);

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
    
    return true;
}

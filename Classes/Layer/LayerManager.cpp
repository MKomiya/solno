//
//  LayerManager.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/05.
//
//

#include "LayerManager.h"

LayerManager* LayerManager::instance;

void LayerManager::init(cocos2d::Scene *root)
{
    root_scene = root;
}

void LayerManager::push(cocos2d::Layer *layer)
{
    root_scene->addChild(layer);
    layer_list.push_back(layer);
}

cocos2d::Layer* LayerManager::pop()
{
    if (layer_list.empty()) {
        return nullptr;
    }
    
    auto ret = layer_list.front();
    
    root_scene->removeChild(ret);
    layer_list.pop_front();
    
    return ret;
}

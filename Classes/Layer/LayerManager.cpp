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

void LayerManager::release()
{
    root_scene = nullptr;
}

void LayerManager::push(std::string key, cocos2d::Layer *layer)
{
    root_scene->addChild(layer);
    layer_map.insert(std::make_pair(key, layer));
}

cocos2d::Layer* LayerManager::pop()
{
    if (layer_map.empty()) {
        return nullptr;
    }
    
    auto ret = layer_map.begin();
    
    root_scene->removeChild(ret->second);
    layer_map.erase(ret);
    
    return ret->second;
}

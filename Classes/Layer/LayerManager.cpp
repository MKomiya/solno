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
    layer_list.push_back(layer);
}

cocos2d::Layer* LayerManager::pop()
{
    if (layer_map.empty()) {
        return nullptr;
    }
    
    auto ret = layer_list.back();
    
    for (auto value : layer_map) {
        if (value.second == ret) {
            layer_map.erase(value.first);
            break;
        }
    }
    
    root_scene->removeChild(ret);
    layer_list.pop_back();
    
    return ret;
}

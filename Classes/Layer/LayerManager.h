//
//  LayerManager.h
//  solno
//
//  Created by S_Wyvern on 2015/01/05.
//
//

#ifndef __solno__LayerManager__
#define __solno__LayerManager__

#include <stdio.h>
#include <cocos2d.h>
#include <unordered_map>

class LayerManager
{
public:
    static LayerManager* getInstance() {
        if (!instance) {
            instance = new LayerManager();
        }
        return instance;
    }
    
    void init(cocos2d::Scene* root);
    void release();
    
    void push(std::string key, cocos2d::Layer* layer);
    cocos2d::Layer* pop();

private:
    static LayerManager* instance;
    
    std::unordered_map<std::string, cocos2d::Layer*> layer_map;
    std::list<cocos2d::Layer*> layer_list;
    
    cocos2d::Scene* root_scene;
};

#endif /* defined(__solno__LayerManager__) */

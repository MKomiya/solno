//
//  Template.h
//  solno
//
//  Created by S_Wyvern on 2015/01/20.
//
//

#ifndef __solno__Template__
#define __solno__Template__

#include <stdio.h>
#include <unordered_map>
#include <cocos2d.h>

class Template : public cocos2d::Ref
{
public:
    static Template* create(std::string str);
    
    void assign(std::string key, std::string value);
    void assign(std::string key, int value);
    void assigns(std::unordered_map<std::string, std::string> datalist);
    
    CC_SYNTHESIZE(std::string, str, String);
};

#endif /* defined(__solno__Template__) */

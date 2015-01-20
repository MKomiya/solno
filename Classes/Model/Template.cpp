//
//  Template.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/20.
//
//

#include <algorithm>
#include "Template.h"

Template* Template::create(std::string str)
{
    auto ret = new Template();
    if (!ret) {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    ret->setString(str);
    return ret;
}

void Template::assign(std::string key, std::string value)
{
    auto position = str.find(key);
    while (position != std::string::npos) {
        str.replace(position, key.length(), value);
        position = str.find(key);
    }
}

void Template::assign(std::string key, int value)
{
    assign(key, std::to_string(value));
}

void Template::assigns(std::unordered_map<std::string, std::string> datalist)
{
    std::for_each(datalist.begin(), datalist.end(), [=](std::pair<std::string, std::string> elm) {
        this->assign(elm.first, elm.second);
    });
}
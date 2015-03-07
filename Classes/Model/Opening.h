//
//  Opening.h
//  solno
//
//  Created by S_Wyvern on 2015/03/07.
//
//

#ifndef __solno__Opening__
#define __solno__Opening__

#include <stdio.h>
#include "json11.hpp"

enum class MasterOpeningType {
    NORMAL   = 1, // 通常画面に表示するメッセージ
    TERMINAL = 2, // ターミナル画面に表示するメッセージ
};

class MasterOpening
{
public:
    int id;
    MasterOpeningType type;
    std::string msg;
    
    MasterOpening() : id(0) {}
    MasterOpening(json11::Json::object data) :
    id(data["id"].int_value()),
    type((MasterOpeningType)data["type"].int_value()),
    msg(data["msg"].string_value())
    {}
};
const MasterOpening MasterOpeningNull;

#endif /* defined(__solno__Opening__) */

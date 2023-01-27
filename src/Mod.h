#pragma once
#include <llapi/LoggerAPI.h>
#include <llapi/I18nAPI.h>
#include "Data.h"
#include "pch.h"

class Permission;

class Mod {
    
public:

    Logger logger;
    Permission perm;

    Mod();
    void entry();

};
extern Mod mod;

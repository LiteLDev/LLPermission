#pragma once

#include <llapi/LoggerAPI.h>
#include <llapi/I18nAPI.h>
#include "Data.h"
#include "pch.h"

class Permission;

class LLPermission {

public:

    Logger logger;
    Permission perm;

    LLPermission();

    void entry();

};

extern LLPermission mod;

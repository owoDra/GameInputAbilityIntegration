// Copyright (C) 2023 owoDra

#pragma once

#include "Modules/ModuleManager.h"

/**
 *  Modules for the main features of the Game Input: Ability Integration plugin
 */
class FGIAIntgModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

};

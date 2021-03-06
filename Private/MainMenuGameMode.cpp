// © 2015 Mark Vatsel.

#include "Manipulators_01.h"
#include "Public/MainMenuGameMode.h"
#include "Public/UI/MainMenuHUD.h"
#include "Public/MainMenuPlayerController.h"

AMainMenuGameMode::AMainMenuGameMode(const FObjectInitializer & objectInitializer): Super(objectInitializer)
{
	HUDClass = AMainMenuHUD::StaticClass();
	PlayerControllerClass = AMainMenuPlayerController::StaticClass();
}
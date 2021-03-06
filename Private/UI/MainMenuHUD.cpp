// © 2015 Mark Vatsel.

#include "Manipulators_01.h"
#include "Public/UI/MainMenu/MainMenuHUD.h"

AMainMenuHUD::AMainMenuHUD(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
/* Depending on the widget creation function, the widget's Construct() may be called before the primary game module initialises.
 * Style set pointers in Construct() are at that point set to null (as per hot reload hack).
 */
{
	AddMenuItem(menu, MainMenuItem::Title, FText::FromString("START"))->onButtonClicked.BindUObject(this,&AMainMenuHUD::LoadMainLevel);
	AddMenuItem(menu, MainMenuItem::Option, FText::FromString("NEW"))->onButtonClicked.BindUObject(this, &AMainMenuHUD::LoadMainLevel);
	AddMenuItem(menu, MainMenuItem::Option, FText::FromString("LOAD"),true);
	AddMenuItem(menu, MainMenuItem::Option, FText::FromString("SETTINGS"), true);
	AddMenuItem(menu, MainMenuItem::End, FText::FromString("EXIT"))->onButtonClicked.BindUObject(this, &AMainMenuHUD::ExecuteQuit);
}

void AMainMenuHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();	
	RebuildWidgets();
}

FMainMenuItem* AMainMenuHUD::AddMenuItem(TSharedPtr<TArray<FMainMenuItem>> &appendToMenu, MainMenuItem type, FText buttonText, bool inactive)
{
	if (!appendToMenu.IsValid()) appendToMenu = MakeShareable(new TArray<FMainMenuItem>());
	FMainMenuItem menuItem(buttonText, type, inactive);
	appendToMenu->Add(menuItem);
	return &appendToMenu->Last();
}

void AMainMenuHUD::RebuildWidgets(bool bHotReolad)
{
	mainMenuWidget.Reset();
	
	if (GEngine && GEngine->GameViewport)
	{		
		SAssignNew(mainMenuWidget, SMainMenuWidget)
			.Cursor(EMouseCursor::Default)
			.ownerHUD(TWeakObjectPtr<AMainMenuHUD>(this));

		UGameViewportClient * gvc = GEngine->GameViewport;
		gvc->AddViewportWidgetContent(
			SNew(SWeakWidget)
			.PossiblyNullContent(mainMenuWidget.ToSharedRef()));
	}
}

void AMainMenuHUD::LoadMainLevel()
{
	GetWorld()->ServerTravel(FString("/Game/Maps/main"));
}

void AMainMenuHUD::ExecuteQuit()
{
	GetOwningPlayerController()->ConsoleCommand("quit");
}
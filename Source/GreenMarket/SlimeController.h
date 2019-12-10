// We got no rights, just please don't steal

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SlimeController.generated.h"

/**
 * 
 */
UCLASS()
class GREENMARKET_API ASlimeController : public APlayerController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

public:
	/*
	 * UMG widget for the HUD
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Heads Up Display")
	TSubclassOf<UUserWidget> WidgetHUD;

	/*
	 * Reference for the HUD widget
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Heads Up Display")
	UUserWidget* HUD;

	/*
	 * UMG widget for the Letters
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Subtitles")
	TSubclassOf<UUserWidget> WidgetLetter;

	/*
	 * UMG widget for the HUD
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Subtitles")
	FString MessageText = "Hello";

	/*
	 * Adds a message to the on screen text box
	 *
	 *  @param Message The message to display
	 */
	UFUNCTION(BlueprintCallable, Category="Subtitles")
	void AddMessage(FString Message);

private:
	/*
	 * Creates the HUD widget
	 *
	 * Returns true if HUD is successfully created
	 */
	UFUNCTION(BlueprintCallable, Category="Heads Up Display")
	bool CreateHUD();

	/*
	 * Adds a letter to the text box on HUD
	 *
	 *  @param Letter Letter to add
	 */
	void AddLetter(char Char);
	
};

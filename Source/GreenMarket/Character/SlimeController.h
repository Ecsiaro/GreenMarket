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
	 * Delay between letters appearing
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Subtitles")
	float LetterDelayInSeconds = 1.0f;

	/*
	 * FOR DEBUG ONLY
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subtitles")
	FString MessageDebug = "";

	/*
	 * Adds a message to the on screen text box
	 *
	 *  @param Message The message to display
	 *  @param Time The time before the next letter starts to appear
	 */
	UFUNCTION(BlueprintCallable, Category = "Heads Up Display")
	void SetMessage(FString Message, float Time);

private:
	/*
	 * Creates the HUD widget
	 *
	 * Returns true if HUD is successfully created
	 */
	UFUNCTION(BlueprintCallable, Category="Heads Up Display")
	bool CreateHUD();

	/*
	 * Adds a message to the on screen text box
	 *
	 *  @param Message The message to display
	 */
	void MakeMessage();

	/*
	 * Holds the current message
	 */
	FString MessageText = "";

	/*
	 * Variables for message loop
	 */
	int CurrentIndex = 0;
	FTimerHandle LetterTimer;
	
};

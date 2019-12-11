// We got no rights, just please don't steal

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueComponent.generated.h"


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GREENMARKET_API UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogueComponent();


	/*
	 * UMG widget for the HUD
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heads Up Display")
	TSubclassOf<class UUserWidget> WidgetHUD;

	/*
	 * UMG widget for the Letters
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subtitles")
	TSubclassOf<UUserWidget> WidgetLetter;

	/*
	 * UMG widget for the Words
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subtitles")
	TSubclassOf<UUserWidget> WidgetWord;

	/*
	 * Reference for the HUD widget
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Heads Up Display")
	UUserWidget* HUD;

	/*
	 * Delay between letters appearing
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subtitles")
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
	UFUNCTION(BlueprintCallable, Category = "Heads Up Display")
	bool CreateHUD();

	/*
	 * Adds a message to the on screen text box
	 *
	 *  @param Message The message to display
	 */
	void MakeMessage();

	/*
	 * Groups letter into a word
	 *
	 *  @param Char The letter for the widget text to be set to
	 */
	UUserWidget* MakeLetter(char Char);

	/*
	 * Holds the current message
	 */
	FString MessageText = "";

	/*
	 * Holds the current word widget
	 */
	UUserWidget* WWord;

	/*
	 * Variables for message loop
	 */
	int LetterIndex = 0;
	int WordIndex = 0;
	FTimerHandle LetterTimer;

		
};

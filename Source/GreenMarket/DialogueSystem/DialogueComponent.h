// We got no rights, just please don't steal

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueComponent.generated.h"


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GREENMARKET_API UDialogueComponent : public UActorComponent {
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
	 * Reference for the HUD widget
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Heads Up Display")
	UUserWidget* DialogueHUD;

	/*
	 * UMG widget for the Letters
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue|Subtitles")
	TSubclassOf<UUserWidget> WidgetLetter;

	/*
	 * UMG widget for the Words
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue|Subtitles")
	TSubclassOf<UUserWidget> WidgetWord;

	/*
	 * Delay between letters appearing
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue|Subtitles")
	float LetterDelayInSeconds = 1.0f;
	
	/*
	 * Data table containing dialogue data
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	class UDataTable* DialogueTable;

	/*
	 * Adds a message to the on screen text box
	 *
	 *  @param DialogueEntry The entry of the dialogue table that stores the message details
	 *  @param Time The time before the next letter starts to appear
	 */
	UFUNCTION(BlueprintCallable, Category = "Dialogue|Subtitles")
	void SetMessage(FName DialogueEntry, float Time);

private:
	/*
	 * Creates the dialogue HUD widget
	 *
	 * Returns true if HUD is successfully created
	 */
	UFUNCTION(BlueprintCallable, Category = "Heads Up Display")
	bool CreateHUD();
	
	/*
	 * Destroys the dialogue HUD widget
	 */
	UFUNCTION(BlueprintCallable, Category = "Heads Up Display")
	void DestroyHUD() const;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void ClearMessage();

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
	UUserWidget* MakeLetter();

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

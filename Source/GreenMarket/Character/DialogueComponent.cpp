// We got no rights, just please don't steal


#include "DialogueComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Components/HorizontalBox.h"
#include "TimerManager.h"
#include "WidgetBlueprintLibrary.h"

// Sets default values for this component's properties
UDialogueComponent::UDialogueComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

/*
 * Creates the HUD widget
 *
 * Returns true if HUD is successfully created
 */
bool UDialogueComponent::CreateHUD() {
	if (WidgetHUD) {
		HUD = CreateWidget(GetWorld()->GetFirstPlayerController(), WidgetHUD);
		// If HUD is created correctly
		if (HUD) {
			HUD->AddToViewport();
			// Only return true if the HUD is created AND added to viewport correctly
			return true;
		}
	}
	// Returns false if not created AND added correctly
	return false;
}

/*
 * Adds a message to the on screen text box
 *
 *  @param Message The message to display
 *  @param Time The time before the next letter starts to appear
 */
void UDialogueComponent::SetMessage(FString Message, float Time) {
	MessageText = Message;
	LetterDelayInSeconds = Time;
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetWorld()->GetFirstPlayerController(), HUD, EMouseLockMode::DoNotLock);
	MakeMessage();

}

/*
 * Adds the message to the on screen text box
 *
 */
void UDialogueComponent::MakeMessage() {
	// Checking if we should exit
	if (LetterIndex >= MessageText.Len()) {
		LetterIndex = 0;
		return;
	}

	// Get the text box from the HUd
	UWrapBox* TextBox = Cast<UWrapBox>(HUD->GetWidgetFromName(TEXT("TextBox")));
	//If there isn't a text box on the HUD, return
	if (!TextBox) return;

	//If no current word, create one and add it to the text box
	if (!WWord) {
		WWord = CreateWidget(GetWorld()->GetFirstPlayerController(), WidgetWord);
		TextBox->AddChildToWrapBox(WWord);
	}

	// Get the box for the letters to go in to form a word
	UHorizontalBox* WordBox = Cast<UHorizontalBox>(WWord->GetWidgetFromName(TEXT("WordBox")));
	WordBox->AddChildToHorizontalBox(MakeLetter(MessageText[LetterIndex]));

	// If at a space, or the end of the string, end the current word
	if (MessageText[LetterIndex] == ' ' || LetterIndex + 1 == MessageText.Len()) {
		WWord = nullptr;
		WordIndex++;
	}

	// Incrementing index
	LetterIndex++;

	// Looping after a delay
	GetWorld()->GetTimerManager().SetTimer(LetterTimer, this, &UDialogueComponent::MakeMessage, LetterDelayInSeconds);
}

/*
 * Groups letter into a word
 *
 *  @param Char The letter for the widget text to be set to
 */
UUserWidget* UDialogueComponent::MakeLetter(char Char) {
	FString CurrentLetter = "";

	// Setting string to desired character because FTexts don't convert any char types directly :(
	CurrentLetter.AppendChar(MessageText[LetterIndex]);

	//Creating the letter widget and setting the text to the desired char
	UUserWidget* WLetter = CreateWidget(GetWorld()->GetFirstPlayerController(), WidgetLetter);
	UTextBlock* Text = Cast<UTextBlock>(WLetter->GetWidgetFromName(TEXT("Letter")));
	Text->SetText(FText::FromString(CurrentLetter));

	return WLetter;
}



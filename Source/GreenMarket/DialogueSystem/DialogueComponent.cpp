// We got no rights, just please don't steal


#include "DialogueComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Components/HorizontalBox.h"
#include "TimerManager.h"
#include "WidgetBlueprintLibrary.h"
#include "Engine/DataTable.h"
#include "DialogueSystem/DialogueTable.h"
#include "Components/Spacer.h"

// Sets default values for this component's properties
UDialogueComponent::UDialogueComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}

/*
 * Creates the HUD widget
 *
 * Returns true if HUD is successfully created
 */
bool UDialogueComponent::CreateHUD() {
	if (WidgetHUD) {
		DialogueHUD = CreateWidget(GetWorld()->GetFirstPlayerController(), WidgetHUD);
		// If HUD is created correctly
		if (DialogueHUD) {
			DialogueHUD->AddToViewport();
			UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetWorld()->GetFirstPlayerController(), DialogueHUD, EMouseLockMode::DoNotLock);
			// Only return true if the HUD is created AND added to viewport correctly
			return true;
		}
	}
	// Returns false if not created AND added correctly
	return false;
}

/*
 * Destroys the dialogue HUD widget
 */
void UDialogueComponent::DestroyHUD() const {
	if (DialogueHUD) {
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController());
		DialogueHUD->RemoveFromParent();
		CollectGarbage(EObjectFlags::RF_NoFlags);
	}
}

/*
 * Adds a message to the on screen text box
 *
 *  @param DialogueEntry The entry of the dialogue table that stores the message details
 *  @param Time The time before the next letter starts to appear
 */
void UDialogueComponent::SetMessage(const FName DialogueEntry, const float Time) {
	FString ContextString = "";
	FDialogueTable* DialogueRow = DialogueTable->FindRow<FDialogueTable>(DialogueEntry, ContextString);
	MessageText = DialogueRow->DialogueText;
	LetterDelayInSeconds = Time;
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

	// Get the text box from the HUD
	UWrapBox* TextBox = Cast<UWrapBox>(DialogueHUD->GetWidgetFromName(TEXT("TextBox")));
	//If there isn't a text box on the HUD, return
	if (!TextBox) return;

	//If no current word, create one and add it to the text box
	if (!WWord) {
		WWord = CreateWidget(GetWorld()->GetFirstPlayerController(), WidgetWord);
		TextBox->AddChildToWrapBox(WWord);
	}

	// Get the box for the letters to go in to form a word
	UHorizontalBox* WordBox = Cast<UHorizontalBox>(WWord->GetWidgetFromName(TEXT("WordBox")));
	WordBox->AddChildToHorizontalBox(MakeLetter());

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
 */
UUserWidget* UDialogueComponent::MakeLetter() {
	FString CurrentLetter = "";

	// Setting string to desired character because FTexts don't convert any char types directly :(
	CurrentLetter.AppendChar(MessageText[LetterIndex]);

	//Creating the letter widget and setting the text to the desired char
	UUserWidget* WLetter = CreateWidget(GetWorld()->GetFirstPlayerController(), WidgetLetter);
	UTextBlock* Text = Cast<UTextBlock>(WLetter->GetWidgetFromName(TEXT("Letter")));
	Text->SetText(FText::FromString(CurrentLetter));

	return WLetter;
}

void UDialogueComponent::ClearMessage() {
	MessageText.Empty();
	// Get the text box from the HUD
	UWrapBox* TextBox = Cast<UWrapBox>(DialogueHUD->GetWidgetFromName(TEXT("TextBox")));
	for (UWidget* Word : TextBox->GetAllChildren()) {
		Word->RemoveFromParent();
		CollectGarbage(EObjectFlags::RF_NoFlags);
	}
}

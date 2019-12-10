// We got no rights, just please don't steal


#include "SlimeController.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Components/HorizontalBox.h"
#include "TimerManager.h"
#include "WidgetBlueprintLibrary.h"

void ASlimeController::BeginPlay(){
	Super::BeginPlay();

	CreateHUD();

	SetMessage("You harvested some WAMBA ARMS! You have the ability to CLIMB WALLS until they are no longer in you!", .02f);
}

/*
 * Creates the HUD widget
 *
 * Returns true if HUD is successfully created
 */
bool ASlimeController::CreateHUD() {
	if (WidgetHUD) {
		HUD = CreateWidget(this, WidgetHUD);
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
void ASlimeController::SetMessage(FString Message, float Time) {
	MessageText = Message;
	LetterDelayInSeconds = Time;
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this, HUD, EMouseLockMode::DoNotLock);
	MakeMessage();
	
}

/*
 * Adds the message to the on screen text box
 *
 */
void ASlimeController::MakeMessage() {
	//Checking if we should exit
	if(LetterIndex >= MessageText.Len()) {
		LetterIndex = 0;
		return;
	}
	
	// Initialising local variables
	UUserWidget* WLetter = CreateWidget(this, WidgetLetter);
	UTextBlock* Text = Cast<UTextBlock>(WLetter->GetWidgetFromName(TEXT("Letter")));
	FString CurrentLetter = "";

	// Setting string to desired character because FTexts don't convert any char types directly :(
	CurrentLetter.AppendChar(MessageText[LetterIndex]);
	Text->SetText(FText::FromString(CurrentLetter));

	LetterArray.Add(WLetter);

	if (MessageText[LetterIndex] == ' ' || LetterIndex + 1 == MessageText.Len()) {
		UWrapBox* TextBox = Cast<UWrapBox>(HUD->GetWidgetFromName(TEXT("TextBox")));
		// Returns if there is no text box on HUD
		if (!TextBox) return;
		UUserWidget* WWord = MakeWord(LetterArray);
		TextBox->AddChildToWrapBox(WWord);
		WordIndex++;
		LetterArray.Empty();
	}
	
	//  Incrementing index
	LetterIndex++;

	// Looping after a delay
	GetWorld()->GetTimerManager().SetTimer(LetterTimer, this, &ASlimeController::MakeMessage, LetterDelayInSeconds);
}

UUserWidget* ASlimeController::MakeWord(TArray<UUserWidget*> LetterArray) {
	UUserWidget* WWord = CreateWidget(this, WidgetWord);
	for (UUserWidget* Letter : LetterArray) {
		UHorizontalBox* WordBox = Cast<UHorizontalBox>(WWord->GetWidgetFromName("WordBox"));
		WordBox->AddChildToHorizontalBox(Letter);
	}
	return WWord;
}


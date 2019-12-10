// We got no rights, just please don't steal


#include "SlimeController.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "TimerManager.h"
#include "WidgetBlueprintLibrary.h"

void ASlimeController::BeginPlay(){
	Super::BeginPlay();

	CreateHUD();
}

/*
 * Creates the HUD widget
 *
 * Returns true if HUD is successfully created
 */
bool ASlimeController::CreateHUD() {
	if (ensure(WidgetHUD)) {
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
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this, HUD);
	MakeMessage();
	
}

/*
 * Adds the message to the on screen text box
 *
 */
void ASlimeController::MakeMessage() {
	//Checking if we should exit
	if(CurrentIndex >= MessageText.Len()) {
		CurrentIndex = 0;
		return;
	}
	
	// Initialising local variables
	UUserWidget* WLetter = CreateWidget(this, WidgetLetter);
	UTextBlock* Text = Cast<UTextBlock>(WLetter->GetWidgetFromName(TEXT("Letter")));
	UWrapBox* TextBox = Cast<UWrapBox>(HUD->GetWidgetFromName(TEXT("TextBox")));
	FString CurrentLetter = "";

	// Setting string to desired character because FTexts don't convert any chars directly :(
	CurrentLetter.AppendChar(MessageText[CurrentIndex]);
	Text->SetText(FText::FromString(CurrentLetter));
	
	// Returns if there is no text box on HUD
	if (!TextBox) return;
	
	TextBox->AddChildToWrapBox(WLetter);
	
	//  Incrementing index
	CurrentIndex += 1;

	// Looping after a delay
	GetWorld()->GetTimerManager().SetTimer(LetterTimer, this, &ASlimeController::MakeMessage, LetterDelayInSeconds);
}


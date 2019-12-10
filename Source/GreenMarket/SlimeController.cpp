// We got no rights, just please don't steal


#include "SlimeController.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MyWrapBox.h"

void ASlimeController::BeginPlay(){
	Super::BeginPlay();

	CreateHUD();
	AddMessage(MessageText);
}

/*
 * Creates the HUD widget
 *
 * Returns true if HUD is successfully created
 */
bool ASlimeController::CreateHUD() {
	if (ensure(WidgetHUD)) {
		HUD = CreateWidget(this, WidgetHUD);
		//If HUD is created correctly
		if (HUD) {
			HUD->AddToViewport();
			//Only return true if the HUD is created AND added to viewport correctly
			return true;
		}
	}
	//Returns false if not created AND added correctly
	return false;
}

/*
 * Adds a message to the on screen text box
 *
 *  @param Message The message to display
 */
void ASlimeController::AddMessage(FString Message) {
	for (int i = 0; i < Message.Len(); i++) {
		AddLetter(Message[i]);
	}
}

/*
 * Adds a letter to the text box on HUD
 *
 *  @param Letter Letter to add
 */
void ASlimeController::AddLetter(char Char) {
	// Initialising local variables
	UUserWidget* WLetter = CreateWidget(this, WidgetLetter);
	UTextBlock* Text = Cast<UTextBlock>(WLetter->GetWidgetFromName(TEXT("Letter")));
	UMyWrapBox* TextBox = Cast<UMyWrapBox>(HUD->GetWidgetFromName(TEXT("TextBox")));
	FString CurrentLetter = "";

	// Setting string to desired character because FTexts don't convert chars directly :(
	CurrentLetter.AppendChar(Char);
	Text->SetText(FText::FromString(CurrentLetter));
	// Returns if there is no text box on HUD
	if (!TextBox) return;
	TextBox->AddChildToWrapBox(WLetter);
}

// We got no rights, just please don't steal


#include "SlimeController.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MyWrapBox.h"

void ASlimeController::BeginPlay(){
	Super::BeginPlay();

	CreateHUD();
	AddMessage("Hello World!");
}

bool ASlimeController::CreateHUD() {
	if (ensure(WidgetHUD)) {
		HUD = CreateWidget(this, WidgetHUD);
		if (HUD) {
			HUD->AddToViewport();
			return true;
		}
	}
	return false;
}

void ASlimeController::AddMessage(FString Message) {
	for (int i = 0; i < Message.Len(); i++) {
		AddLetter(Message[i]);
	}
}

void ASlimeController::AddLetter(char Letter) {
	FString CurrentLetter = "";
	CurrentLetter.AppendChar(Letter);
	UUserWidget* WLetter = CreateWidget(this, WidgetLetter);
	UTextBlock* Text = Cast<UTextBlock>(WLetter->GetWidgetFromName(TEXT("Letter")));
	Text->SetText(FText::FromString(CurrentLetter));
	UMyWrapBox* TextBox = Cast<UMyWrapBox>(HUD->GetWidgetFromName(TEXT("TextBox")));
	if (!TextBox) return;
	TextBox->AddChildToWrapBox(WLetter);
}

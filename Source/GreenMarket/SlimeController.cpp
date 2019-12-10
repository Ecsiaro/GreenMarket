// Fill out your copyright notice in the Description page of Project Settings.


#include "SlimeController.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MyWrapBox.h"

void ASlimeController::BeginPlay(){
	Super::BeginPlay();

	CreateHUD();
}

UUserWidget* ASlimeController::CreateHUD() {
	if (ensure(WidgetHUD)) {
		HUD = CreateWidget(this, WidgetHUD);
		if (HUD) {
			HUD->AddToViewport();
			for (int i = 0; i < MessageText.Len(); i++) {
				AddLetter(MessageText[i]);
			}

		}
	}
}

void ASlimeController::AddLetter(char letter) {
	FString CurrentLetter = "";
	CurrentLetter.AppendChar(letter);
	UUserWidget* Letter = CreateWidget(this, WidgetLetter);
	UTextBlock* Text = Cast<UTextBlock>(Letter->GetWidgetFromName(TEXT("Letter")));
	Text->SetText(FText::FromString(CurrentLetter));
	UMyWrapBox* TextBox = Cast<UMyWrapBox>(HUD->GetWidgetFromName(TEXT("TextBox")));
	if (!TextBox) return;
	TextBox->AddChildToWrapBox(Letter);
}

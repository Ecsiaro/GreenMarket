// Fill out your copyright notice in the Description page of Project Settings.

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Heads Up Display")
	TSubclassOf<UUserWidget> WidgetHUD;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Heads Up Display")
	UUserWidget* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subtitles")
	TSubclassOf<UUserWidget> WidgetLetter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subtitles")
	FString MessageText = "Hello";

	void AddLetter(char index);

	TArray<FName> SlotNames;

private:
	TArray<UUserWidget*> Letters;
	
};

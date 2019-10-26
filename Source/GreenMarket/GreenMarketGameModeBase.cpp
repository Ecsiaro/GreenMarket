// Fill out your copyright notice in the Description page of Project Settings.


#include "GreenMarketGameModeBase.h"
#include "UObject/ConstructorHelpers.h"

AGreenMarketGameModeBase::AGreenMarketGameModeBase()
	: Super() {
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/Player/BP_SlimeCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

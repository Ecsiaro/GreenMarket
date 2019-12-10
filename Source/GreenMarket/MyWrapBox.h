// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WrapBox.h"
#include "MyWrapBox.generated.h"

/**
 * 
 */
UCLASS()
class GREENMARKET_API UMyWrapBox : public UWrapBox
{
	GENERATED_BODY()

public:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	
};

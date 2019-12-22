// We got no rights, just please don't steal

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DialogueTable.generated.h"


/*
 *
 */

USTRUCT(BlueprintType)
struct FDialogueTable : public FTableRowBase {
	GENERATED_BODY()

	public:
	// Text to go in dialogue box
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DialogueText = "";

	// Amount of replies there will be
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ReplyCount;

	// Text to go in reply 1
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ReplyOneText;

	// Name of table entry to be used next if reply 1 is selected
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ReplyOneNext;

	// Text to go in reply 2
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ReplyTwoText;

	// Name of table entry to be used next if reply 2 is selected
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ReplyTwoNext;

	// Text to go in reply 3
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ReplyThreeText;

	// Name of table entry to be used next if reply 3 is selected
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ReplyThreeNext;

	// Text to go in reply 4
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ReplyFourText;

	// Name of table entry to be used next if reply 4 is selected
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ReplyFourNext;
};
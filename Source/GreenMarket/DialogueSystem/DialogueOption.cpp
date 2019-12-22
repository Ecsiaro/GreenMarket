// We got no rights, just please don't steal


#include "DialogueOption.h"
#include "Engine/Engine.h"
#include "Components/TextBlock.h"

void UDialogueOption::FindText() {
	for (UWidget* Child : GetAllChildren()) {
		UTextBlock* temp = Cast<UTextBlock>(Child);
		if (temp) { Text = temp; }
	}
}


#include "TaskPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

void ATaskPlayerController::BeginPlay()
{
    Super::BeginPlay();


    UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    if (InputSubsystem)
    {
        UInputMappingContext* IMC = LoadObject<UInputMappingContext>(nullptr, TEXT("/Game/Input/IMC_Task.IMC_Task"));
        if (IMC)
        {
            InputSubsystem->AddMappingContext(IMC, 0);
        }
    }
}


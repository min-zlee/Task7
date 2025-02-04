#include "TaskGameMode.h"
#include "TaskCharacter.h"
#include "TaskPlayerController.h"

ATaskGameMode::ATaskGameMode()
{

    DefaultPawnClass = ATaskCharacter::StaticClass();//기본 Pawn<< TaskCharacter 설정
    PlayerControllerClass = ATaskPlayerController::StaticClass();//기본 PlayerController << TaskPlayerController 설정
}

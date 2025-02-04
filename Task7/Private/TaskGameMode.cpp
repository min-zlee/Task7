#include "TaskGameMode.h"
#include "TaskCharacter.h"
#include "TaskPlayerController.h"

ATaskGameMode::ATaskGameMode()
{
    // 기본 Pawn을 TaskCharacter로 설정
    DefaultPawnClass = ATaskCharacter::StaticClass();

    // 기본 PlayerController를 TaskPlayerController로 설정
    PlayerControllerClass = ATaskPlayerController::StaticClass();
}

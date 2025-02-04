#include "TaskGameMode.h"
#include "TaskCharacter.h"
#include "TaskPlayerController.h"

ATaskGameMode::ATaskGameMode()
{
    // �⺻ Pawn�� TaskCharacter�� ����
    DefaultPawnClass = ATaskCharacter::StaticClass();

    // �⺻ PlayerController�� TaskPlayerController�� ����
    PlayerControllerClass = ATaskPlayerController::StaticClass();
}

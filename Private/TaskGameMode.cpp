#include "TaskGameMode.h"
#include "TaskCharacter.h"
#include "TaskPlayerController.h"

ATaskGameMode::ATaskGameMode()
{

    DefaultPawnClass = ATaskCharacter::StaticClass();//�⺻ Pawn<< TaskCharacter ����
    PlayerControllerClass = ATaskPlayerController::StaticClass();//�⺻ PlayerController << TaskPlayerController ����
}

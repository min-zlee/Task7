#include "TaskCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"

ATaskCharacter::ATaskCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
    RootComponent = CapsuleComponent;

    MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(CapsuleComponent);

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArmComponent->SetupAttachment(CapsuleComponent);
    SpringArmComponent->TargetArmLength = 300.0f;
    SpringArmComponent->bUsePawnControlRotation = false;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComponent->SetupAttachment(SpringArmComponent);

    bUseControllerRotationYaw = false;
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;//Pawn이 컨트롤러를 사용하여 회전하도록 설정?
 
    MoveAction = nullptr;
    StrafeAction = nullptr;
    LookAction = nullptr;
    TurnAction = nullptr;
}
void ATaskCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ATaskCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    TaskDeltaTime = DeltaTime;

}
void ATaskCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    if (EnhancedInput)
    {
        if (MoveAction)
            EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATaskCharacter::MoveForward);

        if (StrafeAction)
            EnhancedInput->BindAction(StrafeAction, ETriggerEvent::Triggered, this, &ATaskCharacter::MoveRight);

        if (LookAction)
            EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATaskCharacter::LookUp);

        if (TurnAction)
            EnhancedInput->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ATaskCharacter::Turn);
    }
}

void ATaskCharacter::MoveForward(const FInputActionValue& Value)
{
    float InputValue = Value.Get<float>();
    if (InputValue != 0.0f)
    {
        FRotator CameraRotation = CameraComponent->GetComponentRotation();
        FVector ForwardDirection = FRotationMatrix(CameraRotation).GetUnitAxis(EAxis::X);//상하 회전 무시
        ForwardDirection.Z = 0.0f;//평면이동이니까 z값 고정
        ForwardDirection.Normalize();

        AddActorWorldOffset(ForwardDirection * InputValue * 300.0f * TaskDeltaTime, true);
    }
}

void ATaskCharacter::MoveRight(const FInputActionValue& Value)
{
    float InputValue = Value.Get<float>();
    if (InputValue != 0.0f)
    {
        FRotator CameraRotation = CameraComponent->GetComponentRotation();
        FVector RightDirection = FRotationMatrix(CameraRotation).GetUnitAxis(EAxis::Y);//좌우 회전 무시
        RightDirection.Z = 0.0f;
        RightDirection.Normalize();

        AddActorWorldOffset(RightDirection * InputValue * 300.0f * TaskDeltaTime, true);
    }
}

void ATaskCharacter::LookUp(const FInputActionValue& Value)//마우스상하 시점이 움직여야함
{
    float InputValue = Value.Get<float>();
    if (InputValue != 0.0f)
    {
        FRotator NewRotation = SpringArmComponent->GetRelativeRotation();
        float NewPitch = NewRotation.Pitch - (InputValue * 50.0f * TaskDeltaTime);
        NewPitch = FMath::Clamp(NewPitch, -80.0f, 80.0f);
        SpringArmComponent->SetRelativeRotation(FRotator(NewPitch, 0.0f, 0.0f));
    }
}

void ATaskCharacter::Turn(const FInputActionValue& Value) //마우스좌우 actor가 움직임 
{
    float InputValue = Value.Get<float>();
    if (InputValue != 0.0f)
    {
         
        AddActorLocalRotation(FRotator(0, InputValue * 50.0f * TaskDeltaTime, 0));
    }
}

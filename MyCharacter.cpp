// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "MyPlayerController.h"

AMyCharacter::AMyCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArmComp->SetupAttachment(RootComponent);
    SpringArmComp->TargetArmLength = 300.0f;
    SpringArmComp->bUsePawnControlRotation = true;

    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
    CameraComp->bUsePawnControlRotation = false;

    NormalSpeed = 600.0f;
    SprintSpeedMultiplier = 1.5f;
    SprintSpeed = NormalSpeed * SprintSpeedMultiplier;

    GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
}



void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Enhanced InputComponent�� ĳ����
    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // IA�� �������� ���� ���� ���� ���� Controller�� ASpartaPlayerController�� ĳ����
		if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController()))
        {
            if (PlayerController->MoveAction)
            {
                // IA_Move �׼� Ű�� "Ű�� ������ �ִ� ����" Move() ȣ��
                EnhancedInput->BindAction(
                    PlayerController->MoveAction,
                    ETriggerEvent::Triggered,
                    this,
                    &AMyCharacter::Move
                );
            }

            if (PlayerController->JumpAction)
            {
                // IA_Jump �׼� Ű�� "Ű�� ������ �ִ� ����" StartJump() ȣ��
                EnhancedInput->BindAction(
                    PlayerController->JumpAction,
                    ETriggerEvent::Triggered,
                    this,
                    &AMyCharacter::StartJump
                );

                // IA_Jump �׼� Ű���� "���� �� ����" StopJump() ȣ��
                EnhancedInput->BindAction(
                    PlayerController->JumpAction,
                    ETriggerEvent::Completed,
                    this,
                    &AMyCharacter::StopJump
                );
            }

            if (PlayerController->LookAction)
            {
                // IA_Look �׼� ���콺�� "������ ��" Look() ȣ��
                EnhancedInput->BindAction(
                    PlayerController->LookAction,
                    ETriggerEvent::Triggered,
                    this,
                    &AMyCharacter::Look
                );
            }

            if (PlayerController->SprintAction)
            {
                // IA_Sprint �׼� Ű�� "������ �ִ� ����" StartSprint() ȣ��
                EnhancedInput->BindAction(
                    PlayerController->SprintAction,
                    ETriggerEvent::Triggered,
                    this,
                    &AMyCharacter::StartSprint
                );
                // IA_Sprint �׼� Ű���� "���� �� ����" StopSprint() ȣ��
                EnhancedInput->BindAction(
                    PlayerController->SprintAction,
                    ETriggerEvent::Completed,
                    this,
                    &AMyCharacter::StopSprint
                );
            }
        }
    }
}

void AMyCharacter::Move(const FInputActionValue& value)
{
    if (!Controller) return;

    // Value�� Axis2D�� ������ IA_Move�� �Է°� (WASD)�� ��� ����
// ��) (X=1, Y=0) �� ���� / (X=-1, Y=0) �� ���� / (X=0, Y=1) �� ������ / (X=0, Y=-1) �� ����
    const FVector2D MoveInput = value.Get<FVector2D>();

    if (!FMath::IsNearlyZero(MoveInput.X))
    {
        // ĳ���Ͱ� �ٶ󺸴� ����(����)���� X�� �̵�
        AddMovementInput(GetActorForwardVector(), MoveInput.X);
    }

    if (!FMath::IsNearlyZero(MoveInput.Y))
    {
        // ĳ������ ������ �������� Y�� �̵�
        AddMovementInput(GetActorRightVector(), MoveInput.Y);
    }
}

void AMyCharacter::StartJump(const FInputActionValue& value)
{
    // Jump �Լ��� Character�� �⺻ ����
    if (value.Get<bool>())
    {
        Jump();
    }
}

void AMyCharacter::StopJump(const FInputActionValue& value)
{
    if (!value.Get<bool>())
    {
        StopJumping();
    }
}

void AMyCharacter::Look(const FInputActionValue& value)
{
    FVector2D LookInput = value.Get<FVector2D>();

    // X�� �¿� ȸ�� (Yaw), Y�� ���� ȸ�� (Pitch)
    // �¿� ȸ��
    AddControllerYawInput(LookInput.X);
    // ���� ȸ��
    AddControllerPitchInput(LookInput.Y);
}

void AMyCharacter::StartSprint(const FInputActionValue& value)
{
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
    }
}

void AMyCharacter::StopSprint(const FInputActionValue& value)
{
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
    }
}



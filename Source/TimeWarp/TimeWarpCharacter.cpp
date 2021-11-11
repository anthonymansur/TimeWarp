// Copyright Epic Games, Inc. All Rights Reserved.

#include "TimeWarpCharacter.h"
#include "TimeWarpProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "TimeWarpGameState.h"
#include "TimeWarpGameMode.h"

#define RECORD_FREQUENCY 0.002 // NOTE: this is also defined in TimeWarpGameMode

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ATimeWarpCharacter

ATimeWarpCharacter::ATimeWarpCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

		

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.

	// Create VR Controllers.
	R_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("R_MotionController"));
	R_MotionController->MotionSource = FXRMotionControllerBase::RightHandSourceId;
	R_MotionController->SetupAttachment(RootComponent);
	L_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("L_MotionController"));
	L_MotionController->SetupAttachment(RootComponent);

	// Create a gun and attach it to the right-hand VR controller.
	// Create a gun mesh component
	VR_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VR_Gun"));
	VR_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	VR_Gun->bCastDynamicShadow = false;
	VR_Gun->CastShadow = false;
	VR_Gun->SetupAttachment(R_MotionController);
	VR_Gun->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	VR_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("VR_MuzzleLocation"));
	VR_MuzzleLocation->SetupAttachment(VR_Gun);
	VR_MuzzleLocation->SetRelativeLocation(FVector(0.000004, 53.999992, 10.000000));
	VR_MuzzleLocation->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));		// Counteract the rotation of the VR gun model.

	// Uncomment the following line to turn motion controllers on by default:
	//bUsingMotionControllers = true;

	// Create a mesh component that will be used when being viewed from a '2nd person' view
	Mesh2P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh2P"));
	Mesh2P->SetOwnerNoSee(true);
	Mesh2P->SetupAttachment(FirstPersonCameraComponent);

	// 2nd person gun mesh
	FP_Gun2P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun2P"));
	FP_Gun2P->SetOwnerNoSee(true);
	FP_Gun2P->AttachToComponent(Mesh2P, FAttachmentTransformRules::KeepRelativeTransform, "gun_socket");

	// Initiallize the player's health
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;

	CurrentAmmo = 10;

	// Disable movement by default
	bRotationEnabled = false;
	bTranslationEnabled = false;

	// Disable firing by default
	bCanShoot = false;

	// path highlight
	static ConstructorHelpers::FClassFinder<AActor> LineClassFinder(TEXT("/Game/Line"));
	PathLineClass = LineClassFinder.Class;

	// set positionIndex
	PositionIndex = 0;

	// initialize IsTimeTraveling
	IsTimeTraveling = false;
}

void ATimeWarpCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	if (bUsingMotionControllers)
	{
		VR_Gun->SetHiddenInGame(false, true);
		Mesh1P->SetHiddenInGame(true, true);
	}
	else
	{
		VR_Gun->SetHiddenInGame(true, true);
		Mesh1P->SetHiddenInGame(false, true);
	}

}

//////////////////////////////////////////////////////////////////////////
// Input

void ATimeWarpCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATimeWarpCharacter::OnFire);

	// Enable touchscreen input
	EnableTouchscreenMovement(PlayerInputComponent);

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ATimeWarpCharacter::OnResetVR);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ATimeWarpCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATimeWarpCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &ATimeWarpCharacter::Turn);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATimeWarpCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &ATimeWarpCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATimeWarpCharacter::LookUpAtRate);

	// Bind controls for moving foreward and backward in time
	PlayerInputComponent->BindAxis("TimeForward", this, &ATimeWarpCharacter::TimeForward);
	PlayerInputComponent->BindAxis("TimeBackward", this, &ATimeWarpCharacter::TimeBackward);
}

void ATimeWarpCharacter::OnFire()
{
	if (CurrentAmmo < 1)
	{
		DisableShooting();
		return;
	}

	if (!bCanShoot)
		return;

	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		HandleFire();
		CurrentAmmo--;

	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void ATimeWarpCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ATimeWarpCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnFire();
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void ATimeWarpCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;
}

//Commenting this section out to be consistent with FPS BP template.
//This allows the user to turn without using the right virtual joystick

//void ATimeWarpCharacter::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
//{
//	if ((TouchItem.bIsPressed == true) && (TouchItem.FingerIndex == FingerIndex))
//	{
//		if (TouchItem.bIsPressed)
//		{
//			if (GetWorld() != nullptr)
//			{
//				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
//				if (ViewportClient != nullptr)
//				{
//					FVector MoveDelta = Location - TouchItem.Location;
//					FVector2D ScreenSize;
//					ViewportClient->GetViewportSize(ScreenSize);
//					FVector2D ScaledDelta = FVector2D(MoveDelta.X, MoveDelta.Y) / ScreenSize;
//					if (FMath::Abs(ScaledDelta.X) >= 4.0 / ScreenSize.X)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.X * BaseTurnRate;
//						AddControllerYawInput(Value);
//					}
//					if (FMath::Abs(ScaledDelta.Y) >= 4.0 / ScreenSize.Y)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.Y * BaseTurnRate;
//						AddControllerPitchInput(Value);
//					}
//					TouchItem.Location = Location;
//				}
//				TouchItem.Location = Location;
//			}
//		}
//	}
//}

void ATimeWarpCharacter::MoveForward(float Value)
{
	if (bTranslationEnabled && Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ATimeWarpCharacter::MoveRight(float Value)
{
	if (bTranslationEnabled && Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ATimeWarpCharacter::Turn(float rate)
{
	if (bRotationEnabled)
	{
		APawn::AddControllerYawInput(rate);
	}
}

void ATimeWarpCharacter::LookUp(float rate)
{
	if (bRotationEnabled)
	{
		APawn::AddControllerPitchInput(rate);
	}
}

void ATimeWarpCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	if (bRotationEnabled)
	{
		AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void ATimeWarpCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	if (bRotationEnabled)
	{
		AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}

void ATimeWarpCharacter::TimeForward(float Val)
{
	// Note that Val is positive
	if (Val != 0.0f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, "Q (TimeForward) Pressed!");
		SetIsTimeTraveling(true);
		SetPositionIndex(PositionIndex + static_cast<int>(Val * 10.f));
	}
	else {
		SetIsTimeTraveling(false);
	}
}

void ATimeWarpCharacter::TimeBackward(float Val)
{
	// Note that Val is negative
	if (Val != 0.0f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, "E (TimeBackward) Pressed!");
		SetIsTimeTraveling(true);
		SetPositionIndex(PositionIndex + static_cast<int>(Val * 10.f));
	}
	else {
		SetIsTimeTraveling(false);
	}
}

bool ATimeWarpCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ATimeWarpCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &ATimeWarpCharacter::EndTouch);

		//Commenting this out to be more consistent with FPS BP template.
		//PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ATimeWarpCharacter::TouchUpdate);
		return true;
	}
	
	return false;
}

void ATimeWarpCharacter::OnHealthUpdate()
{
	// Client-specific functionality
	if (IsLocallyControlled())
	{
		//FString healthMessage = FString::Printf(TEXT("You now have %f health remaining."), CurrentHealth);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);
	}

	// Server-specific functionality
	if (GetLocalRole() == ROLE_Authority)
	{
		//FString healthMessage = FString::Printf(TEXT("%s now has %f health remaining."), *GetFName().ToString(), CurrentHealth);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);
	}

	if (abs(CurrentHealth) <= 0.001f)
	{
		//FString deathMessage = FString::Printf(TEXT("You have been killed."));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, deathMessage);

		if (GetWorld()->IsServer())
		{
			// End match 
			ATimeWarpGameMode* gameMode = static_cast<ATimeWarpGameMode*>(GetWorld()->GetAuthGameMode());
			gameMode->EndElimination();
		}
	}
	//Functions that occur on all machines. 
   /*
	   Any special functionality that should occur as a result of damage or death should be placed here.
   */
}

void ATimeWarpCharacter::SetCurrentHealth(float healthValue)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		CurrentHealth = FMath::Clamp(healthValue, 0.f, MaxHealth);
		OnHealthUpdate();
	}
}


void ATimeWarpCharacter::SetCurrentAmmo(int ammoValue)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		CurrentAmmo = ammoValue;
	}
}


void ATimeWarpCharacter::SetPositionIndex_Implementation(int posValue)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		PositionIndex = posValue;
	}
}


void ATimeWarpCharacter::SetIsTimeTraveling_Implementation(bool boolValue)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		IsTimeTraveling = boolValue;
	}
}

float ATimeWarpCharacter::TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (CurrentHealth > 0.01f)
	{
		float damageApplied = CurrentHealth - DamageTaken;
		SetCurrentHealth(damageApplied);
		return damageApplied;
	}
	return 0;
}

bool ATimeWarpCharacter::IsDead()
{
	return abs(CurrentHealth) < 0.001f;
}

void ATimeWarpCharacter::AllowRotation()
{
	bRotationEnabled = true;
}

void ATimeWarpCharacter::AllowTranslation()
{
	bTranslationEnabled = true;
}

void ATimeWarpCharacter::AllowShooting()
{
	bCanShoot = true;
}

void ATimeWarpCharacter::DisableRotation()
{
	bRotationEnabled = false;
}
void ATimeWarpCharacter::DisableTranslation()
{
	bTranslationEnabled = false;
}
void ATimeWarpCharacter::DisableShooting()
{
	bCanShoot = false;
}

//////////////////////////////////////////////////////////////////////////
// Replicated Properties

void ATimeWarpCharacter::GetLifetimeReplicatedProps(TArray <FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicate current health.
	DOREPLIFETIME(ATimeWarpCharacter, CurrentHealth);
	DOREPLIFETIME(ATimeWarpCharacter, CurrentAmmo);
	DOREPLIFETIME(ATimeWarpCharacter, bRotationEnabled);
	DOREPLIFETIME(ATimeWarpCharacter, bTranslationEnabled);
	DOREPLIFETIME(ATimeWarpCharacter, bCanShoot);
	DOREPLIFETIME(ATimeWarpCharacter, timeRemaining);
	DOREPLIFETIME(ATimeWarpCharacter, PositionIndex);
	DOREPLIFETIME(ATimeWarpCharacter, IsTimeTraveling);
}

//////////////////////////////////////////////////////////////////////////
// Replication Handlers

void ATimeWarpCharacter::OnRep_CurrentHealth()
{
	OnHealthUpdate();
}

//////////////////////////////////////////////////////////////////////////
// RPCs
void ATimeWarpCharacter::HandleFire_Implementation()
{
	UWorld* const World = GetWorld();
	if (World != NULL)
	{
		if (bUsingMotionControllers)
		{
			const FRotator SpawnRotation = VR_MuzzleLocation->GetComponentRotation();
			const FVector SpawnLocation = VR_MuzzleLocation->GetComponentLocation();
			World->SpawnActor<ATimeWarpProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
		}
		else
		{
			const FRotator SpawnRotation = GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			ActorSpawnParams.Instigator = this;

			// spawn the projectile at the muzzle
			World->SpawnActor<ATimeWarpProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}
}

// helper function
void ATimeWarpCharacter::DrawSinglePath(int i)
{
	if ((i + 10) >= PositionBuffer->Num())
		return;
	FVector posDiff = FVector((*PositionBuffer)[i + 10]) - FVector((*PositionBuffer)[i]);
	posDiff[2] = 0;
	float angle = FMath::Acos(FVector::DotProduct(FVector(1, 0, 0), posDiff.GetSafeNormal()));
	FTransform transform = FTransform();
	transform.SetLocation(FVector((*PositionBuffer)[i].X, (*PositionBuffer)[i].Y, 171));
	transform.SetRotation(FQuat(0, 0, 1, angle));

	FActorSpawnParameters ActorSpawnParams;
	Lines.Add(GetWorld()->SpawnActor<AActor>(PathLineClass, transform, ActorSpawnParams));
	Lines.Last()->SetActorScale3D(FVector(0.1, 2, 1));
}

void ATimeWarpCharacter::DrawPaths()
{
	static ATimeWarpGameMode* gameMode = static_cast<ATimeWarpGameMode*>(GetWorld()->GetAuthGameMode());
	static const float drawInterval = RECORD_FREQUENCY; // interval, in seconds, to draw line 
	static const float drawLength = 1; // draw the path one second ahead 
	static const int numOfLinesToDraw = 2 * (int)(drawLength / drawInterval);

	if (Lines.Num() == 0)
	{
		for (int i = 0; i < numOfLinesToDraw; i++)
		{
			DrawSinglePath(i);
		}
	}
	else
	{
		Lines[0]->Destroy();
		Lines.RemoveAt(0);
		if ((posInx + numOfLinesToDraw) < (PositionBuffer->Num() - 1))
			DrawSinglePath(posInx + numOfLinesToDraw);
	}
	posInx++;
}

void ATimeWarpCharacter::SendPositionArray_Implementation(bool player1)
{
	if (player1)
		PositionBuffer = static_cast<ATimeWarpGameState*>(GetWorld()->GetGameState())->getP1Position(); 
	else
		PositionBuffer = static_cast<ATimeWarpGameState*>(GetWorld()->GetGameState())->getP2Position();
}

void ATimeWarpCharacter::StartDrawPathCommand_Implementation()
{
	ATimeWarpGameMode* gameMode = static_cast<ATimeWarpGameMode*>(GetWorld()->GetAuthGameMode());
	const float drawInterval = RECORD_FREQUENCY; // interval, in seconds, to draw line 
	GetWorldTimerManager().SetTimer(handle_drawPath, this, &ATimeWarpCharacter::DrawPaths, drawInterval, true, 0.f);

}
void ATimeWarpCharacter::EndDrawPathCommand_Implementation()
{
	GetWorldTimerManager().ClearTimer(handle_drawPath);
	int size = Lines.Num();
	for (int i = 0; i < size; i++)
		Lines.Pop()->Destroy();
	posInx = 0;
}

void ATimeWarpCharacter::SetTimeRemaining_Implementation(int time)
{
	timeRemaining = time;

	if (time > 0)
	{
		GetWorldTimerManager().SetTimer(handle_timeRemaining, this, &ATimeWarpCharacter::UpdateTime, 1, true, 0.f);
	}
}

void ATimeWarpCharacter::UpdateTime()
{
	timeRemaining -= 1;
	if (timeRemaining == 0)
		GetWorldTimerManager().ClearTimer(handle_timeRemaining);
}


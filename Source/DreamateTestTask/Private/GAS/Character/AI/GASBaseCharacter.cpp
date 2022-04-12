// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Character/AI/GASBaseCharacter.h"
#include "DreamateTestTask/Public/Inventory/Weapon/Weapon.h"

// Sets default values
AGASBaseCharacter::AGASBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("AttributeSet"));
	StimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(
		TEXT("PerceptionStimuliSourceComponent"));
	WeaponComponent = CreateDefaultSubobject<UChildActorComponent>("WeaponComponent");
	/*WeaponComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules((EAttachmentRule::SnapToTarget), false), "middle_02_r");*/
	WeaponComponent->SetupAttachment(GetMesh(), "Weapon_r");
}

UAbilitySystemComponent* AGASBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void AGASBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	for (const auto& Ability : StandardAbilities)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability.Value, 1,static_cast<int32>(Ability.Key)));
	}
	
}

void AGASBaseCharacter::InitializeDefaultAttributesAndEffects()
{
	if (DefaultAttributes)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 0.f, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
		}
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	
	for (const auto& Effect : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, 0.f, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
		}
	}
}

// Called every frame
void AGASBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGASBaseCharacter::Attack()
{
	AbilitySystemComponent->TryActivateAbilityByClass(StandardAbilities[EAbilities::Attack]);
}
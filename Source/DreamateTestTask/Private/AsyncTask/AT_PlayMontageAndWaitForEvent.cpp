// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTask/AT_PlayMontageAndWaitForEvent.h"

#include "AbilitySystemComponent.h"
#include "AnimNotify/ANS_ApplyGameplayEffectBase.h"
#include "GameFramework/Character.h"

void UAT_PlayMontageAndWaitForEvent::Activate()
{

	if (!Ability)
	{
		return;
	}

	bool bPlayedMontage = false;

	if (AbilitySystemComponent)
	{
		const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
		UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
		if (AnimInstance)
		{
			EventHandle = AbilitySystemComponent->AddGameplayEventTagContainerDelegate(EventTags, FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &UAT_PlayMontageAndWaitForEvent::OnGameplayEvent));
			if (AbilitySystemComponent->PlayMontage(Ability, Ability->GetCurrentActivationInfo(), MontageToPlay, Rate, StartSection) > 0.f)
			{
				if (!ShouldBroadcastAbilityTaskDelegates())
				{
					return;
				}
				CancelledHandle = Ability->OnGameplayAbilityCancelled.AddUObject(this, &UAT_PlayMontageAndWaitForEvent::OnAbilityCanceled);

				BlendingOutDelegate.BindUObject(this, &UAT_PlayMontageAndWaitForEvent::OnMontageBlendingOut);
				AnimInstance->Montage_SetBlendingOutDelegate(BlendingOutDelegate, MontageToPlay);

				MontageEndedDelegate.BindUObject(this, &UAT_PlayMontageAndWaitForEvent::OnMontageEnded);
				AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, MontageToPlay);

				if (ACharacter* Character = Cast<ACharacter>(GetAvatarActor()))
				{
					Character->SetAnimRootMotionTranslationScale(AnimRootMotionTranslationScale);
				}

				bPlayedMontage = true;
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("URPGAbilityTask_PlayMontageAndWaitForEvent call to PlayMontage failed!"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("URPGAbilityTask_PlayMontageAndWaitForEvent called on invalid AbilitySystemComponent"));
		}
		if (!bPlayedMontage)
		{
			UE_LOG(LogTemp, Warning,  TEXT("URPGAbilityTask_PlayMontageAndWaitForEvent called in Ability %s failed to play montage %s; Task Instance Name %s."), *Ability->GetName(), *GetNameSafe(MontageToPlay),*InstanceName.ToString());
			if (ShouldBroadcastAbilityTaskDelegates())
			{
				OnCanceled.Broadcast(FGameplayTag(), FGameplayEventData());
			}

			SetWaitingOnAvatar();
		}
	}
}

void UAT_PlayMontageAndWaitForEvent::ExternalCancel()
{
	check(AbilitySystemComponent);

	OnAbilityCanceled();
	
	Super::ExternalCancel();
}

void UAT_PlayMontageAndWaitForEvent::OnDestroy(bool bAbilityEnded)
{
	if (Ability)
	{
		Ability->OnGameplayAbilityCancelled.Remove(CancelledHandle);
		if (bAbilityEnded && bStopWhenAbilityEnds)
		{
			StopPlayingMontage();
		}
	}
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(EventTags, EventHandle);
	}
	Super::OnDestroy(bAbilityEnded);
}

UAT_PlayMontageAndWaitForEvent* UAT_PlayMontageAndWaitForEvent::PlayMontageAndWaitForEvent(
	UGameplayAbility* OwningAbility, FName TaskInstanceName, UAnimMontage* MontageToPlay,
	FGameplayTagContainer EventTags, float Rate, FName StartSection, bool bStopWhenAbilityEnds,
	float AnimRootMotionTranslationScale)
{
	UAT_PlayMontageAndWaitForEvent* Task = NewAbilityTask<UAT_PlayMontageAndWaitForEvent>(OwningAbility, TaskInstanceName);
	Task->MontageToPlay = MontageToPlay;
	Task->EventTags = EventTags;
	Task->Rate = Rate;
	Task->StartSection = StartSection;
	Task->bStopWhenAbilityEnds = bStopWhenAbilityEnds;
	Task->AnimRootMotionTranslationScale = AnimRootMotionTranslationScale;
	return Task;
}

bool UAT_PlayMontageAndWaitForEvent::StopPlayingMontage()
{
	const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
	if (!ActorInfo)
	{
		return false;
	}
	UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
	if (!AnimInstance)
	{
		return false;
	}
	if (AbilitySystemComponent && Ability)
	{
		if (AbilitySystemComponent->GetAnimatingAbility() == Ability && AbilitySystemComponent->GetCurrentMontage() == MontageToPlay)
		{
			FAnimMontageInstance* MontageInstance = AnimInstance->GetActiveInstanceForMontage(MontageToPlay);
			if (MontageToPlay)
			{
				MontageInstance->OnMontageBlendingOutStarted.Unbind();
				MontageInstance->OnMontageEnded.Unbind();
			}
			AbilitySystemComponent->CurrentMontageStop();
			return true;
		}
	}
	return false;
}

void UAT_PlayMontageAndWaitForEvent::OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted)
{
	if (Ability && Ability->GetCurrentMontage() == MontageToPlay)
	{
		if (Montage == MontageToPlay)
		{
			AbilitySystemComponent->ClearAnimatingAbility(Ability);
			if (ACharacter* Character = Cast<ACharacter>(GetAvatarActor()))
			{
				Character->SetAnimRootMotionTranslationScale(1.f);
			}
		}
	}
	if (bInterrupted)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnInterrupted.Broadcast(FGameplayTag(), FGameplayEventData());
		}
	}
	else
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnBlendOut.Broadcast(FGameplayTag(), FGameplayEventData());
		}
	}
}

void UAT_PlayMontageAndWaitForEvent::OnAbilityCanceled()
{
	if (StopPlayingMontage())
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnCanceled.Broadcast(FGameplayTag(), FGameplayEventData());
		}
	}
}

void UAT_PlayMontageAndWaitForEvent::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (!bInterrupted)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnCompleted.Broadcast(FGameplayTag(), FGameplayEventData());
		}
	}
}

void UAT_PlayMontageAndWaitForEvent::OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		FGameplayEventData TempData = *Payload;
		TempData.EventTag = EventTag;
		EventReceived.Broadcast(EventTag, TempData);
	}
}
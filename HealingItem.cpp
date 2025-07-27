// Fill out your copyright notice in the Description page of Project Settings.


#include "HealingItem.h"

AHealingItem::AHealingItem()
{
		HealAmount = 20.0f; 
		ItemType = "Healing";
}

void AHealingItem::ActiveItem(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		// ȸ�� ����� �޽���
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Player gained %d HP!"), HealAmount));
	}
	DestroyItem();
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinItem.h"
#include "Engine/World.h"
#include "MyGameState.h"

ACoinItem::ACoinItem()
{
	PointValue = 0;
	ItemType = "DefaultCoin";
}

void ACoinItem::ActiveItem(AActor* Activator)
{
    // 플레이어 태그 확인
    if (Activator && Activator->ActorHasTag("Player"))
    {
        if (UWorld* World = GetWorld())
        {
            if (AMyGameState* GameState = World->GetGameState<AMyGameState>())
            {
                GameState->AddScore(PointValue);
                GameState->OnCoinCollected();
            }
        }

        // 부모 클래스 (BaseItem)에 정의된 아이템 파괴 함수 호출
        DestroyItem();
    }
}
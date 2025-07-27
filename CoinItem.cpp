// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinItem.h"

ACoinItem::ACoinItem()
{
	PointValue = 0;
	ItemType = "DefaultCoin";
}

void ACoinItem::ActiveItem(AActor* Activator)
{
    // �÷��̾� �±� Ȯ��
    if (Activator && Activator->ActorHasTag("Player"))
    {
        // ���� ȹ�� ����� �޽���
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Player gained %d points!"), PointValue));

        // �θ� Ŭ���� (BaseItem)�� ���ǵ� ������ �ı� �Լ� ȣ��
        DestroyItem();
    }
}
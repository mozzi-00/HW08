// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoinItem.h"
#include "SmallCoinItem.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ASmallCoinItem : public ACoinItem
{
	GENERATED_BODY()
	
public:	
	ASmallCoinItem();

	virtual void ActiveItem(AActor* Activtor) override;
};


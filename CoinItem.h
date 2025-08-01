// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "CoinItem.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ACoinItem : public ABaseItem
{
	GENERATED_BODY()
public:
	ACoinItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 PointValue;

	virtual void ActiveItem(AActor* Activator) override;
};

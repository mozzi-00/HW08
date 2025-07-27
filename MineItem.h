// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "MineItem.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMineItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	AMineItem();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USphereComponent* ExplosionCollision;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ExplosionDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ExplosionRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int ExplosionDamage;
	
	FTimerHandle ExplosionTimerHandle;

	virtual void ActiveItem(AActor* Activator) override;
	
	void Explode();

};

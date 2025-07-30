// Fill out your copyright notice in the Description page of Project Settings.


#include "BigCoinItem.h"

ABigCoinItem::ABigCoinItem()
{
	ItemType = "BigCoin";
	PointValue = 50;
}

void ABigCoinItem::ActiveItem(AActor* Activator)
{
	Super::ActiveItem(Activator);
	
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemStorage.generated.h"

UCLASS()
class ASSIGNMENT_API AItemStorage : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemStorage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditDefaultsOnly, Category = "SaveData")
	TMap<FString, TSubclassOf<class AWeapon>> WeaponMap;
	/*
		* Map의 작동방식
		[key] -> [value]

		key 값으로 항목을 값을 인덱싱 할 때 값을 얻을 수 있음.
		Array에서는 정수만 사용할 수 있지만, Map에서는 문자열도 사용할 수 있는 만큼 반드시 정수일 필요는 없음.
		Unreal에서는 TMap<> 으로 사용함.

		일반적인 C언어로 할 경우 WeaponMap.Add() 하여 Map에 저장하지만
		이번 코드의 경우 위와 같이 선언 후 블루프린트에서 직접 추가한다.
	*/

};

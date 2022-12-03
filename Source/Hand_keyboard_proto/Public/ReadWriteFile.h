// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ReadWriteFile.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct HAND_KEYBOARD_PROTO_API FDataRecordUnitCpp
{
	GENERATED_BODY()
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Letter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> LeftLocationList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> RightLocationList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LeftDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RightDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> TimeList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PreviousLetter;

	FDataRecordUnitCpp()
	{
		Letter = FString(TEXT(""));
		LeftDistance = 0.0;
		RightDistance = 0.0;
		PreviousLetter = FString(TEXT(""));
	}
};


UCLASS()
class HAND_KEYBOARD_PROTO_API UReadWriteFile : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Save"))
		static bool SaveArrayText(FString SaveDirectory, FString FileName, TArray<FString> SaveText, bool AllowOverWriting);

	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Read"))
		static bool ReadDataRecordFile(FString SaveDirectory, FString FileName, TArray<FDataRecordUnitCpp>& PastDataList);

	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "FileName"))
		static bool ReadAllFileNames(FString SaveDirectory, TArray<FString>& AllFileNames);
};



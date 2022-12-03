// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadWriteFile.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"

bool UReadWriteFile::SaveArrayText(FString SaveDirectory, FString FileName, TArray<FString> SaveText, bool AllowOverWriting = false)
{
	// Set file path
	SaveDirectory += "\\";
	SaveDirectory += FileName;

	if (!AllowOverWriting) {
		if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*SaveDirectory)) {
			return false;
		}
	}

	FString FinalString = "";
	for (FString& Each : SaveText) {
		FinalString += Each;
		FinalString += LINE_TERMINATOR;
	}

	return FFileHelper::SaveStringToFile(FinalString, *SaveDirectory);
}

bool UReadWriteFile::ReadDataRecordFile(FString SaveDirectory, FString FileName, TArray<FDataRecordUnitCpp>& PastDataList)
{
	// Set file path
	SaveDirectory += "\\";
	SaveDirectory += FileName;

	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*SaveDirectory)) {
		return false;
	}

	// Read every line into Texts
	TArray<FString> Texts;
	FFileHelper::LoadFileToStringArray(Texts, *SaveDirectory);

	// Split each line, and store them
	PastDataList.Add(FDataRecordUnitCpp()); // The first one
	for (int i = 1; i < Texts.Num(); i++) {
		TArray<FString> Words;
		TArray<FString> WordsPre;
		Texts[i].ParseIntoArray(Words, TEXT(","), false);
		if (i == 0) {
			PastDataList.Add(FDataRecordUnitCpp());
		}
		else {
			Texts[i - 1].ParseIntoArray(WordsPre, TEXT(","), false);
			if (Words[0] != WordsPre[0]) {
				// Means this is a new letter
				PastDataList.Add(FDataRecordUnitCpp());
			}
		}
		PastDataList[PastDataList.Num() - 1].Letter = Words[0];
		PastDataList[PastDataList.Num() - 1].LeftLocationList.Add(FVector(FCString::Atof(*Words[1]), FCString::Atof(*Words[2]), FCString::Atof(*Words[3])));
		PastDataList[PastDataList.Num() - 1].RightLocationList.Add(FVector(FCString::Atof(*Words[4]), FCString::Atof(*Words[5]), FCString::Atof(*Words[6])));
		PastDataList[PastDataList.Num() - 1].LeftDistance = FCString::Atof(*Words[7]);
		PastDataList[PastDataList.Num() - 1].RightDistance = FCString::Atof(*Words[8]);
		PastDataList[PastDataList.Num() - 1].TimeList.Add(FCString::Atof(*Words[9]));
		PastDataList[PastDataList.Num() - 1].PreviousLetter = Words[10];
	}

	return true;
}

bool UReadWriteFile::ReadAllFileNames(FString SaveDirectory, TArray<FString>& AllFileNames)
{
	// Set file path
	SaveDirectory += "\\myfilenames.csv";

	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*SaveDirectory)) {
		return false;
	}
	return FFileHelper::LoadFileToStringArray(AllFileNames, *SaveDirectory);
}
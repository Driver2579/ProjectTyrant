// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "MoverTypes.h"
#include "ProjectTyrantMoverInputs.generated.h"

// Data block containing extended mover inputs used by this project
USTRUCT()
struct PROJECTTYRANT_API FProjectTyrantMoverInputs : public FMoverDataStructBase
{
	GENERATED_USTRUCT_BODY()

    bool bRunPressed = false;

	/**
	 * This MUST be overridden by derived types.
	 * @return Newly allocated copy of this struct.
	 */
	virtual FMoverDataStructBase* Clone() const override
	{
		return new FProjectTyrantMoverInputs(*this);
	}

	/**
	 * This MUST be overridden by derived types.
	 * @return The StaticStruct of this struct.
	 */
	virtual UScriptStruct* GetScriptStruct() const override { return StaticStruct(); }

	virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override
	{
		Ar.SerializeBits(&bRunPressed, 1);

		return Super::NetSerialize(Ar, Map, bOutSuccess);
	}

	virtual void ToString(FAnsiStringBuilderBase& Out) const override
	{
		Super::ToString(Out);
		Out.Appendf("bIsRunPressed: %i\n", bRunPressed);
	}
};
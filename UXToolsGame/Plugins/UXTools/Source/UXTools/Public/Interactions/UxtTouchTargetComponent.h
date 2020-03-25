// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Interactions/UxtTouchTarget.h"

#include "UxtTouchTargetComponent.generated.h"

class UUxtTouchTargetComponent;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FBeginFocusDelegate, UUxtTouchTargetComponent*, Interactable, UUxtNearPointerComponent*, Pointer, FUxtPointerInteractionData, Data, bool, bWasFocused);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FUpdateFocusDelegate, UUxtTouchTargetComponent*, Interactable, UUxtNearPointerComponent*, Pointer, FUxtPointerInteractionData, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FEndFocusDelegate, UUxtTouchTargetComponent*, Interactable, UUxtNearPointerComponent*, Pointer, bool, bIsFocused);

/**
 * Base class for pointer targets that keeps track of the currently touching pointers.
 */
UCLASS(Blueprintable, ClassGroup = UXTools, meta = (BlueprintSpawnableComponent))
class UXTOOLS_API UUxtTouchTargetComponent : public USceneComponent, public IUxtTouchTarget
{
    GENERATED_BODY()

public:

	UUxtTouchTargetComponent();

protected:
	//
	// IUxtTouchTarget interface

	virtual void OnEnterTouchFocus_Implementation(UUxtNearPointerComponent* Pointer, const FUxtPointerInteractionData& Data) override;
	virtual void OnUpdateTouchFocus_Implementation(UUxtNearPointerComponent* Pointer, const FUxtPointerInteractionData& Data) override;
	virtual void OnExitTouchFocus_Implementation(UUxtNearPointerComponent* Pointer) override;

	virtual bool GetClosestTouchPoint_Implementation(const UPrimitiveComponent* Primitive, const FVector& Point, FVector& OutPointOnSurface) const override;

	/** Returns a list of the pointers that are currently touching this actor. */
	const TMap<UUxtNearPointerComponent*, FUxtPointerInteractionData>& GetFocusedPointers() const;

private:

	/** List of pointers that are currently touching the actor. */
	TMap<UUxtNearPointerComponent*, FUxtPointerInteractionData> FocusedPointers;

	/** Event raised when a pointer starts focusing the interactable. WasFocused indicates if the interactable was already focused by another pointer. */
	UPROPERTY(BlueprintAssignable, Category = "Interactable")
	FBeginFocusDelegate OnBeginFocus;

	/** Event raised when a focusing pointer updates. */
	UPROPERTY(BlueprintAssignable, Category = "Interactable")
	FUpdateFocusDelegate OnUpdateFocus;

	/** Event raised when a pointer ends focusing the interactable. IsFocused indicates if the interactable is still focused by another pointer. */
	UPROPERTY(BlueprintAssignable, Category = "Interactable")
	FEndFocusDelegate OnEndFocus;
};

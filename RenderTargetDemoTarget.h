

#pragma once

#include "GameFramework/Actor.h"
#include "Engine/Canvas.h"
#include "Engine/TextureRenderTarget2D.h"
#include "RenderTargetDemoTarget.generated.h"

/**
 * 
 */
UCLASS()
class RENDERTARGETDEMO_API ARenderTargetDemoTarget : public AActor
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION()
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = TargetDemo)
	virtual void DrawOnTarget(FVector2D Loc);

	UPROPERTY(BlueprintReadWrite, Category = Target)
	class UMaterialInstanceDynamic* MaterialInstance;

	UPROPERTY(BlueprintReadWrite, Category = Target)
	class UTexture2D* DrawTexture;

private:
	bool DoDraw;

	FVector2D DrawLoc;

	FCanvas* Canvas;

	UPROPERTY()
	class UTextureRenderTarget2D* RenderTarget;	
};

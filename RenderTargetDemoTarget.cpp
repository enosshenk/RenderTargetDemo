

#include "RenderTargetDemo.h"
#include "RenderTargetDemoTarget.h"
#include "Engine/TextureRenderTarget2D.h"
#include "RenderUtils.h"

ARenderTargetDemoTarget::ARenderTargetDemoTarget(const class FPostConstructInitializeProperties& PCIP)
: Super(PCIP), DoDraw(false), MaterialInstance(nullptr), RenderTarget(nullptr), DrawTexture(nullptr), DrawLoc(FVector2D(0, 0))
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ARenderTargetDemoTarget::BeginPlay()
{
	Super::BeginPlay();

	if (RenderTarget == nullptr)
	{
		RenderTarget = NewObject<UTextureRenderTarget2D>(this);
		RenderTarget->ClearColor = FLinearColor::Black;
		RenderTarget->InitAutoFormat(1024, 1024);
		RenderTarget->UpdateResourceImmediate();

		FTextureRenderTarget2DResource* TextureResource = (FTextureRenderTarget2DResource*)RenderTarget->Resource;
		Canvas = new FCanvas(TextureResource, NULL, 0, 0, 0);
		Canvas->Clear(FLinearColor::Black);

		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Setting up render target"));
	}

	if (MaterialInstance != nullptr)
	{
		MaterialInstance->SetTextureParameterValue(FName("Mask"), RenderTarget);

		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Setting up material instance"));
	}

}

void ARenderTargetDemoTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DoDraw)
	{
		FCanvasTileItem Box(DrawLoc, DrawTexture->Resource, FVector2D(32, 32), FLinearColor(1.0f, 1.0f, 1.0f));
		Canvas->DrawItem(Box);
		Canvas->Flush();

		DoDraw = false;
	}
}

void ARenderTargetDemoTarget::DrawOnTarget(FVector2D Loc)
{
	DrawLoc = FVector2D(Loc.X + 512, Loc.Y + 512);
	DoDraw = true;
}
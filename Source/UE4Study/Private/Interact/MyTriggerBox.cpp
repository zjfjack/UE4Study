// Fill out your copyright notice in the Description page of Project Settings.


#define print(text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, text)
#define printf(text, fstring) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, FString::Printf(TEXT(text), fstring))

#include "Interact/MyTriggerBox.h"
#include "DrawDebugHelpers.h"

AMyTriggerBox::AMyTriggerBox()
{
    OnActorBeginOverlap.AddDynamic(this, &AMyTriggerBox::OnOverlapBegin);
    OnActorEndOverlap.AddDynamic(this, &AMyTriggerBox::OnOverlapEnd);
}

void AMyTriggerBox::BeginPlay()
{
    Super::BeginPlay();

    DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Red, true, -1, 0, 5);
}

void AMyTriggerBox::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
    if (OtherActor && OtherActor != this)
    {
        print("Overlap Begin");
        printf("Overlapped Actor = %s", *OverlappedActor->GetName());
    }
        
}

void AMyTriggerBox::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
    if (OtherActor && OtherActor != this)
    {
        print("Overlap Ended");
        printf("Overlapped Actor = %s", *OtherActor->GetName());
    }
}

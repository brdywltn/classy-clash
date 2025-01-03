#include "BaseCharacter.h"


BaseCharacter::BaseCharacter()
{

}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        screenPos.x,
        screenPos.y,
        width * scale,
        height * scale,
    };
}

void BaseCharacter::tick(float deltaTime) 
{
    worldPosLastFrame = worldPos;

    // Update animation frame
    runningTime += deltaTime;

    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0.f;
    }

    // Draw the character
    Rectangle sourceRect{frame * width, 0.f, rightLeft * width, height};
    Rectangle destRect{screenPos.x, screenPos.y, scale * width, scale * height};
    DrawTexturePro(texture, sourceRect, destRect, Vector2{}, 0.f, WHITE);
}
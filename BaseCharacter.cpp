#include "BaseCharacter.h"
#include "raymath.h"

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
        getScreenPos().x,
        getScreenPos().y,
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

    if (Vector2Length(velocity) != 0.0)
    {
        // Set worldPos = worldPos - direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        // Change direction
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }

    velocity = {};

    // Draw the character
    Rectangle sourceRect{frame * width, 0.f, rightLeft * width, height};
    Rectangle destRect{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
    DrawTexturePro(texture, sourceRect, destRect, Vector2{}, 0.f, WHITE);
}
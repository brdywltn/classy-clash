#include "Character.h"
#include "raymath.h"

Character::Character(int windowWidth, int windowHeight)
{
    width = texture.width / maxFrames;
    height = texture.height;

    screenPos = {
        (float)windowWidth / 2.0f - scale * (0.5f * width), // X pos
        (float)windowHeight / 2.0f - scale * (0.5f * height)       // Y pos
    };
}


void Character::undoMovement()
{
    worldPos = worldPosLastFrame;
}

void Character::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    Vector2 direction{};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;

    if (Vector2Length(direction) != 0.0)
    {
        // Set worldPos = worldPos - direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        // Change direction
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }

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
#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    width = texture.width / maxFrames;
    height = texture.height;
    speed = 3.5f;
}

void Enemy::tick(float deltaTime)
{
    // Get toTarget vector
    Vector2 toTarget = Vector2Subtract(current_target->getScreenPos(), screenPos);
    // Normalise the vector
    toTarget = Vector2Normalize(toTarget);
    // multiply it by speed
    toTarget = Vector2Scale(toTarget, speed);
    // move the enemy (set worldPos)
    worldPos = Vector2Add(worldPos, toTarget);

    screenPos = Vector2Subtract(worldPos, current_target->getWorldPos());

    BaseCharacter::tick(deltaTime);


}

void Enemy::setTarget(Character* target)
{
    current_target = target;
}
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

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, current_target->getWorldPos());
}

void Enemy::tick(float deltaTime)
{
    velocity = Vector2Subtract(current_target->getScreenPos(), getScreenPos());

    //BaseCharacter::tick(deltaTime);
}

void Enemy::setTarget(Character* target)
{
    current_target = target;
}
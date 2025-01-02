#include "raylib.h"
#include "raymath.h"

class Character
{
public:
    Vector2 getWorldPos() { return worldPos; }
    void setScreenPos(int windowWidth, int windowHeight);
    void tick(float deltaTime);

private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPos;
    Vector2 worldPos;
    // 1: facing right, -1: facing left
    float rightLeft{1.f};
    // Animation variables for knight
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f / 12.f};
    const float speed{4.f};
};

void Character::setScreenPos(int windowWidth, int windowHeight)
{
    screenPos = {
        (float)windowWidth / 2.0f - 4.0f * (0.5f * (float)texture.width / 6.0f), // X pos
        (float)windowHeight / 2.0f - 4.0f * (0.5f * (float)texture.height)       // Y pos
    };
}

void Character::tick(float deltaTime)
{
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
}

int main()
{
    // Set the window variables
    const int windowDimensions[]{384, 384};
    const char windowTitle[]{"Classy Clash"};

    // Init window
    InitWindow(windowDimensions[0], windowDimensions[1], windowTitle);

    // Load the background image
    Texture2D background = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 background_pos{0.0, 0.0};

    float speed{4.0};

    Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");
    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2 knightPos{
        (float)windowDimensions[0] / 2.0f - 4.0f * (0.5f * (float)knight.width / 6.0f), // X pos
        (float)windowDimensions[1] / 2.0f - 4.0f * (0.5f * (float)knight.height)        // Y pos
    };

    // 1: facing right, -1: facing left
    float rightLeft{1.f};
    // Animation variables for knight
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f / 12.f};

    // Game logic loop
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Game logic

        // Begin drawing and set the background
        BeginDrawing();
        ClearBackground(WHITE);

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
            // Set background_pos = background_pos - direction
            background_pos = Vector2Subtract(background_pos, Vector2Scale(Vector2Normalize(direction), speed));
            // Change direction
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
            knight = knight_run;
        }
        else
        {
            knight = knight_idle;
        }

        // Draw the map
        DrawTextureEx(background, background_pos, 0, 4.0, WHITE);

        // Update animation frame
        runningTime += GetFrameTime();

        if (runningTime >= updateTime)
        {
            frame++;
            runningTime = 0.f;
            if (frame > maxFrames)
                frame = 0.f;
        }

        // Draw the character
        Rectangle sourceRect{frame * (float)knight.width / 6.f, 0.f, rightLeft * (float)knight.width / 6.f, (float)knight.height};
        Rectangle destRect{knightPos.x, knightPos.y, 4.0f * (float)knight.width / 6.0f, 4.0f * (float)knight.height};
        Vector2 origin{};

        DrawTexturePro(knight, sourceRect, destRect, origin, 0.f, WHITE);

        EndDrawing();
    }

    UnloadTexture(background);
    CloseWindow();
};
#include "raylib.h"
#include "raymath.h"

int main() 
{
    // Set the window variables
    const int windowDimensions[] { 384, 384 };
    const char windowTitle[] { "Classy Clash" };

    // Init window
    InitWindow(windowDimensions[0], windowDimensions[1], windowTitle);

    // Load the background image
    Texture2D background = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 background_pos { 0.0, 0.0 };

    float speed { 4.0 };

    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2 knightPos 
    { 
        (float)windowDimensions[0] / 2.0f - 4.0f * (0.5f * (float)knight.width / 6.0f),   // X pos
        (float)windowDimensions[1] / 2.0f - 4.0f * (0.5f * (float)knight.height)         // Y pos
    };

    // Game logic loop
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Game logic

        // Begin drawing and set the background
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction {};
        if (IsKeyDown(KEY_A)) direction.x -= 1.0;
        if (IsKeyDown(KEY_D)) direction.x += 1.0;
        if (IsKeyDown(KEY_W)) direction.y -= 1.0;
        if (IsKeyDown(KEY_S)) direction.y += 1.0;
        
        if (Vector2Length(direction) != 0.0)
        {
            // Set background_pos = background_pos - direction
            background_pos = Vector2Subtract(background_pos, Vector2Scale(Vector2Normalize(direction), speed));
            
        } 

        // Draw the map
        DrawTextureEx(background, background_pos, 0, 4.0, WHITE);

        // Draw the character
        Rectangle sourceRect {0.f, 0.f, (float)knight.width / 6.f, (float)knight.height };
        Rectangle destRect { knightPos.x, knightPos.y, 4.0f * (float)knight.width / 6.0f, 4.0f * (float)knight.height };
        Vector2 origin {};

        DrawTexturePro(knight, sourceRect, destRect, origin, 0.f, WHITE);





        EndDrawing();
    }

    UnloadTexture(background);
    CloseWindow();

};
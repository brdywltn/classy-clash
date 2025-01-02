#include "raylib.h"
#include "raymath.h"
#include "Character.h"

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
    const float mapScale {4.0f};


    Character knight;
    knight.setScreenPos(windowDimensions[0], windowDimensions[1]);

    // Game logic loop
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Begin drawing and set the background
        BeginDrawing();
        ClearBackground(WHITE);


        background_pos = Vector2Scale(knight.getWorldPos(), -1.f);
        // Draw the map
        DrawTextureEx(background, background_pos, 0, mapScale, WHITE);
        knight.tick(GetFrameTime());

        // Check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowDimensions[0] > background.width * mapScale ||
            knight.getWorldPos().y + windowDimensions[1] > background.height * mapScale)
        {
            knight.undoMovement();
        } 

        EndDrawing();
    }

    UnloadTexture(background);
    CloseWindow();
};
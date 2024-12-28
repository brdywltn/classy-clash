#include "raylib.h"

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

    // Game logic loop
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Game logic

        // Begin drawing and set the background
        BeginDrawing();
        ClearBackground(WHITE);

        DrawTextureEx(background, background_pos, 0, 4.0, WHITE);




        EndDrawing();
    }

    UnloadTexture(background);
    CloseWindow();

};
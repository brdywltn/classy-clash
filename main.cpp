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

        DrawTextureEx(background, background_pos, 0, 4.0, WHITE);




        EndDrawing();
    }

    UnloadTexture(background);
    CloseWindow();

};
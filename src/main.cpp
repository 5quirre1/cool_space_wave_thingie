#include "raylib.h"
#include <string>

int main()
{
    // window
    const int screenWidth = 800;  // width
    const int screenHeight = 450; // height

    InitWindow(screenWidth, screenHeight, "amazing"); // make window

    Texture2D texture = LoadTexture("resources/space.png"); // load texture

    // load shader file
    std::string shaderPath = "resources/shaders/glsl330/wave.fs";
    Shader shader = LoadShader(nullptr, shaderPath.c_str());

    // get shader variable locations
    int secondsLoc = GetShaderLocation(shader, "seconds");
    int freqXLoc = GetShaderLocation(shader, "freqX");
    int freqYLoc = GetShaderLocation(shader, "freqY");
    int ampXLoc = GetShaderLocation(shader, "ampX");
    int ampYLoc = GetShaderLocation(shader, "ampY");
    int speedXLoc = GetShaderLocation(shader, "speedX");
    int speedYLoc = GetShaderLocation(shader, "speedY");

    // values for shader
    float freqX = 25.0f;
    float freqY = 25.0f;
    float ampX = 5.0f;
    float ampY = 5.0f;
    float speedX = 8.0f;
    float speedY = 8.0f;

    // set initial shader values
    float screenSize[2] = {(float)GetScreenWidth(), (float)GetScreenHeight()};
    SetShaderValue(shader, GetShaderLocation(shader, "size"), screenSize, SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, freqXLoc, &freqX, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, freqYLoc, &freqY, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, ampXLoc, &ampX, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, ampYLoc, &ampY, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, speedXLoc, &speedX, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, speedYLoc, &speedY, SHADER_UNIFORM_FLOAT);

    float seconds = 0.0f; // timer

    SetTargetFPS(60); // set fps

    // game loop
    while (!WindowShouldClose())
    {
        // update shader timer
        seconds += GetFrameTime();
        SetShaderValue(shader, secondsLoc, &seconds, SHADER_UNIFORM_FLOAT);

        // draw
        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginShaderMode(shader);
                DrawTexture(texture, 0, 0, WHITE);
                DrawTexture(texture, texture.width, 0, WHITE);
            EndShaderMode();

        EndDrawing();
    }

    // cleanup
    UnloadShader(shader);
    UnloadTexture(texture);
    CloseWindow(); // close window

    return 0;
}

/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"
#include "Pathfinding.h"
#include "NodeMap.h"

#include <string>

using namespace AIForGames;

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------


    Node* a = new Node();
    a->position = glm::vec2(125.0f, 75.0f);
    Node* b = new Node();
    b->position = glm::vec2(250.0f, 75.0f);


    //create a ASCII map
    std::vector<std::string> asciiMap;
    asciiMap.push_back("000000000000");
    asciiMap.push_back("010111011100");
    asciiMap.push_back("010101110110");
    asciiMap.push_back("010100000000");
    asciiMap.push_back("010111111110");
    asciiMap.push_back("010000001000");
    asciiMap.push_back("011111111110");
    asciiMap.push_back("000000000000");

    NodeMap nodeMap;    

    nodeMap.Initialise(asciiMap, 50);

    Node* start = nodeMap.GetNode(1, 1);
    Node* end = nodeMap.GetNode(10, 2);

    std::vector<Node*> nodeMapPath = DijkstrasSearch(start, end);
    Color lineColor = { 255, 255, 255, 255 };


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        //restet the start position based on the left click of the mouse
        if (IsMouseButtonPressed(0))
        {
            Vector2 mousePos = GetMousePosition();
            start = nodeMap.GetClosestNode(glm::vec2(mousePos.x, mousePos.y));
            nodeMapPath = DijkstrasSearch(start, end);
        }
        //reset the end position based on theright click of the mouse
        if (IsMouseButtonPressed(1))
        {
            Vector2 mousePos = GetMousePosition();
            end = nodeMap.GetClosestNode(glm::vec2(mousePos.x, mousePos.y));
            nodeMapPath = DijkstrasSearch(start, end);
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();       
        

        ClearBackground(DARKGRAY);

        nodeMap.Draw();
        nodeMap.DrawPath(nodeMapPath);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
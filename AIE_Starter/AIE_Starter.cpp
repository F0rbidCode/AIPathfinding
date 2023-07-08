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
#include "PathAgent.h"

#include <string>

using namespace AIForGames;

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    float time = (float)GetTime();
    float deltaTime;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    //create a ASCII map
    std::vector<std::string> asciiMap;
    asciiMap.push_back("0000000000000000000000000");
    asciiMap.push_back("0101110111000000011110000");
    asciiMap.push_back("0101011101100000010010000");
    asciiMap.push_back("0101000000000000010011100");
    asciiMap.push_back("0101111111100000010000100");
    asciiMap.push_back("0100000010000000110000110");
    asciiMap.push_back("0111111111111111111111010");
    asciiMap.push_back("0000000000000000000011110");
    asciiMap.push_back("0000000010000111100010100");
    asciiMap.push_back("0000000011110100111110100");
    asciiMap.push_back("0000000000010110000010100");
    asciiMap.push_back("0000000000010010000010100");
    asciiMap.push_back("0000000000011110000010110");
    asciiMap.push_back("0000000000000000000011110");
    

    NodeMap nodeMap;    

    nodeMap.Initialise(asciiMap, 32);

    Node* start = nodeMap.GetNode(1, 1);
    Node* end = nodeMap.GetNode(10, 2);

    

    std::vector<Node*> nodeMapPath = DijkstrasSearch(start, end);
    Color lineColor = { 255, 255, 255, 255 };

    //initialise our path agent
    PathAgent agent;
    agent.setNode(start);
    agent.setSpeed(64);

    //initialize the player
    PathAgent player;
    player.setNode(end);
    player.setSpeed(50);

    glm::vec2 playerPos;
    glm::vec2 playerTarget = player.GetPosition();
    glm::vec2 agentPos;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //calculate delta time
        float fTime = (float)GetTime();
        deltaTime = fTime - time;
        time = fTime;


        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        //restet the start position based on the left click of the mouse
        if (IsMouseButtonPressed(0))
        {
            //start = agent.GetCurrentNode();
           // end = agent.GetTarget();

            Vector2 mousePos = GetMousePosition();
            if (nodeMap.GetClosestNode(glm::vec2(mousePos.x, mousePos.y)) == player.GetCurrentNode())
            {
            
            }
            else if (nodeMap.GetClosestNode(glm::vec2(mousePos.x, mousePos.y)) == agent.GetCurrentNode())
            {
            }
            else
            {
                nodeMap.ToggleClosestNode(glm::vec2(mousePos.x, mousePos.y), asciiMap);
                nodeMap.Initialise(asciiMap, 32);


                player.setNode(nodeMap.GetClosestNode(playerPos));
                agent.setNode(nodeMap.GetClosestNode(agentPos));

                agent.setTarget(player.GetCurrentNode());
                player.setTarget(nodeMap.GetClosestNode(playerTarget));


                //agent.setNode(start);
                //agent.setTarget(end);

                //start = nodeMap.GetClosestNode(agent.GetPosition());
                //end = nodeMap.GetNode(12, 12);

                ///nodeMapPath = DijkstrasSearch(start, end);
            }
        }
        //reset the end position based on theright click of the mouse
        if (IsMouseButtonPressed(1))
        {
            Vector2 mousePos = GetMousePosition();
           // end = nodeMap.GetClosestNode(glm::vec2(mousePos.x, mousePos.y));

            playerTarget = glm::vec2(mousePos.x, mousePos.y);
            player.setTarget(nodeMap.GetClosestNode(playerTarget));
           
            //nodeMapPath = DijkstrasSearch(start, end);
            //start = agent.GetCurrentNode();
            //agent.setTarget(end);
        }


        //update position
        /*start = nodeMap.GetClosestNode(agent.GetPosition());
        end = nodeMap.GetClosestNode(player.GetPosition());
        playerPos = nodeMap.GetClosestNode(player.GetPosition());
        nodeMapPath = DijkstrasSearch(start, playerPos);*/
        agent.setTarget(player.GetCurrentNode());

        playerPos = player.GetPosition();
        agentPos = agent.GetPosition();



        agent.Update(deltaTime);
        agent.Draw(YELLOW);

       // nodeMapPath = DijkstrasSearch(playerPos, end);

        player.Update(deltaTime);
        player.Draw(GREEN);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();       
        

        ClearBackground(DARKGRAY);

        nodeMap.Draw();
        nodeMap.DrawPath(agent.m_path);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
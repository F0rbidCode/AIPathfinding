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
#include "Agent.h"
#include "GoToPointBehaviour.h"
#include "WanderBehaviour.h"
#include "FollowBehaviour.h"
#include "SelectorBehaviour.h"
#include "DistanceCondition.h"
#include "State.h"
#include "FiniteStateMechine.h"
#include "UtilityAI.h"

#include <string>



using namespace AIForGames;

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    bool Game = true;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    float time = (float)GetTime();
    float deltaTime;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------


   /* Node* a = new Node();
    a->position = glm::vec2(125.0f, 75.0f);
    Node* b = new Node();
    b->position = glm::vec2(250.0f, 75.0f);*/


    //create a ASCII map
    std::vector<std::string> asciiMap;
    asciiMap.push_back("0000000000000000000000000");
    asciiMap.push_back("0101110111000000011110000");
    asciiMap.push_back("0001011101100000010010000");
    asciiMap.push_back("0101000000000000010011100");
    asciiMap.push_back("0101111111100000010000100");
    asciiMap.push_back("0100000010000000110000110");
    asciiMap.push_back("0111111111101111111111010");
    asciiMap.push_back("0000000000000000000011110");
    asciiMap.push_back("0000000010000111100010100");
    asciiMap.push_back("0000000011110100111110100");
    asciiMap.push_back("0000000000010110000010100");
    asciiMap.push_back("0000000000010010000010100");
    asciiMap.push_back("0000000000011110000010110");
    asciiMap.push_back("0000000000000000000011112");
    

    NodeMap nodeMap;   
    const int CELL_SIZE = 32; //used to contolre the size of each node

    nodeMap.Initialise(asciiMap, CELL_SIZE);

    Node* start = nodeMap.GetNode(1, 1);
    Node* end = nodeMap.GetNode(10, 2);

    /*std::vector<Node*> nodeMapPath = DijkstrasSearch(start, end);
    Color lineColor = { 255, 255, 255, 255 };*/

    //initialise our path agent
    /*PathAgent agent;    
    agent.setNode(start);
    agent.setSpeed(64);*/

    //set up a FSM, we're going to have two states with their own conditions
    DistanceCondition* closerThan5 = new DistanceCondition(5.0f * nodeMap.GetCellSize(), true);
    DistanceCondition* furtherThan7 = new DistanceCondition(7.0f * nodeMap.GetCellSize(), false);

    //register these states with the FSM, so its responsible for deleting them now
    State* wanderState = new State(new WanderBehaviour());
    State* followState = new State(new FollowBehaviour());
    wanderState->AddTransition(closerThan5, followState);
    followState->AddTransition(furtherThan7, wanderState);

    //make a finite state machine that starts off wandering
    FiniteStateMechine* fsm = new FiniteStateMechine(wanderState);
    fsm->AddState(wanderState);
    fsm->AddState(followState);

    //initialise the UtilityAI
    UtilityAI* utilityAI = new UtilityAI();
    utilityAI->AddBehaviour(new WanderBehaviour());
    utilityAI->AddBehaviour(new FollowBehaviour());



    //initialise agent
    Agent agent(&nodeMap, new GoToPointBehaviour());    
    agent.setNode(start);

    Agent agent2(&nodeMap, fsm);
    agent2.setNode(nodeMap.GetRandomNode());
    agent2.setTarget(&agent);

    Agent agent3(&nodeMap, utilityAI);
    agent3.setNode(nodeMap.GetRandomNode());
    agent3.setSpeed(32);
    agent3.setTarget(&agent);


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
        ////////////////////////////////////////////////// 
        //left click is handled by the GoToPoint Behaviour
        //////////////////////////////////////////////////
        
        //use the right click to put up and take down walls
        if (IsMouseButtonPressed(1))
        {
            //check that you are not trying to put a wall up where an agent currently is
            glm::vec2 mousePos = glm::vec2(GetMousePosition().x, GetMousePosition().y);
            if (nodeMap.GetClosestNode(mousePos) == nodeMap.GetClosestNode(agent.GetPosition()) || nodeMap.GetClosestNode(mousePos) == nodeMap.GetClosestNode(agent2.GetPosition()) ||nodeMap.GetClosestNode(mousePos) == nodeMap.GetClosestNode(agent3.GetPosition()))
            {
               
            }
            else
            {
                //get mouse position and call toggle node
                nodeMap.ToggleClosesNode(mousePos, asciiMap);

                //delete current node map
                nodeMap.~NodeMap();

                //call initialise on the node map with the modified ascii map
                nodeMap.Initialise(asciiMap, CELL_SIZE);

                //set agents nodemap updated flag to true
                agent.nodeMapUpdate = true;
                agent2.nodeMapUpdate = true;
                agent3.nodeMapUpdate = true;

                ////update all agents current node
                //agent.UpdateNode(nodeMap.GetClosestNode(agent.GetPosition()));
                //agent2.UpdateNode(nodeMap.GetClosestNode(agent2.GetPosition()));
                //agent3.UpdateNode(nodeMap.GetClosestNode(agent3.GetPosition()));

                ////recalculate all agent paths
                //agent.GoTo(agent.GetTargetPos());
                //agent2.GoTo(agent2.GetTargetPos());
                //agent3.GoTo(agent3.GetTargetPos());
            }

        }

       

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();       
        

        ClearBackground(DARKGRAY);

        //draw node map
        nodeMap.Draw();


        //update and draw agents
        agent.Update(deltaTime);
        agent.Draw();

        agent2.Update(deltaTime);
        agent2.Draw();

        agent3.Update(deltaTime);
        agent3.Draw();



        //check for win condition
        if (agent.GetCurrentNode())
        {
            if (agent.GetCurrentNode()->isEnd)
            {
                //cout << "You Win!" << endl;
                Game = false;

                while (!Game)
                {
                    BeginDrawing();
                    ClearBackground(DARKGRAY);

                    //cout << "you win" << endl;

                    DrawText("You Win!", (GetScreenWidth() / 2) - (MeasureText("You Win!", 50) / 2), GetScreenHeight() / 2, 50, WHITE);
                    EndDrawing();

                    if (IsKeyPressed(KEY_ESCAPE))
                    {
                        Game = true;
                    }
                }
            }
        }

        //cleck for loose conditions
        if (agent.GetCurrentNode() && agent2.GetCurrentNode() && agent3.GetCurrentNode())
        {
            if (agent.GetCurrentNode() == agent2.GetCurrentNode() || agent.GetCurrentNode() == agent3.GetCurrentNode())
            {
                Game = false;

                while (!Game)
                {
                    BeginDrawing();
                    ClearBackground(DARKGRAY);

                    //cout << "you win" << endl;

                    DrawText("You Loose!", (GetScreenWidth() / 2) - (MeasureText("You Win!", 50) / 2), GetScreenHeight() / 2, 50, WHITE);
                    EndDrawing();

                    if (IsKeyPressed(KEY_ESCAPE))
                    {
                        Game = true;
                    }
                }

            }
        }


       

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    
    //clean up

    /*delete fsm;
    fsm = nullptr;

    delete utilityAI;
    utilityAI = nullptr;*/

    return 0;
}
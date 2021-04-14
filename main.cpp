#include <raylib.h>
#include <cmath>
#include "cell.h"
#include <string>


bool simulating = false;
const int screenWidth = 700;
const int screenHeight = 700;
const int cellSize = 14;
const unsigned int gridWidth = screenWidth / cellSize;
const unsigned int gridHeight = screenHeight / cellSize;
cell grid[gridWidth][gridHeight];
int simSpeed = 60;

Vector2 mousePos;
Rectangle cursorBlock;

bool updateble = true;
double lastUpdate = 0;
double updateInterval = 0.2;
double timeupdatestep = 0.02;

void clearBoard();


int main() {


    clearBoard();

    cursorBlock.width = cellSize;
    cursorBlock.height = cellSize;

    char *status = (char *) "Simulation not running";
    char *simSpeed = (char *) "Simulation speed: %x (Use UP/DOWN arrows)";

    InitWindow(screenWidth, screenHeight, "Cellular automata - Game of Life");


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    cell tempGrid[gridWidth][gridHeight];

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        // Checking for update eligibility
        if (GetTime() - lastUpdate >= updateInterval) {
            updateble = true;
            lastUpdate = GetTime();
        }

        // Mouse information
        mousePos = GetMousePosition();
        mousePos.x = floor(mousePos.x);
        mousePos.y = floor(mousePos.y);

        // Simulation control
        simulating = IsKeyPressed(KEY_ENTER) ^ simulating; // Flips the simulating value when Enter is true
        status = (simulating) ? (char *) "Simulation running" : (char *) "Simulation not running";

        if (!simulating) {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                grid[(int) mousePos.x / cellSize][(int) mousePos.y / cellSize].setState(1);
            }
            if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
                grid[(int) mousePos.x / cellSize][(int) mousePos.y / cellSize].setState(0);
            }
        }

        if (IsKeyPressed(KEY_C)) {
            clearBoard();
            simulating = false;
        }

        if (IsKeyPressed(KEY_UP)) {
            updateInterval -= timeupdatestep;
            if (updateInterval < 0.01) {
                updateInterval = 0.01;
            }
        }

        if (IsKeyPressed(KEY_DOWN)) {
            updateInterval += timeupdatestep;
            if (updateInterval > 1.0) {
                updateInterval = 1.0;
            }
        }


        if (simulating && updateble) {
            updateble = false;

            std::copy(&grid[0][0], &grid[gridWidth][gridHeight], &tempGrid[0][0]);

            for (int x = 0; x < gridWidth; ++x) {
                for (int y = 0; y < gridHeight; ++y) {
                    char liveCells = 0;
                    int t = (y == 0) ? gridHeight - 1 : y - 1;
                    int b = (y == gridHeight - 1) ? 0 : y + 1;
                    int l = (x == 0) ? gridWidth - 1 : x - 1;
                    int r = (x == gridWidth - 1) ? 0 : x + 1;

                    // Calculating live neighboring cells
                    if (grid[l][t].state) { liveCells++; }
                    if (grid[x][t].state) { liveCells++; }
                    if (grid[r][t].state) { liveCells++; }
                    if (grid[l][y].state) { liveCells++; }
                    if (grid[r][y].state) { liveCells++; }
                    if (grid[l][b].state) { liveCells++; }
                    if (grid[x][b].state) { liveCells++; }
                    if (grid[r][b].state) { liveCells++; }


                    if (grid[x][y].state == 0 && liveCells == 3) {
                        tempGrid[x][y].setState(1);
                    } else if (grid[x][y].state == 1 && (liveCells > 3 || liveCells < 2)) {
                        tempGrid[x][y].setState(0);
                    }

                }
            }

            std::copy(&tempGrid[0][0], &tempGrid[gridWidth][gridHeight], &grid[0][0]);
        }


        BeginDrawing();

        ClearBackground(RAYWHITE);

        for (int x = 0; x < gridWidth; ++x) {
            for (int y = 0; y < gridHeight; ++y) {
                if (grid[x][y].state && grid[x][y].state != 2) {
                    grid[x][y].setState(1);
                    DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, DARKGRAY);
                } else { grid[x][y].setState(0); }
            }
        }


        DrawText(status, 0, 0, 10, RED);
        DrawText(simSpeed, 0, 12, 10, RED);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void clearBoard() {
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            grid[x][y] = cell(x, y, 0);
        }
    }
}
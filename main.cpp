#include <iostream>
#include <conio.h>
#include <windows.h>

// Game settings
const int screenWidth = 100;
const int screenHeight = 125;
const int birdPosX = 10;
const int birdSize = 1;
const int gravity = 1;

// Bird variables
int birdPosY;
int birdVelocity;

// Obstacle variables
int obstaclePosX;
int obstacleGap;
int obstacleWidth;
int obstaclePosY;

// Game state variables
int score;
bool gameOver;

// Function to draw the game screen
void Draw()
{
    system("cls"); // Clear the console screen

    // Draw bird
    for (int y = 0; y < birdSize; ++y)
    {
        for (int x = 0; x < birdSize; ++x)
        {
            std::cout << "@";
        }
        std::cout << std::endl;
    }

    // Draw obstacles
    for (int y = 0; y < screenHeight; ++y)
    {
        if (y < obstaclePosY || y >= obstaclePosY + obstacleGap)
        {
            for (int x = 0; x < obstacleWidth; ++x)
            {
                std::cout << "#";
            }
            std::cout << std::endl;
        }
        else
        {
            for (int x = 0; x < obstacleWidth; ++x)
            {
                std::cout << " ";
            }
            std::cout << std::endl;
        }
    }

    // Draw score
    std::cout << "Score: " << score << std::endl;

    // Draw game over message
    if (gameOver)
    {
        std::cout << "Game Over!" << std::endl;
    }
}

// Function to handle user input
void Input()
{
    if (_kbhit())
    {
        char key = _getch();
        if (key == ' ')
        {
            birdVelocity = -2;
        }
    }
}

// Function to update game state
void Update()
{
    // Update bird position
    birdPosY += birdVelocity;
    birdVelocity += gravity;

    // Update obstacle position
    obstaclePosX--;

    // Check for collision with obstacles
    if (birdPosY < 0 || birdPosY >= screenHeight || (birdPosX >= obstaclePosX && birdPosX < obstaclePosX + obstacleWidth && (birdPosY <= obstaclePosY || birdPosY >= obstaclePosY + obstacleGap)))
    {
        gameOver = true;
    }

    // Check if bird has passed the obstacle
    if (birdPosX == obstaclePosX + obstacleWidth)
    {
        score++;
    }

    // Check if obstacle has gone off the screen
    if (obstaclePosX + obstacleWidth < 0)
    {
        obstaclePosX = screenWidth;
        obstaclePosY = rand() % (screenHeight - obstacleGap);
    }
}

// Function to initialize game variables
void Initialize()
{
    birdPosY = screenHeight / 2;
    birdVelocity = 0;
    obstaclePosX = screenWidth;
    obstaclePosY = screenHeight / 2;
    obstacleGap = 4;
    obstacleWidth = 5;
    score = 0;
    gameOver = false;
}

int main()
{
    Initialize();

    while (!gameOver)
    {
        Draw();
        Input();
        Update();
        Sleep(100); // Delay for smoother animation
    }

    Draw();

    return 0;
}

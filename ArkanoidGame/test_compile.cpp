#include "Platform.h"
#include "Ball.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStateMainMenu.h"

int main()
{
    // Test if our classes can be instantiated
    ArkanoidGame::Platform platform(100, 500, 100, 20, 300);
    ArkanoidGame::Ball ball(400, 300, 10, 400);
    
    return 0;
}

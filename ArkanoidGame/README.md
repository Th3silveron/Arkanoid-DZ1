# Arkanoid Game

A C++ implementation of the classic Arkanoid game using SFML library.

## Game Features

- **Platform Control**: Move the platform left and right using arrow keys
- **Ball Physics**: Ball bounces off walls, platform, and blocks with realistic physics
- **Destructible Blocks**: 24 colorful blocks arranged in 3 rows that can be destroyed
- **Game States**: Main menu, playing, game over, win screen, records, and exit dialog
- **Score System**: Earn points by destroying blocks (higher rows give more points)
- **Lives System**: Multiple lives with ball reset mechanics
- **Win Condition**: Destroy all blocks to win the game
- **Interactive Menus**: Navigate with arrow keys and select with Enter

## Controls

### In Game:
- **LEFT/RIGHT Arrow Keys**: Move platform
- **SPACE**: Launch ball
- **ESC**: Return to main menu

### In Menus:
- **UP/DOWN Arrow Keys**: Navigate menu options
- **ENTER or SPACE**: Select option
- **ESC**: Exit/back

## Building and Running

### Prerequisites
- Visual Studio 2019 or later
- SFML 2.5.1 or later

### Build Instructions
1. Open `ArkanoidGame.vcxproj` in Visual Studio
2. Select x64 platform and Debug configuration
3. Build the solution (Ctrl+Shift+B)
4. Run the game (F5)

### Project Structure
- **Core Classes**: `Platform`, `Ball`, `Block`, `Game`
- **Base Classes**: `GameObject` (base class for game objects)
- **Game States**: `GameStatePlaying`, `GameStateMainMenu`, `GameStateWin`, etc.
- **Resources**: Fonts, sounds, and textures in `Resources/` folder

## Technical Details

- **Architecture**: Object-oriented design with RAII principles
- **State Management**: Polymorphic game state system
- **Graphics**: SFML-based rendering
- **Physics**: Basic collision detection and ball movement
- **Memory Management**: Smart pointers and RAII for resource management

## Game Mechanics

The ball bounces off the platform, screen walls, and blocks. The platform can only move horizontally at the bottom of the screen. The game features 24 destructible blocks arranged in 3 rows with different colors and point values. Higher rows give more points when destroyed. The game tracks score and lives, with the ball resetting to the platform when a life is lost. The player wins by destroying all blocks.

## Notes

- The game uses placeholder sounds and textures
- High scores are currently hardcoded for demonstration
- The game window is 800x600 pixels

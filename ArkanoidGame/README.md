# Arkanoid Game

This is a C++ Arkanoid game built with SFML, transformed from a Snake game.

## Game Features

- **Platform Control**: Use left and right arrow keys to move the platform
- **Ball Physics**: The ball bounces off walls and the platform
- **Game Mechanics**: 
  - Press Space to launch the ball
  - You have 3 lives
  - The ball follows the platform when not launched
  - Game over when you lose all lives

## Controls

- **Arrow Keys**: Move platform left/right
- **Space**: Launch ball
- **Enter**: Start game (from main menu)
- **Escape**: Exit game

## Technical Implementation

### Classes Created

1. **Platform Class** (`Platform.h/cpp`)
   - Encapsulated rectangle shape
   - Movement controlled by arrow keys
   - Collision detection
   - Bounds checking

2. **Ball Class** (`Ball.h/cpp`)
   - Physics-based movement
   - Wall collision detection
   - Platform collision with bounce physics
   - Launch mechanism

3. **GameState Classes**
   - Converted from structs to classes with RAII
   - `GameStatePlaying`: Main game logic
   - `GameStateGameOver`: Game over screen
   - `GameStateMainMenu`: Main menu

### Design Patterns Implemented

1. **Encapsulation**: All data is private, accessed through public methods
2. **RAII**: Memory management handled automatically in constructors/destructors
3. **Inheritance**: Game states inherit from `GameStateBase`
4. **Polymorphism**: Virtual functions for game state interface

## File Structure

```
ArkanoidGame/
├── Platform.h/cpp          # Platform class
├── Ball.h/cpp              # Ball class
├── GameStatePlaying.h/cpp  # Main game state
├── GameStateGameOver.h/cpp # Game over state
├── GameStateMainMenu.h/cpp # Main menu state
├── Game.h/cpp              # Game management
├── Application.h/cpp       # Application wrapper
├── GameSettings.h          # Game constants
├── Text.h/cpp              # Text utilities
├── Vector.h                # Vector utilities
└── GameMain.cpp            # Entry point
```

## Building

This project is designed for Visual Studio. The game window size is 800x600 pixels.

## Graphics Requirements

The game currently uses simple SFML shapes (rectangles and circles) for the platform and ball. For enhanced graphics, you would need:

- **Platform texture**: 100x20 pixels (PNG format)
- **Ball texture**: 20x20 pixels (PNG format)
- **Background texture**: 800x600 pixels (PNG format)

Place these in the `Resources/Textures/` directory.

## Sound Requirements

The game reuses existing sound files:
- `AppleEat.wav` - Used for ball hits
- `Death.wav` - Used for game over

Place these in the `Resources/Sounds/` directory.

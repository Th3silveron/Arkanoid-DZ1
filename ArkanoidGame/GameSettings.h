#pragma once
#include <string>

namespace ArkanoidGame
{
	// Screen dimensions
	constexpr float SCREEN_WIDTH = 800.0f;
	constexpr float SCREEN_HEIGHT = 600.0f;

	// Platform settings
	constexpr float PLATFORM_WIDTH = 100.0f;
	constexpr float PLATFORM_HEIGHT = 20.0f;
	constexpr float PLATFORM_SPEED = 300.0f;

	// Ball settings
	constexpr float BALL_RADIUS = 10.0f;
	constexpr float BALL_SPEED = 400.0f;

	// Game name
	constexpr const char* GAME_NAME = "ArkanoidGame";
	constexpr const char* RECORDS_FILE = "records.txt";

	// Resource paths
	const std::string RESOURCES_PATH = "Resources/";
	const std::string TEXTURES_PATH = RESOURCES_PATH + "Textures/";
	const std::string FONTS_PATH = RESOURCES_PATH + "Fonts/";
	const std::string SOUNDS_PATH = RESOURCES_PATH + "Sounds/";

	// Game constants
	constexpr float TIME_PER_FRAME = 1.0f / 60.0f; // 60 fps
	constexpr float BONUS_DROP_CHANCE = 0.1f; // 10% chance
	constexpr float BONUS_FALL_SPEED = 100.0f;
	constexpr float BONUS_SIZE = 20.0f;
	constexpr float BONUS_RADIUS = 10.0f;
	
	// Block constants
	constexpr float BLOCK_WIDTH = 80.0f;
	constexpr float BLOCK_HEIGHT = 30.0f;
	constexpr float BLOCK_SPACING = 10.0f;
	constexpr int BLOCKS_PER_ROW = 8;
	constexpr int BLOCK_ROWS = 3;
	
	// UI constants
	constexpr int UI_FONT_SIZE_LARGE = 48;
	constexpr int UI_FONT_SIZE_MEDIUM = 24;
	constexpr int UI_FONT_SIZE_SMALL = 18;
	constexpr int UI_FONT_SIZE_TINY = 16;
}

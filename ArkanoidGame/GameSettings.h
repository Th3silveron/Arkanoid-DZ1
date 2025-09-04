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

	// Resource paths
	const std::string RESOURCES_PATH = "Resources/";
	const std::string TEXTURES_PATH = RESOURCES_PATH + "Textures/";
	const std::string FONTS_PATH = RESOURCES_PATH + "Fonts/";
	const std::string SOUNDS_PATH = RESOURCES_PATH + "Sounds/";
}

#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"

namespace ArkanoidGame
{
	class Game; // Forward declaration

	/**
	 * @brief Name input state for Arkanoid game
	 * 
	 * Allows player to enter their name after game ends.
	 * Shows current score and whether it qualifies for records table.
	 * Player can save their score or skip to main menu.
	 */
	class GameStateNameInput : public GameStateBase
	{
	private:
		sf::Font font;
		sf::Text titleText;
		sf::Text scoreText;
		sf::Text namePromptText;
		sf::Text nameInputText;
		sf::Text recordsHintText;
		sf::Text saveText;
		sf::Text skipText;
		sf::RectangleShape background;
		sf::RectangleShape inputBox;
		
		// Records table display
		sf::Text recordsTitleText;
		std::vector<sf::Text> recordsTableTexts;
		bool showRecordsTable = false;
		
		// Input handling
		std::string playerName;
		bool isTyping = false;
		
		// Menu navigation
		int selectedOption = 0; // 0 = Save, 1 = Skip
		static const int MENU_OPTIONS_COUNT = 2;
		sf::Text* menuOptions[MENU_OPTIONS_COUNT];

	public:
		GameStateNameInput();
		~GameStateNameInput() = default;

		void handleWindowEvent(const sf::Event& event) override;
		void update(float timeDelta) override;
		void draw(sf::RenderWindow& window) override;

	private:
		void initializeUI();
		void updateMenuSelection();
		void selectOption();
		void handleTextInput(const sf::Event& event);
		void updateInputDisplay();
		void initializeRecordsTable();
		void updateRecordsTable();
	};
}

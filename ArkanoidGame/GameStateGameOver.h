#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"

namespace ArkanoidGame
{
	class Game; // Forward declaration

	/**
	 * @brief Game over state for Arkanoid game
	 * 
	 * Displays game over message and offers to play again.
	 * Player can choose Yes (restart game) or No (return to main menu).
	 */
	class GameStateGameOver : public GameStateBase
	{
	private:
		sf::Font font;
		sf::Text gameOverText;
		sf::Text defeatMessageText;
		sf::Text playAgainText;
		sf::Text yesText;
		sf::Text noText;
		sf::RectangleShape background;
		
		// Menu navigation
		int selectedOption = 0; // 0 = Yes, 1 = No
		static const int MENU_OPTIONS_COUNT = 2;
		sf::Text* menuOptions[MENU_OPTIONS_COUNT];

	public:
		GameStateGameOver();
		~GameStateGameOver() = default;

		void handleWindowEvent(const sf::Event& event) override;
		void update(float timeDelta) override;
		void draw(sf::RenderWindow& window) override;

	private:
		void initializeUI();
		void updateMenuSelection();
		void selectOption();
	};
}

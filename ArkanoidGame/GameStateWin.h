#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"

namespace ArkanoidGame
{
	class Game; // Forward declaration

	/**
	 * @brief Win state for Arkanoid game
	 * 
	 * Displays congratulations message and offers to play again.
	 * Player can choose Yes (restart game) or No (return to main menu).
	 */
	class GameStateWin : public GameStateBase
	{
	private:
		sf::Font font;
		sf::Text congratulationsText;
		sf::Text playAgainText;
		sf::Text yesText;
		sf::Text noText;
		sf::RectangleShape background;
		
		// Menu navigation
		int selectedOption = 0; // 0 = Yes, 1 = No
		static const int MENU_OPTIONS_COUNT = 2;
		sf::Text* menuOptions[MENU_OPTIONS_COUNT];

	public:
		GameStateWin();
		~GameStateWin() = default;

		void handleWindowEvent(const sf::Event& event) override;
		void update(float timeDelta) override;
		void draw(sf::RenderWindow& window) override;

	private:
		void initializeUI();
		void updateMenuSelection();
		void selectOption();
	};
}

#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"

namespace ArkanoidGame
{
	class Game; // Forward declaration

	/**
	 * @brief Exit confirmation dialog game state
	 * 
	 * Simple dialog that asks the user to confirm if they want to exit the game.
	 * Shows "Press Y to exit, N or ESC to continue" message.
	 */
	class GameStateExitDialog : public GameStateBase
	{
	private:
		sf::Font font;
		sf::Text exitText;
		sf::Text hintText;
		sf::RectangleShape background;

	public:
		GameStateExitDialog();
		~GameStateExitDialog() = default;

		void handleWindowEvent(const sf::Event& event) override;
		void update(float timeDelta) override;
		void draw(sf::RenderWindow& window) override;

	private:
		void initializeUI();
	};
}

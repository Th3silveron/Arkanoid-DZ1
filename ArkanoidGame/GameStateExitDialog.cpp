#include "GameStateExitDialog.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
	GameStateExitDialog::GameStateExitDialog()
	{
		initializeUI();
	}

	void GameStateExitDialog::initializeUI()
	{
		// Load font
		if (!font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"))
		{
			// Fallback to default font if loading fails
		}

		// Initialize background
		background.setSize(sf::Vector2f(400, 200));
		background.setPosition((SCREEN_WIDTH - 400) / 2, (SCREEN_HEIGHT - 200) / 2);
		background.setFillColor(sf::Color(0, 0, 0, 200));
		background.setOutlineColor(sf::Color::White);
		background.setOutlineThickness(2);

		// Initialize exit text
		exitText.setFont(font);
		exitText.setString("Exit Game?");
		exitText.setCharacterSize(32);
		exitText.setFillColor(sf::Color::White);
		exitText.setOrigin(exitText.getLocalBounds().width / 2, exitText.getLocalBounds().height / 2);
		exitText.setPosition(SCREEN_WIDTH / 2, (SCREEN_HEIGHT - 200) / 2 + 50);

		// Initialize hint text
		hintText.setFont(font);
		hintText.setString("Press Y to exit, N or ESC to continue");
		hintText.setCharacterSize(18);
		hintText.setFillColor(sf::Color::Yellow);
		hintText.setOrigin(hintText.getLocalBounds().width / 2, hintText.getLocalBounds().height / 2);
		hintText.setPosition(SCREEN_WIDTH / 2, (SCREEN_HEIGHT - 200) / 2 + 120);
	}

	void GameStateExitDialog::handleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Y)
			{
				// Exit the game
				if (game)
				{
					game->SwitchStateTo(GameStateType::None);
				}
			}
			else if (event.key.code == sf::Keyboard::N || event.key.code == sf::Keyboard::Escape)
			{
				// Return to previous state
				if (game)
				{
					game->PopState();
				}
			}
		}
	}

	void GameStateExitDialog::update(float timeDelta)
	{
		// No update logic needed for this state
	}

	void GameStateExitDialog::draw(sf::RenderWindow& window)
	{
		window.draw(background);
		window.draw(exitText);
		window.draw(hintText);
	}
}

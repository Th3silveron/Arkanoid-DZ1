#include "GameStateGameOver.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
	GameStateGameOver::GameStateGameOver()
	{
		initializeUI();
		
		// Initialize menu options array
		menuOptions[0] = &yesText;
		menuOptions[1] = &noText;
		
		// Initialize menu selection
		updateMenuSelection();
	}

	void GameStateGameOver::initializeUI()
	{
		// Load font
		if (!font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"))
		{
			// Fallback to default font if loading fails
		}

		// Initialize background
		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(100, 0, 0, 200)); // Red background

		// Initialize game over text
		gameOverText.setFont(font);
		gameOverText.setString("GAME OVER");
		gameOverText.setCharacterSize(UI_FONT_SIZE_LARGE);
		gameOverText.setFillColor(sf::Color::Red);
		gameOverText.setOrigin(gameOverText.getLocalBounds().width / 2, gameOverText.getLocalBounds().height / 2);
		gameOverText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 150);

		// Initialize defeat message text
		defeatMessageText.setFont(font);
		defeatMessageText.setString("You lost all your lives!");
		defeatMessageText.setCharacterSize(UI_FONT_SIZE_MEDIUM);
		defeatMessageText.setFillColor(sf::Color::White);
		defeatMessageText.setOrigin(defeatMessageText.getLocalBounds().width / 2, defeatMessageText.getLocalBounds().height / 2);
		defeatMessageText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100);

		// Initialize play again text
		playAgainText.setFont(font);
		playAgainText.setString("Would you like to play again?");
		playAgainText.setCharacterSize(UI_FONT_SIZE_SMALL);
		playAgainText.setFillColor(sf::Color::White);
		playAgainText.setOrigin(playAgainText.getLocalBounds().width / 2, playAgainText.getLocalBounds().height / 2);
		playAgainText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50);

		// Initialize yes text
		yesText.setFont(font);
		yesText.setString("Yes - Play Again");
		yesText.setCharacterSize(UI_FONT_SIZE_MEDIUM);
		yesText.setFillColor(sf::Color::White);
		yesText.setOrigin(yesText.getLocalBounds().width / 2, yesText.getLocalBounds().height / 2);
		yesText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 20);

		// Initialize no text
		noText.setFont(font);
		noText.setString("No - Main Menu");
		noText.setCharacterSize(UI_FONT_SIZE_MEDIUM);
		noText.setFillColor(sf::Color::White);
		noText.setOrigin(noText.getLocalBounds().width / 2, noText.getLocalBounds().height / 2);
		noText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 20);
	}

	void GameStateGameOver::handleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Up)
			{
				selectedOption = (selectedOption - 1 + MENU_OPTIONS_COUNT) % MENU_OPTIONS_COUNT;
				updateMenuSelection();
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				selectedOption = (selectedOption + 1) % MENU_OPTIONS_COUNT;
				updateMenuSelection();
			}
			else if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space)
			{
				selectOption();
			}
			else if (event.key.code == sf::Keyboard::Escape)
			{
				// ESC defaults to No (Main Menu)
				selectedOption = 1;
				selectOption();
			}
		}
	}

	void GameStateGameOver::update(float timeDelta)
	{
		// No update logic needed for this state
	}

	void GameStateGameOver::updateMenuSelection()
	{
		// Reset all text colors to white
		yesText.setFillColor(sf::Color::White);
		noText.setFillColor(sf::Color::White);
		
		// Highlight selected option
		menuOptions[selectedOption]->setFillColor(sf::Color::Yellow);
	}

	void GameStateGameOver::selectOption()
	{
		if (!game) return;
		
		switch (selectedOption)
		{
		case 0: // Yes - Play Again
			game->SwitchStateTo(GameStateType::Playing);
			break;
		case 1: // No - Main Menu
			game->SwitchStateTo(GameStateType::MainMenu);
			break;
		}
	}

	void GameStateGameOver::draw(sf::RenderWindow& window)
	{
		// Draw background
		window.draw(background);

		// Draw all text elements
		window.draw(gameOverText);
		window.draw(defeatMessageText);
		window.draw(playAgainText);
		window.draw(yesText);
		window.draw(noText);
		
		// Draw control hint
		sf::Text hintText;
		hintText.setFont(font);
		hintText.setString("Use UP/DOWN arrows to navigate, ENTER to select, ESC for Main Menu");
		hintText.setCharacterSize(UI_FONT_SIZE_TINY);
		hintText.setFillColor(sf::Color::Cyan);
		hintText.setOrigin(hintText.getLocalBounds().width / 2, hintText.getLocalBounds().height / 2);
		hintText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 30);
		window.draw(hintText);
	}
}

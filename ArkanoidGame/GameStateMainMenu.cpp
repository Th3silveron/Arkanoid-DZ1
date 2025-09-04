#include "GameStateMainMenu.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
	GameStateMainMenu::GameStateMainMenu()
	{
		initializeUI();
		
		// Initialize menu options array
		menuOptions[0] = &startGameText;
		menuOptions[1] = &recordsText;
		menuOptions[2] = &exitText;
		
		// Initialize menu selection
		updateMenuSelection();
	}

	void GameStateMainMenu::initializeUI()
	{
		// Load font
		if (!font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"))
		{
			// Fallback to default font if loading fails
		}

		// Initialize background
		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(0, 50, 100));

		// Initialize title text
		titleText.setFont(font);
		titleText.setString("ARKANOID GAME");
		titleText.setCharacterSize(48);
		titleText.setFillColor(sf::Color::Yellow);
		titleText.setOrigin(titleText.getLocalBounds().width / 2, titleText.getLocalBounds().height / 2);
		titleText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 150);

		// Initialize start game text
		startGameText.setFont(font);
		startGameText.setString("Start Game");
		startGameText.setCharacterSize(24);
		startGameText.setFillColor(sf::Color::White);
		startGameText.setOrigin(startGameText.getLocalBounds().width / 2, startGameText.getLocalBounds().height / 2);
		startGameText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50);

		// Initialize records text
		recordsText.setFont(font);
		recordsText.setString("View Records");
		recordsText.setCharacterSize(24);
		recordsText.setFillColor(sf::Color::White);
		recordsText.setOrigin(recordsText.getLocalBounds().width / 2, recordsText.getLocalBounds().height / 2);
		recordsText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

		// Initialize exit text
		exitText.setFont(font);
		exitText.setString("Exit Game");
		exitText.setCharacterSize(24);
		exitText.setFillColor(sf::Color::White);
		exitText.setOrigin(exitText.getLocalBounds().width / 2, exitText.getLocalBounds().height / 2);
		exitText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50);
	}

	void GameStateMainMenu::handleWindowEvent(const sf::Event& event)
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
				// Exit game
				if (game)
				{
					game->SwitchStateTo(GameStateType::None);
				}
			}
		}
	}

	void GameStateMainMenu::update(float timeDelta)
	{
		// No update logic needed for this state
	}

	void GameStateMainMenu::updateMenuSelection()
	{
		// Reset all text colors to white
		startGameText.setFillColor(sf::Color::White);
		recordsText.setFillColor(sf::Color::White);
		exitText.setFillColor(sf::Color::White);
		
		// Highlight selected option
		menuOptions[selectedOption]->setFillColor(sf::Color::Yellow);
	}

	void GameStateMainMenu::selectOption()
	{
		if (!game) return;
		
		switch (selectedOption)
		{
		case 0: // Start Game
			game->SwitchStateTo(GameStateType::Playing);
			break;
		case 1: // View Records
			game->PushState(GameStateType::Records, true);
			break;
		case 2: // Exit Game
			game->SwitchStateTo(GameStateType::None);
			break;
		}
	}

	void GameStateMainMenu::draw(sf::RenderWindow& window)
	{
		// Draw background
		window.draw(background);

		// Draw all text elements
		window.draw(titleText);
		window.draw(startGameText);
		window.draw(recordsText);
		window.draw(exitText);
		
		// Draw control hint
		sf::Text hintText;
		hintText.setFont(font);
		hintText.setString("Use UP/DOWN arrows to navigate, ENTER to select, ESC to exit");
		hintText.setCharacterSize(16);
		hintText.setFillColor(sf::Color::Cyan);
		hintText.setOrigin(hintText.getLocalBounds().width / 2, hintText.getLocalBounds().height / 2);
		hintText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 30);
		window.draw(hintText);
	}
}

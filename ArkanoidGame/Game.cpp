#include "Game.h"
#include <assert.h>
#include <algorithm>
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStateExitDialog.h"
#include "GameStateMainMenu.h"
#include "GameStateRecords.h"

namespace ArkanoidGame
{
	Game::Game()
	{
		// Generate fake records table
		recordsTable =
		{
			{"John", 1000},
			{"Jane", 800 },
			{"Alice", 600 },
			{"Bob", 400 },
			{"Clementine", 200 },
		};

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		SwitchStateTo(GameStateType::MainMenu);
	}

	Game::~Game()
	{
		Shutdown();
	}

	void Game::HandleWindowEvents(sf::RenderWindow& window)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window if close button or Escape key pressed
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (stateStack.size() > 0)
			{
				stateStack.back().data->handleWindowEvent(event);
			}
		}
	}

	bool Game::Update(float timeDelta)
	{
		if (stateChangeType == GameStateChangeType::Switch)
		{
			// Clear all game states
			stateStack.clear();
		}
		else if (stateChangeType == GameStateChangeType::Pop)
		{
			// Remove only current game state
			if (stateStack.size() > 0)
			{
				stateStack.pop_back();
			}
		}

		// Initialize new game state if needed
		if (pendingGameStateType != GameStateType::None)
		{
			stateStack.push_back({ pendingGameStateType, CreateGameState(pendingGameStateType), pendingGameStateIsExclusivelyVisible });
		}

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;

		if (stateStack.size() > 0)
		{
			stateStack.back().data->update(timeDelta);
			return true;
		}

		return false;
	}

	void Game::Draw(sf::RenderWindow& window)
	{
		if (stateStack.size() > 0)
		{
			std::vector<GameState*> visibleGameStates;
			for (auto it = stateStack.rbegin(); it != stateStack.rend(); ++it)
			{
				visibleGameStates.push_back(&(*it));
				if (it->isExclusivelyVisible)
				{
					break;
				}
			}

			for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
			{
				(*it)->data->draw(window);
			}
		}
	}

	void Game::Shutdown()
	{
		// Clear all game states
		stateStack.clear();

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
	}

	void Game::PushState(GameStateType stateType, bool isExclusivelyVisible)
	{
		pendingGameStateType = stateType;
		pendingGameStateIsExclusivelyVisible = isExclusivelyVisible;
		stateChangeType = GameStateChangeType::Push;
	}

	void Game::PopState()
	{
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		stateChangeType = GameStateChangeType::Pop;
	}

	void Game::SwitchStateTo(GameStateType newState)
	{
		pendingGameStateType = newState;
		pendingGameStateIsExclusivelyVisible = false;
		stateChangeType = GameStateChangeType::Switch;
	}

	bool Game::IsEnableOptions(GameOptions option) const
	{
		const bool isEnable = ((std::uint8_t)options & (std::uint8_t)option) != (std::uint8_t)GameOptions::Empty;
		return isEnable;
	}

	void Game::SetOption(GameOptions option, bool value)
	{
		if (value) {
			options = (GameOptions)((std::uint8_t)options | (std::uint8_t)option);
		}
		else {
			options = (GameOptions)((std::uint8_t)options & ~(std::uint8_t)option);
		}
	}

	int Game::GetRecordByPlayerId(const std::string& playerId) const
	{
		auto it = recordsTable.find(playerId);
		return it == recordsTable.end() ? 0 : it->second;
	}

	void Game::UpdateRecord(const std::string& playerId, int score)
	{
		recordsTable[playerId] = std::max(recordsTable[playerId], score);
	}

	std::unique_ptr<GameStateBase> CreateGameState(GameStateType stateType)
	{
		switch (stateType)
		{
		case GameStateType::MainMenu:
		{
			return std::make_unique<GameStateMainMenu>();
		}
		case GameStateType::Playing:
		{
			return std::make_unique<GameStatePlaying>();
		}
		case GameStateType::GameOver:
		{
			return std::make_unique<GameStateGameOver>();
		}
		case GameStateType::ExitDialog:
		{
			return std::make_unique<GameStateExitDialog>();
		}
		case GameStateType::Records:
		{
			return std::make_unique<GameStateRecords>();
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			return nullptr;
		}
	}
}
